#include "../dataStructs/HuffmanTree.h"
#include "../dataStructs/CustomVector.h"
#include <bitset>
#include <map>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class HuffmanCoding
{
private:
    string input_path;
    string output_path;
    HuffmanTree tree;
    string data;
    CustomVector<char> distinct_chars;
    CustomVector<int> frequency;

    // Read file and populate data string
    void read_file()
    {
        ifstream file(input_path);
        if (!file.is_open())
        {
            throw runtime_error("Unable to open input file: " + input_path);
        }

        // Read file content into data string
        string line;
        while (getline(file, line))
        {
            data += line;
            if (!file.eof())
            {
                data += '\n'; // Preserve line breaks except for last line
            }
        }
        file.close();

        // Process the data to populate distinct_chars and frequency
        process_data();
    }

    // Process the data string to find distinct characters and their frequencies
    void process_data()
    {
        if (data.empty())
        {
            throw runtime_error("No data to process");
        }

        // First pass: collect distinct characters
        for (char c : data)
        {
            bool found = false;
            for (size_t i = 0; i < distinct_chars.getSize(); ++i)
            {
                if (distinct_chars[i] == c)
                {
                    found = true;
                    frequency[i]++;
                    break;
                }
            }
            if (!found)
            {
                distinct_chars.append(c);
                frequency.append(1);
            }
        }
    }

    // Function to generate and process Huffman codes
    void generateCodes()
    {
        if (distinct_chars.getSize() == 0)
        {
            throw runtime_error("No characters to encode");
        }

        // Convert CustomVector to arrays for HuffmanTree
        char *char_array = new char[distinct_chars.getSize()];
        int *freq_array = new int[frequency.getSize()];

        for (size_t i = 0; i < distinct_chars.getSize(); ++i)
        {
            char_array[i] = distinct_chars[i];
            freq_array[i] = frequency[i];
        }

        // Build Huffman tree and get codes
        HuffmanTree::Node *root = tree.buildHuffmanTree(char_array, freq_array, distinct_chars.getSize());
        int treeHeight = HuffmanTree::getTreeHeight(root);

        cout << "Tree Height: " << treeHeight << endl;
        cout << "Character Frequencies:" << endl;
        for (size_t i = 0; i < distinct_chars.getSize(); ++i)
        {
            cout << "'" << distinct_chars[i] << "': " << frequency[i] << endl;
        }

        cout << "\nHuffman Codes:" << endl;
        auto codes = tree.getCodes(root);

        // Print the Huffman codes
        for (const auto &pair : codes)
        {
            // Handle special characters for better readability
            if (pair.first == '\n')
            {
                cout << "'\\n'" << ": " << pair.second << std::endl;
            }
            else if (pair.first == '\t')
            {
                cout << "'\\t'" << ": " << pair.second << std::endl;
            }
            else if (pair.first == ' ')
            {
                cout << "' '" << ": " << pair.second << std::endl;
            }
            else
            {
                cout << "'" << pair.first << "'" << ": " << pair.second << endl;
            }
        }
        save_output(codes);
        // Cleanup
        delete[] char_array;
        delete[] freq_array;
        delete root;
    }

    void save_output(const unordered_map<char, string> &codes)
    {
        if (output_path.empty() || data.empty())
        {
            throw runtime_error("Output path or data is empty");
        }

        ofstream outFile(output_path, ios::binary);
        if (!outFile.is_open())
        {
            throw runtime_error("Unable to create output file: " + output_path);
        }

        // 1. Write number of unique characters (as an integer)
        int uniqueChars = distinct_chars.getSize();
        outFile.write(reinterpret_cast<const char *>(&uniqueChars), sizeof(uniqueChars));

        // 2. Write total number of characters in input file
        int totalChars = data.length();
        outFile.write(reinterpret_cast<const char *>(&totalChars), sizeof(totalChars));

        // 3. Write character-code mapping table
        for (size_t i = 0; i < distinct_chars.getSize(); ++i)
        {
            // Write the character
            char currentChar = distinct_chars[i];
            outFile.write(&currentChar, sizeof(char));

            // Write its code
            const string &code = codes.at(currentChar);
            // Write code length first
            int codeLength = code.length();
            outFile.write(reinterpret_cast<const char *>(&codeLength), sizeof(codeLength));
            // Write the code itself
            outFile.write(code.c_str(), codeLength);
        }

        // 4. Write the encoded data
        string encodedData;
        for (char c : data)
        {
            encodedData += codes.at(c);
        }

        // If the encoded data's length is not a multiple of 8,
        // pad it with zeros to complete the last byte
        int padding = 8 - (encodedData.length() % 8);
        if (padding != 8)
        {
            encodedData += string(padding, '0');
        }

        // Write the padding size (needed for decoding)
        outFile.write(reinterpret_cast<const char *>(&padding), sizeof(padding));

        // Convert bit string to bytes and write to file
        for (size_t i = 0; i < encodedData.length(); i += 8)
        {
            string byte = encodedData.substr(i, 8);
            char c = static_cast<char>(bitset<8>(byte).to_ulong());
            outFile.write(&c, sizeof(char));
        }

        outFile.close();
    }

    void manage_directories()
    {
        // Implementation for managing directories if needed
    }

public:
    // Constructor with input and output paths
    HuffmanCoding(const string &input = "", const string &output = "")
        : input_path(input), output_path(output) {}

    // Set input and output paths
    void set_paths(const string &input, const string &output)
    {
        input_path = input;
        output_path = output;
    }

    // Main compression function
    void compress()
    {
        try
        {
            read_file();
            generateCodes();
            // Additional compression steps can be added here
        }
        catch (const exception &e)
        {
            cerr << "Error during compression: " << e.what() << endl;
        }
    }

    // Getters for testing and verification
    const CustomVector<char> &get_distinct_chars() const { return distinct_chars; }
    const CustomVector<int> &get_frequencies() const { return frequency; }
    const string &get_data() const { return data; }
};

// Example usage in main
int main()
{
    try
    {
        HuffmanCoding huffman("input.txt", "output.huf");
        huffman.compress();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}