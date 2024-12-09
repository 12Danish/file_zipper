#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "dataStructs/SlidingWindow.h"
#include "dataStructs/BibufferStream.h"
#include "dataStructs/FrequencyTable.h"
#include "dataStructs/HuffmanTree.h"
#include "dataStructs/BitBuffer.h"
#include "dataStructs/MatchFinder.h"
#include "dataStructs/LZWDictionary.h"

using namespace std;

// Test SlidingWindow
void testSlidingWindow()
{
    slidingWindow window(5);
    window.add('A');
    window.add('B');
    window.add('C');
    window.printWindow(); // Output: ABC

    window.add('D');
    window.add('E');
    window.add('F');
    window.printWindow(); // Output: BCDEF (oldest data 'A' removed)

    cout << "Element at position 2: " << window.get(2) << endl; // Output: D
}

// Test BiBufferStream
void testBiBufferStream()
{
    const size_t bufferSize = 10;
    BiBufferStream bufferStream(bufferSize);

    // Simulate input
    ifstream inputFile("example.txt", ios::binary);
    if (!inputFile)
    {
        cerr << "Failed to open example.txt\n";
        return;
    }
    bufferStream.loadInput(inputFile);

    while (!bufferStream.isInputEmpty())
    {
        char c = bufferStream.fetchInput();
        bufferStream.writeOutput(c);
    }

    // Flush output to file
    ofstream outputFile("output_test.txt", ios::binary);
    bufferStream.flushOutput(outputFile);

    inputFile.close();
    outputFile.close();
    cout << "BiBufferStream test passed. Check output_test.txt.\n";
}

// Test FrequencyTable
void testFrequencyTable()
{
    FrequencyTable freqTable;
    vector<char> data = {'A', 'B', 'A', 'C', 'B', 'A'};
    freqTable.calculateFrequency(data);

    cout << "Frequency Table:\n";
    freqTable.printFrequencyTable();
}

// Test HuffmanTree
void testHuffmanTree()
{
    unordered_map<char, int> freqMap = {{'A', 5}, {'B', 3}, {'C', 2}};
    HuffmanTree huffmanTree;
    huffmanTree.build(freqMap);

    cout << "Huffman Tree:\n";
    huffmanTree.print();
}

// Test BitBuffer
void testBitBuffer()
{
    BitBuffer bitBuffer;

    // Write some bits
    bitBuffer.writeBit(1);
    bitBuffer.writeBit(0);
    bitBuffer.writeBit(1);
    bitBuffer.writeBit(1);
    bitBuffer.flush();

    cout << "Bit Buffer Contents:\n";
    bitBuffer.printBuffer(); // Should print the binary representation
}

// Test MatchFinder
void testMatchFinder()
{
    MatchFinder matchFinder;
    string window = "ABCDEF";
    string lookahead = "CDE";

    Match match = matchFinder.findMatch(window, lookahead);
    cout << "Match Found: Offset = " << match.offset << ", Length = " << match.length << ", Next Char = " << match.nextChar << endl;
}

// Test LZWDictionary
void testLZWDictionary()
{
    LZWDictionary dictionary;

    string input = "ABC";
    for (char c : input)
    {
        string str(1, c);
        if (!dictionary.contains(str))
        {
            dictionary.addEntry(str);
            cout << "Added: " << str << " with code " << dictionary.getCode(str) << endl;
        }
    }
}

// Main Function to Run All Tests
int main()
{
    cout << "Running tests...\n\n";

    cout << "Testing Sliding Window:\n";
    testSlidingWindow();
    cout << "\n";

    cout << "Testing BiBuffer Stream:\n";
    testBiBufferStream();
    cout << "\n";

    cout << "Testing Frequency Table:\n";
    testFrequencyTable();
    cout << "\n";

    cout << "Testing Huffman Tree:\n";
    testHuffmanTree();
    cout << "\n";

    cout << "Testing Bit Buffer:\n";
    testBitBuffer();
    cout << "\n";

    cout << "Testing Match Finder:\n";
    testMatchFinder();
    cout << "\n";

    cout << "Testing LZW Dictionary:\n";
    testLZWDictionary();
    cout << "\n";

    cout << "All tests completed successfully!\n";
    return 0;
}
