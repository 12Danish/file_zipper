#include <iostream>
#include "c_huffman.hpp"
using namespace std;

ifstream::pos_type filesize(const char *filename);

int main()
{
    string workingMode;
    string inpath;
    string outpath;
    cout << "Enter the working mode:";
    cin >> workingMode;
    if (workingMode == "compress")
    {
        cout << "Enter file's path which you want to compress:";
        cin >> inpath;
        ifstream inFile(inpath);
        if (!inFile)
        {
            cerr << "Input file does not exist." << endl;
            return 1;
        }
        inFile.close();
        cout << "Enter path where you want to store the compressed file:";
        cin >> outpath;
        clock_t tStart = clock();
        huffman f(inpath, outpath);
        f.compress();
        const char *inchararr = inpath.c_str();
        const char *outchararr = outpath.c_str();
        cout << "Time taken: " << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << "sec" << endl;
        cout << "Input File Size : " << filesize(inchararr) << " bytes." << endl;
        cout << "Compressed File Size : " << filesize(outchararr) << " bytes." << endl;
        cout << "Compression Ratio : " << (1.0 * filesize(outchararr) / filesize(inchararr)) << endl;
    }
    else if (workingMode == "decompress")
    {
        cout << "Enter file's path which you want to decompress:";
        cin >> inpath;
        ifstream inFile(inpath);
        if (!inFile)
        {
            cerr << "Input file does not exist." << endl;
            return 1;
        }
        inFile.close();
        cout << "Enter path where you want to store the decompressed file:";
        cin >> outpath;
        clock_t tStart = clock();
        huffman f(inpath, outpath);
        f.decompress();
        const char *inchararr = inpath.c_str();
        const char *outchararr = outpath.c_str();
        cout << "Time taken: " << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << "sec" << endl;
        cout << "Input File (Compressed) Size : " << filesize(inchararr) << " bytes." << endl;
        cout << "DeCompressed File Size : " << filesize(outchararr) << " bytes." << endl;
    }
    else
    {
        cout << "Invalid input!";
    }
    return 0;
}

std::ifstream::pos_type filesize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}