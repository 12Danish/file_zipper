#include <iostream>
#include <filesystem>
#include "./HEC/c_huffman.hpp"
#include "./RLE/RLE.h"

using namespace std;
namespace fs = std::filesystem;

ifstream::pos_type filesize(const char *filename);

int main()
{
    string workingMode;
    while (true)
    {
        std::cout << "\nEnter the working mode (compress/decompress or 'exit' to quit): ";
        cin >> workingMode;

        if (workingMode == "exit")
        {
            std::cout << "Exiting the program." << endl;
            break;
        }
        else if (workingMode != "compress" && workingMode != "decompress")
        {
            cerr << "Invalid input! Please enter 'compress', 'decompress', or 'exit'." << endl;
            cin.clear();                                         // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue;
        }

        string algorithmChoice;
        while (true)
        {
            std::cout << "Choose the algorithm:\n1. RLE (Text files and directories)\n2. HEC (Text files only)\nEnter your choice: ";
            cin >> algorithmChoice;

            if (cin.fail() || (algorithmChoice != "RLE" && algorithmChoice != "HEC"))
            {
                cerr << "Invalid algorithm choice! Please enter 1 or 2." << endl;
                cin.clear();                                         // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                continue;
            }
            break;
        }

        string inpath, outpath;

        if (algorithmChoice == "RLE") // RLE
        {
            string typeChoice;
            while (true)
            {
                std::cout << "Do you want to process a file or a directory? (file/directory): ";
                cin >> typeChoice;

                if (typeChoice != "file" && typeChoice != "directory")
                {
                    cerr << "Invalid input! Please enter 'file' or 'directory'." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                std::cout << "Enter input path: ";
                cin >> inpath;

                if (typeChoice == "file")
                {
                    if (!fs::exists(inpath) || !fs::is_regular_file(inpath))
                    {
                        cerr << "Invalid file path! Please provide a valid file for processing." << endl;
                        continue;
                    }
                }
                else // directory
                {
                    if (workingMode == "compress" && (!fs::exists(inpath) || !fs::is_directory(inpath)))
                    {
                        cerr << "Invalid directory path! Please provide a valid directory for compression." << endl;
                        continue;
                    }
                    else if (workingMode == "decompress" && (!fs::exists(inpath) || !fs::is_regular_file(inpath)))
                    {
                        cerr << "Invalid file path! Please provide a valid compressed file for decompression." << endl;
                        continue;
                    }
                }

                std::cout << "Enter output path: ";
                cin >> outpath;

                if (workingMode == "decompress" && typeChoice == "directory" &&
                    (!fs::exists(outpath) || !fs::is_directory(outpath)))
                {
                    cerr << "Invalid output directory path for decompression." << endl;
                    continue;
                }

                // Proceed with processing
                clock_t tStart = clock();
                if (typeChoice == "file")
                {
                    if (workingMode == "compress")
                        RLE<char>::process_compression(inpath, outpath);
                    else
                        RLE<char>::process_decompression(inpath, outpath);

                    const char *inchararr = inpath.c_str();
                    const char *outchararr = outpath.c_str();
                    std::cout << "Time taken: " << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << " sec" << endl;
                    std::cout << "Input File Size: " << filesize(inchararr) << " bytes." << endl;
                    std::cout << "Output File Size: " << filesize(outchararr) << " bytes." << endl;
                    std::cout << "Compression Ratio: " << (1.0 * filesize(outchararr) / filesize(inchararr)) << endl;
                }
                else // directory
                {
                    size_t totalInputSize = 0;
                    size_t totalOutputSize = 0;

                    if (workingMode == "compress")
                    {
                        // Calculate total input size by iterating over files in the input directory
                        for (const auto &file : fs::recursive_directory_iterator(inpath))
                        {
                            if (fs::is_regular_file(file))
                            {
                                totalInputSize += fs::file_size(file);
                            }
                        }

                        // Perform compression
                        RLE<char>::compress_directory(inpath, outpath);

                        // Output size is a single file, so we calculate the size of the output file directly
                        if (fs::is_regular_file(outpath))
                        {
                            totalOutputSize = fs::file_size(outpath);
                        }
                    }
                    else // decompress
                    {
                        // Input is a single file, so we just calculate its size directly
                        if (fs::is_regular_file(inpath))
                        {
                            totalInputSize = fs::file_size(inpath);
                        }

                        // Perform decompression
                        RLE<char>::decompress_directory(inpath, outpath);

                        // Calculate total output size by iterating over the files in the output directory
                        for (const auto &file : fs::recursive_directory_iterator(outpath))
                        {
                            if (fs::is_regular_file(file))
                            {
                                totalOutputSize += fs::file_size(file);
                            }
                        }
                    }

                    std::cout << "Directory processing completed in " << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << " sec" << endl;
                    std::cout << "Total Input Directory Size: " << totalInputSize << " bytes." << endl;
                    std::cout << "Total Output Directory Size: " << totalOutputSize << " bytes." << endl;
                    std::cout << "Compression Ratio: " << (1.0 * totalOutputSize / totalInputSize) << endl;
                }

                break;
            }
        }
        else if (algorithmChoice == "HEC") // HEC
        {
            while (true)
            {
                std::cout << "Enter input path (file only): ";
                cin >> inpath;

                if (!fs::exists(inpath) || !fs::is_regular_file(inpath))
                {
                    cerr << "Invalid input! Please provide a valid file path." << endl;
                    continue;
                }

                std::cout << "Enter output path: ";
                cin >> outpath;

                clock_t tStart = clock();
                huffman huff(inpath, outpath);
                if (workingMode == "compress")
                    huff.compress();
                else
                    huff.decompress();

                const char *inchararr = inpath.c_str();
                const char *outchararr = outpath.c_str();
                std::cout << "Time taken: " << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << " sec" << endl;
                std::cout << "Input File Size: " << filesize(inchararr) << " bytes." << endl;
                std::cout << "Output File Size: " << filesize(outchararr) << " bytes." << endl;
                std::cout << "Compression Ratio: " << (1.0 * filesize(outchararr) / filesize(inchararr)) << endl;
                break;
            }
        }
    }
    return 0;
}

std::ifstream::pos_type filesize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}
