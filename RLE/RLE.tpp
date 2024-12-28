#include "RLE.h"
#include "../dataStructs/CustomVector.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

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
