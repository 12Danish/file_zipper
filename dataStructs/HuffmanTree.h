#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char d, int freq);
};

struct CompareFrequency
{
    bool operator()(HuffmanNode *a, HuffmanNode *b);
};

class HuffmanTree
{
private:
    HuffmanNode *root;

public:
    HuffmanTree();
    void build(const unordered_map<char, int> &frequencyMap);
    void print() const;
    ~HuffmanTree();
};

#endif // HUFFMAN_TREE_H
