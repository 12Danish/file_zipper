// HuffmanTree.h
#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

class HuffmanTree
{
public:
    // Node structure for each node of the Huffman Tree
    struct Node
    {
        char data;          // Character stored in the node
        unsigned freq;      // Frequency of the character
        Node *left, *right; // Left and right child pointers

        // Constructor to initialize the node with data and frequency
        Node(char data, unsigned freq);
        // Destructor to recursively delete child nodes
        ~Node();
    };

    // Calculate tree height
    static int getTreeHeight(Node *root);

    // Build the Huffman Tree from the input data and frequencies
    Node *buildHuffmanTree(char data[], int freq[], int size);

    // Generate Huffman codes and return them as an unordered map
    std::unordered_map<char, std::string> getCodes(Node *root);

private:
    // MinHeap structure to store nodes with their frequencies
    struct MinHeap
    {
        unsigned size;     // Current size of the heap
        unsigned capacity; // Maximum capacity of the heap
        Node **array;      // Array of pointers to nodes

        // Constructor to initialize a heap of given capacity
        MinHeap(unsigned capacity);
        // Destructor to free memory allocated for the heap
        ~MinHeap();
    };

    void swapNodes(Node **a, Node **b);
    void minHeapify(MinHeap *minHeap, int idx);
    bool isSizeOne(MinHeap *minHeap);
    Node *extractMin(MinHeap *minHeap);
    void insertMinHeap(MinHeap *minHeap, Node *minHeapNode);
    void buildMinHeap(MinHeap *minHeap);
    MinHeap *createAndBuildMinHeap(char data[], int freq[], int size);
    void getCodesHelper(Node *root, std::string code, std::unordered_map<char, std::string> &codeMap);
};

#endif // HUFFMAN_TREE_H
