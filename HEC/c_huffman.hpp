
// Header Guards to prevent header files from being included multiple times
#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
using namespace std;
#include <string>
#include "../dataStructs/CustomMinHeap.h"
#include "../dataStructs/CustomVector.h"
#include <optional>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
// Defining Huffman Tree Node
struct Node
{
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    Node()
    {
        left = right = NULL;
    }
};

class huffman
{
private:
    CustomVector<Node *> arr;
    char mode;
    fstream inFile, outFile;

    string inPath, outPath;

    Node *root;

    class Compare
    {
    public:
        bool operator()(Node *l, Node *r)
        {
            return l->freq > r->freq;
        }
    };

    CustomMinHeap<Node *> minHeap;

    // Initializing a vector of tree nodes representing character's ascii value and initializing its frequency with 0
    void createArr();

    void clearMinHeap();

    void resetArr();

    // Traversing the constructed tree to generate huffman codes of each present character
    void traverse(Node *, string);

    // Function to convert binary string to its equivalent decimal value
    int binToDec(string);

    // Function to convert a decimal number to its equivalent binary string
    string decToBin(int);

    // Reconstructing the Huffman tree while Decoding the file
    void buildTree(char, string &);

    // Creating Min Heap of Nodes by frequency of characters in the input file
    void createMinHeap(optional<fs::path> dir_file = nullopt);

    // Constructing the Huffman tree
    void createTree();

    // Generating Huffman codes
    void createCodes();

    // Saving Huffman Encoded File
    void saveEncodedFile(optional<fs::path> dir_file = nullopt);

    // Saving Decoded File to obtain the original File
    void saveDecodedFile();

    // Reading the file to reconstruct the Huffman tree
    void getTree();

public:
    // Constructor
    huffman(string inPath, string outPath, char mode)
    {
        this->mode = mode;
        this->inPath = inPath;
        this->outPath = outPath;
        createArr();
    }
    // Compressing input file
    void compress();
    // Decrompressing input file
    void decompress();

    void compress_directories();

    void decompress_directories();
};
#endif