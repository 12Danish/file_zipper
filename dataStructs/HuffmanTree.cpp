#include "HuffmanTree.h"
#include <iostream>
#include <functional>

using namespace std;

HuffmanNode::HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}

bool CompareFrequency::operator()(HuffmanNode *a, HuffmanNode *b)
{
    return a->frequency > b->frequency;
}

HuffmanTree::HuffmanTree() : root(nullptr) {}

void HuffmanTree::build(const unordered_map<char, int> &frequencyMap)
{
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareFrequency> pq;

    for (const auto &pair : frequencyMap)
    {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();
        HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    root = pq.top();
}

void HuffmanTree::print() const
{
    function<void(HuffmanNode *, const string &)> printTree = [&](HuffmanNode *node, const string &prefix)
    {
        if (!node)
            return;
        if (node->data != '\0')
        {
            cout << prefix << " : " << node->data << endl;
        }
        printTree(node->left, prefix + "0");
        printTree(node->right, prefix + "1");
    };
    printTree(root, "");
}

HuffmanTree::~HuffmanTree()
{
    function<void(HuffmanNode *)> freeTree = [&](HuffmanNode *node)
    {
        if (!node)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    };
    freeTree(root);
}
