#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <fstream>
#include <string>
#include "../dataStructs/CustomVector.h" // Include CustomVector.h from the dataStructs directory

using namespace std;

template <typename T>
class RLE
{
private:
    // Function declarations
    static CustomVector<pair<T, int>> rle_compress(const CustomVector<T> &input);
    static CustomVector<T> rle_decompress(const CustomVector<pair<T, int>> &compressed);
    static void save_compressed_to_file(const string &filename, const CustomVector<pair<T, int>> &compressed);
    static CustomVector<pair<T, int>> load_compressed_from_file(const string &filename);
    static void save_decompressed_to_file(const string &filename, const CustomVector<T> &decompressed);

    // Methods to handle files directly (main function will use these)
    static CustomVector<T> load_input_file(const string &filename);

public:
    static void process_compression(const string &inputFile, const string &compressedFile);
    static void process_decompression(const string &compressedFile, const string &decompressedFile);
};

#include "RLE.tpp" // Include the implementation of the RLE functions

#endif // RLE_H