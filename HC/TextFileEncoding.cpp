
#include "../dataStructs/HuffmanTree.h" // Include CustomVector.h from the dataStructs directory
using namespace std;

// Class for generating Huffman codes using the HuffmanTree class
class HuffmanCoding
{
private:
    HuffmanTree tree;

public:
    // Function to generate and print Huffman codes
    void generateCodes(char data[], int freq[], int size)
    {
        HuffmanTree::Node *root = tree.buildHuffmanTree(data, freq, size);

        // Get the actual height of the tree
        int treeHeight = HuffmanTree::getTreeHeight(root);
        int *arr = new int[treeHeight]; // Dynamically allocate array based on actual height

        cout << "Tree Height: " << treeHeight << endl;
        cout << "Huffman Codes:\n";
        tree.printCodes(root, arr, 0);

        delete[] arr; // Free the dynamically allocated memory
        delete root;  // Free the memory for the root of the tree
    }
};

int main()
{
    // Example data and frequency for Huffman Coding
    char arr[] = {'u', 'b', 'c', 'd', 'e', 'f', 'x'};
    int freq[] = {5, 9, 12, 13, 16, 45, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCoding huffman;
    huffman.generateCodes(arr, freq, size); // Generate and print the Huffman codes

    return 0;
}
