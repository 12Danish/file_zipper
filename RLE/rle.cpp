#include <iostream>
#include <fstream>
#include <string>
#include <sstream>                       // for istringstream
#include "../dataStructs/CustomVector.h" // Include CustomVector.h from the dataStructs directory
using namespace std;

template <typename T>
CustomVector<pair<T, int>> rle_compress(const CustomVector<T> &input)
{
    CustomVector<pair<T, int>> compressed;

    if (input.getSize() == 0)
    {
        cout << "Input data is empty. Nothing to compress." << endl;
        return compressed;
    }

    cout << "Compressing data..." << endl;
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
            cout << "Compressed run: " << current << " x" << count << endl;
            current = input[i];
            count = 1;
        }
    }

    compressed.append({current, count}); // Append the last run
    cout << "Compressed run: " << current << " x" << count << endl;

    return compressed;
};

template <typename T>
CustomVector<T> rle_decompress(const CustomVector<pair<T, int>> &compressed)
{
    CustomVector<T> decompressed;
    cout << "Decompressing data..." << endl;

    for (size_t i = 0; i < compressed.getSize(); ++i)
    {
        const auto &pair = compressed[i];
        cout << "Decompressing: " << pair.first << " x" << pair.second << endl;
        for (int j = 0; j < pair.second; ++j)
        {
            decompressed.append(pair.first);
        }
    }

    return decompressed;
}

void save_compressed_to_file(const string &filename, const CustomVector<pair<char, int>> &compressed)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    cout << "Saving compressed data to file: " << filename << endl;

    for (size_t i = 0; i < compressed.getSize(); ++i)
    {
        outFile << compressed[i].first << " " << compressed[i].second << "\n";
        cout << "Saved: " << compressed[i].first << " x" << compressed[i].second << endl;
    }

    outFile.close();
    cout << "Compressed data saved to " << filename << endl;
}

CustomVector<pair<char, int>> load_compressed_from_file(const string &filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return {};
    }

    cout << "Loading compressed data from file: " << filename << endl;

    CustomVector<pair<char, int>> compressed;
    string line; // Define 'line' variable to hold each line

    while (inFile) // Loop until the end of the file is reached
    {
        // Skip any empty lines
        string line;
        char element;
        int count;

        // Read the first character (the element)
        inFile.get(element); // Read first character

        // Skip the space after the character
        inFile.get(); // This will skip the space after the character

        // Read the count (integer) after the space
        inFile >> count;

        // Check if the extraction was successful
        if (inFile)
        {
            compressed.append({element, count});
            cout << "Loaded: '" << element << "' x" << count << endl;
        }

        // Skip the newline after the count
        inFile.get(); // This will skip the newline character

        // If you want to break out of the loop when an invalid line is encountered, you can check for errors
        if (inFile.fail())
            break;
    }

    inFile.close();
    return compressed;
}

void save_decompressed_to_file(const string &filename, const CustomVector<char> &decompressed)
{
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    cout << "Saving decompressed data to file: " << filename << endl;

    for (size_t i = 0; i < decompressed.getSize(); ++i)
    {
        outFile << decompressed[i];
        cout << "Saved: " << decompressed[i] << endl;
    }

    outFile.close();
    cout << "Decompressed data saved to " << filename << endl;
}

int main()
{
    string inputFile = "input.txt";
    string compressedFile = "compressed.txt";
    string decompressedFile = "decompressed.txt";

    // Read input file
    ifstream inFile(inputFile);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file " << inputFile << " for reading." << endl;
        return 1;
    }

    CustomVector<char> inputData;
    char ch;
    while (inFile.get(ch))
    {
        inputData.append(ch);
    }
    inFile.close();

    cout << "Input data loaded from file: " << inputFile << endl;
    cout << "Input data size: " << inputData.getSize() << endl;

    // Compress the data
    auto compressedData = rle_compress(inputData);
    save_compressed_to_file(compressedFile, compressedData);

    // Decompress the data
    auto loadedCompressedData = load_compressed_from_file(compressedFile);
    auto decompressedData = rle_decompress(loadedCompressedData);
    save_decompressed_to_file(decompressedFile, decompressedData);

    return 0;
}
