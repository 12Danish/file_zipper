// FileZipper.cpp : Defines the entry point for the application.
//

#include "FileZipper.h"
#include "dataStructs/SlidingWindow.h"
#include "dataStructs/BibufferStream.h"

using namespace std;

int main()
{
    // slidingWindow window(5);
    //   window.add('A');
    //   window.add('B');
    //   window.add('C');
    //   window.printWindow(); // Output: ABC

    //   window.add('D');
    //   window.add('E');
    //   window.add('F');
    //   window.printWindow(); // Output: BCDEF (oldest data 'A' removed)

    //   cout << "Element at position 2: " << window.get(2) << endl; // Output: D

    const size_t bufferSize = 100; // Define buffer size
    BiBufferStream bufferStream(bufferSize);

    // Open input file for reading
    ifstream inputFile("/home/dan/Desktop/cpp/file_zipper/example.txt", ios::binary);
    if (!inputFile)
    {
        cerr << "Failed to open input file.\n";
        return 1;
    }

    // Open output file for writing
    ofstream outputFile("/home/dan/Desktop/cpp/file_zipper/output.txt", ios::binary);
    if (!outputFile)
    {
        cerr << "Failed to open output file.\n";
        return 1;
    }

    // Load input data into the input buffer
    bufferStream.loadInput(inputFile);

    // Process input buffer and write to the output buffer
    while (!bufferStream.isInputEmpty())
    {
        char c = bufferStream.fetchInput(); // Fetch character from input buffer
        bufferStream.writeOutput(c);        // Write character to output buffer
    }

    // Flush remaining data in the output buffer
    bufferStream.flushOutput(outputFile);

    // Close files
    inputFile.close();
    outputFile.close();

    cout << "Data successfully read from 'example.txt' and written to 'output.txt'.\n";

    return 0;
}
