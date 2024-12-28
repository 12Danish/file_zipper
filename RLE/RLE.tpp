#include "RLE.h"
#include "../dataStructs/CustomVector.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <filesystem>
using namespace std;

namespace fs = std::filesystem;

template <typename T>
CustomVector<pair<T, int>> RLE<T>::rle_compress(const CustomVector<T> &input)
{
    CustomVector<pair<T, int>> compressed;

    if (input.getSize() == 0)
    {
        cerr << "Input data is empty. Nothing to compress." << endl;
        return compressed;
    }

    T current = input[0];
    int count = 1;

    for (size_t i = 1; i < input.getSize(); ++i)
    {
        if (input[i] == current)
        {
            ++count;
        }
        else
        {
            compressed.append({current, count});
            current = input[i];
            count = 1;
        }
    }

    compressed.append({current, count}); // Append the last run
    return compressed;
}

template <typename T>
CustomVector<T> RLE<T>::rle_decompress(const CustomVector<pair<T, int>> &compressed)
{
    CustomVector<T> decompressed;

    for (size_t i = 0; i < compressed.getSize(); ++i)
    {
        const auto &pair = compressed[i];
        for (int j = 0; j < pair.second; ++j)
        {
            decompressed.append(pair.first);
        }
    }

    return decompressed;
}

template <typename T>
void RLE<T>::save_compressed_to_file(const string &filename, const CustomVector<pair<T, int>> &compressed)
{
    ofstream outFile(filename, ios::binary);

    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    size_t size = compressed.getSize();
    outFile.write(reinterpret_cast<const char *>(&size), sizeof(size));

    for (size_t i = 0; i < compressed.getSize(); ++i)
    {
        const auto &pair = compressed[i];
        outFile.write(reinterpret_cast<const char *>(&pair.first), sizeof(pair.first));
        outFile.write(reinterpret_cast<const char *>(&pair.second), sizeof(pair.second));
    }

    outFile.close();
}

template <typename T>
CustomVector<pair<T, int>> RLE<T>::load_compressed_from_file(const string &filename)
{
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return {};
    }

    CustomVector<pair<T, int>> compressed;
    size_t size;
    inFile.read(reinterpret_cast<char *>(&size), sizeof(size));

    for (size_t i = 0; i < size; ++i)
    {
        T element;
        int count;
        inFile.read(reinterpret_cast<char *>(&element), sizeof(element));
        inFile.read(reinterpret_cast<char *>(&count), sizeof(count));

        if (inFile)
        {
            compressed.append({element, count});
        }
    }

    inFile.close();
    return compressed;
}

template <typename T>
void RLE<T>::save_decompressed_to_file(const string &filename, const CustomVector<T> &decompressed)
{
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    for (size_t i = 0; i < decompressed.getSize(); ++i)
    {
        outFile << decompressed[i];
    }

    outFile.close();
}

template <typename T>
CustomVector<T> RLE<T>::load_input_file(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return {};
    }

    CustomVector<T> inputData;
    T ch;
    while (inFile.get(ch))
    {
        inputData.append(ch);
    }
    inFile.close();
    return inputData;
}

template <typename T>
void RLE<T>::process_compression(const string &inputFile, const string &compressedFile)
{
    CustomVector<T> inputData = load_input_file(inputFile);
    if (inputData.getSize() == 0)
    {
        cerr << "Error: No data to compress." << endl;
        return;
    }

    auto compressedData = rle_compress(inputData);
    save_compressed_to_file(compressedFile, compressedData);
}

template <typename T>
void RLE<T>::process_decompression(const string &compressedFile, const string &decompressedFile)
{
    auto compressedData = load_compressed_from_file(compressedFile);
    if (compressedData.getSize() == 0)
    {
        cerr << "Error: No compressed data to decompress." << endl;
        return;
    }

    auto decompressedData = rle_decompress(compressedData);
    save_decompressed_to_file(decompressedFile, decompressedData);
}

template <typename T>
CustomVector<fs::path> RLE<T>::list_files_recursive(const fs::path &dir)
{
    CustomVector<fs::path> filePaths;
    for (const auto &entry : fs::recursive_directory_iterator(dir))
    {
        if (entry.is_regular_file())
        {
            filePaths.append(entry.path());
        }
    }
    return filePaths;
}

