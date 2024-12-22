#include "../dataStructs/HuffmanTree.h"
#include "../dataStructs/CustomVector.h"
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
                std::cout << "'\\n'" << ": " << pair.second << std::endl;
            }
            else if (pair.first == '\t')
            {
                std::cout << "'\\t'" << ": " << pair.second << std::endl;
            }
            else if (pair.first == ' ')
            {
                std::cout << "' '" << ": " << pair.second << std::endl;
            }
            else
            {
                std::cout << "'" << pair.first << "'" << ": " << pair.second << std::endl;
            }
        }
        // Cleanup
        delete[] char_array;
        delete[] freq_array;
        delete root;
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
        HuffmanCoding huffman("input.txt", "output.txt");
        huffman.compress();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}