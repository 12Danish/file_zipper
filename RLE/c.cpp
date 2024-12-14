#include <iostream>
#include <fstream>
#include <string>
#include "../dataStructs/CustomVector.h" // Include CustomVector.h from the dataStructs directory

// RLE Compression function template
template <typename T>
CustomVector<std::pair<T, int>> rle_compress(const CustomVector<T> &input)
{
    CustomVector<std::pair<T, int>> compressed;

    if (input.getSize() == 0)
        return compressed;

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

// RLE Decompression function template
template <typename T>
CustomVector<T> rle_decompress(const CustomVector<std::pair<T, int>> &compressed)
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

void save_compressed_to_file(const std::string &filename, const CustomVector<std::pair<char, int>> &compressed)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    for (size_t i = 0; i < compressed.getSize(); ++i)
    {
        outFile << compressed[i].first << " " << compressed[i].second << "\n";
    }

    outFile.close();
    std::cout << "Compressed data saved to " << filename << std::endl;
}

CustomVector<std::pair<char, int>> load_compressed_from_file(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return {};
    }

    CustomVector<std::pair<char, int>> compressed;
    char element;
    int count;

    while (inFile >> element >> count)
    {
        compressed.append({element, count});
    }

    inFile.close();
    return compressed;
}

void save_decompressed_to_file(const std::string &filename, const CustomVector<char> &decompressed)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    for (size_t i = 0; i < decompressed.getSize(); ++i)
    {
        outFile << decompressed[i];
    }

    outFile.close();
    std::cout << "Decompressed data saved to " << filename << std::endl;
}

int main()
{
    std::string inputFile = "input.txt";
    std::string compressedFile = "compressed.txt";
    std::string decompressedFile = "decompressed.txt";

    // Read input file
    std::ifstream inFile(inputFile);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << inputFile << " for reading." << std::endl;
        return 1;
    }

    CustomVector<char> inputData;
    char ch;
    while (inFile.get(ch))
    {
        inputData.append(ch);
    }
    inFile.close();

    // Compress the data
    auto compressedData = rle_compress(inputData);
    save_compressed_to_file(compressedFile, compressedData);

    // Decompress the data
    auto loadedCompressedData = load_compressed_from_file(compressedFile);
    auto decompressedData = rle_decompress(loadedCompressedData);
    save_decompressed_to_file(decompressedFile, decompressedData);

    return 0;
}