template <typename T>
void RLE<T>::compress_directory(const string &directoryPath, const string &outputFile)
{
    // Open the output file for writing
    ofstream outFile(outputFile, ios::binary);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file " << outputFile << " for writing." << endl;
        return;
    }

    // Base directory path
    fs::path basePath = directoryPath;

    // List all files recursively using CustomVector
    CustomVector<fs::path> files = list_files_recursive(basePath);

    // Write the number of files to the output file
    size_t fileCount = files.getSize();
    outFile.write(reinterpret_cast<const char *>(&fileCount), sizeof(fileCount));

    for (size_t i = 0; i < fileCount; ++i)
    {
        const auto &file = files[i];

        // Compute the relative path from the base directory
        string relativePath = fs::relative(file, basePath).string();

        // Write the relative path size and the path itself
        size_t pathSize = relativePath.size();
        outFile.write(reinterpret_cast<const char *>(&pathSize), sizeof(pathSize));
        outFile.write(relativePath.c_str(), pathSize);

        // Read and compress file contents
        ifstream inFile(file, ios::binary);
        if (!inFile.is_open())
        {
            cerr << "Error: Could not open file " << file.string() << " for reading." << endl;
            continue;
        }

        // Read file contents into CustomVector
        CustomVector<char> fileContents;
        char buffer;
        while (inFile.get(buffer))
        {
            fileContents.append(buffer);
        }
        inFile.close();

        // Compress the file contents using RLE
        auto compressedData = rle_compress(fileContents);

        // Write compressed data size and data to the output file
        size_t compressedSize = compressedData.getSize();
        outFile.write(reinterpret_cast<const char *>(&compressedSize), sizeof(compressedSize));
        for (size_t j = 0; j < compressedSize; ++j)
        {
            outFile.write(reinterpret_cast<const char *>(&compressedData[j].first), sizeof(compressedData[j].first));
            outFile.write(reinterpret_cast<const char *>(&compressedData[j].second), sizeof(compressedData[j].second));
        }
    }

    outFile.close();
}

template <typename T>
void RLE<T>::decompress_directory(const string &compressedFile, const string &outputDirectory)
{
    // Open the compressed file for reading
    ifstream inFile(compressedFile, ios::binary);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file " << compressedFile << " for reading." << endl;
        return;
    }

    // Base path for output directory
    fs::path outputBasePath = outputDirectory;

    // Read the number of files
    size_t fileCount;
    inFile.read(reinterpret_cast<char *>(&fileCount), sizeof(fileCount));

    for (size_t i = 0; i < fileCount; ++i)
    {
        // Read the relative path size and the path itself
        size_t pathSize;
        inFile.read(reinterpret_cast<char *>(&pathSize), sizeof(pathSize));

        CustomVector<char> relativePathVector;
        for (size_t j = 0; j < pathSize; ++j)
        {
            char ch;
            inFile.read(&ch, sizeof(ch));
            relativePathVector.append(ch);
        }
        string relativePath(relativePathVector.getData(), pathSize); // Convert CustomVector to string

        // Construct the full output path
        fs::path outputPath = outputBasePath / relativePath;

        // Create necessary directories for the file
        fs::create_directories(outputPath.parent_path());

        // Read the compressed data size
        size_t compressedSize;
        inFile.read(reinterpret_cast<char *>(&compressedSize), sizeof(compressedSize));

        // Read the compressed data into a CustomVector
        CustomVector<pair<char, int>> compressedData;
        for (size_t j = 0; j < compressedSize; ++j)
        {
            char element;
            int count;
            inFile.read(reinterpret_cast<char *>(&element), sizeof(element));
            inFile.read(reinterpret_cast<char *>(&count), sizeof(count));
            compressedData.append({element, count});
        }

        // Decompress the data
        CustomVector<char> decompressedData = rle_decompress(compressedData);

        // Write the decompressed data to the output file
        ofstream outFile(outputPath, ios::binary);
        for (size_t j = 0; j < decompressedData.getSize(); ++j)
        {
            outFile.put(decompressedData[j]);
        }
        outFile.close();
    }

    inFile.close();
}
