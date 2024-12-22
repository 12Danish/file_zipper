// HuffmanTree.cpp
#include "HuffmanTree.h"

/*
 * Node Implementation
 * These methods handle the creation and cleanup of individual nodes in the Huffman tree
 */

// Constructor: Creates a new node with given character and frequency
// Initializes left and right child pointers to nullptr
HuffmanTree::Node::Node(char data, unsigned freq)
    : data(data), freq(freq), left(nullptr), right(nullptr) {}

// Destructor: Recursively deletes all child nodes
// This ensures proper cleanup of the entire tree when a node is deleted
HuffmanTree::Node::~Node()
{
    delete left;  // Recursively delete left subtree
    delete right; // Recursively delete right subtree
}

/*
 * MinHeap Implementation
 * The MinHeap is used to efficiently find the two lowest frequency nodes when building the tree
 */

// Constructor: Creates a new min heap with specified capacity
// Allocates memory for the array of Node pointers
HuffmanTree::MinHeap::MinHeap(unsigned capacity)
    : size(0), capacity(capacity)
{
    array = new Node *[capacity];
}

// Destructor: Frees the memory allocated for the heap array
// Note: Does not delete the nodes themselves, as they become part of the tree
HuffmanTree::MinHeap::~MinHeap()
{
    delete[] array;
}

/*
 * Tree Height Calculation
 * Static utility function to determine the height of the Huffman tree
 */

// Recursively calculates the height of the tree from a given root node
// Height is defined as the number of edges in the longest path from root to leaf
int HuffmanTree::getTreeHeight(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftHeight = getTreeHeight(root->left);   // Get height of left subtree
    int rightHeight = getTreeHeight(root->right); // Get height of right subtree
    return std::max(leftHeight, rightHeight) + 1; // Return max height plus current level
}

/*
 * MinHeap Helper Functions
 * These private methods handle the internal operations of the min heap
 */

// Swaps two nodes in the heap array
// Used during heapification process
void HuffmanTree::swapNodes(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

// Maintains the min heap property starting from index idx
// Ensures that the parent node has lower frequency than its children
void HuffmanTree::minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;  // Left child index
    int right = 2 * idx + 2; // Right child index

    // If left child exists and has smaller frequency than current smallest
    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    {
        smallest = left;
    }

    // If right child exists and has smaller frequency than current smallest
    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    {
        smallest = right;
    }

    // If smallest is not the current node, swap and recursively heapify
    if (smallest != idx)
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Checks if the heap contains exactly one node
// Used as a termination condition when building the Huffman tree
bool HuffmanTree::isSizeOne(MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

// Extracts and returns the node with minimum frequency from the heap
// Maintains the heap property after extraction
HuffmanTree::Node *HuffmanTree::extractMin(MinHeap *minHeap)
{
    Node *temp = minHeap->array[0];                        // Store the root
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; // Move last element to root
    --minHeap->size;                                       // Reduce heap size
    minHeapify(minHeap, 0);                                // Restore heap property
    return temp;
}

// Inserts a new node into the min heap
// Maintains the heap property by moving the node up as needed
void HuffmanTree::insertMinHeap(MinHeap *minHeap, Node *minHeapNode)
{
    ++minHeap->size;           // Increase heap size
    int i = minHeap->size - 1; // Start at the last position

    // Move up through the heap until we find the right position
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode; // Place the node in its correct position
}

// Converts an array of nodes into a min heap
// Called during initial heap creation
void HuffmanTree::buildMinHeap(MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    // Start from last non-leaf node and heapify each subtree
    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        minHeapify(minHeap, i);
    }
}

// Creates and initializes a min heap from the input data and frequency arrays
// Returns a pointer to the newly created min heap
HuffmanTree::MinHeap *HuffmanTree::createAndBuildMinHeap(char data[], int freq[], int size)
{
    MinHeap *minHeap = new MinHeap(size);

    // Create a node for each character and its frequency
    for (int i = 0; i < size; ++i)
    {
        minHeap->array[i] = new Node(data[i], freq[i]);
    }

    minHeap->size = size;
    buildMinHeap(minHeap); // Convert array to min heap

    return minHeap;
}

/*
 * Public Interface Implementation
 * These methods implement the main functionality of the Huffman Tree
 */

// Builds the Huffman tree from the input data and frequency arrays
// Returns the root node of the constructed tree
HuffmanTree::Node *HuffmanTree::buildHuffmanTree(char data[], int freq[], int size)
{
    Node *left, *right, *top;
    MinHeap *minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate until only one node remains in the heap
    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);  // Extract first minimum
        right = extractMin(minHeap); // Extract second minimum

        // Create internal node with frequency = sum of children's frequencies
        top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top); // Insert the new internal node back to heap
    }

    Node *root = extractMin(minHeap); // The last remaining node is the root
    delete minHeap;                   // Clean up the heap
    return root;
}

// Helper function for generating Huffman codes recursively
// Traverses the tree and builds the code for each character
void HuffmanTree::getCodesHelper(Node *root, std::string code,
                                 std::unordered_map<char, std::string> &codeMap)
{
    if (root == nullptr)
    {
        return;
    }

    // If we reach a leaf node, store the code for its character
    if (!root->left && !root->right)
    {
        codeMap[root->data] = code;
    }

    // Recursively traverse left (add '0' to code) and right (add '1' to code)
    getCodesHelper(root->left, code + "0", codeMap);
    getCodesHelper(root->right, code + "1", codeMap);
}

// Generates and returns Huffman codes for all characters in the tree
// Returns an unordered_map mapping characters to their Huffman codes
std::unordered_map<char, std::string> HuffmanTree::getCodes(Node *root)
{
    std::unordered_map<char, std::string> codeMap;
    getCodesHelper(root, "", codeMap); // Start with empty code at root
    return codeMap;
}