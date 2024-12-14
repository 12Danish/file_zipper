## _Documentation: Data Structures for FileZipper Project_

This document outlines the purpose and functionality of the data structures implemented for the FileZipper project. These data structures play a vital role in implementing efficient file compression and decompression algorithms.

---

### 1. _Sliding Window_

#### _Description:_

The SlidingWindow class is used to maintain a fixed-size buffer that "slides" through a sequence of data. It is primarily used in LZ77-based compression algorithms to identify repeated patterns within a defined window of recently processed data.

#### _Features:_

- Maintains a fixed-size circular buffer.
- Automatically removes the oldest data when new data exceeds the window size.
- Provides random access to elements within the window.

#### _Key Methods:_

- void add(char c): Adds a character to the sliding window, removing the oldest if the buffer is full.
- char get(size_t pos): Retrieves the character at the specified position within the window.
- void printWindow(): Prints the current contents of the window.

---

### 2. _BiBufferStream_

#### _Description:_

The BiBufferStream class is designed to facilitate buffered input and output for file compression. It supports reading data from an input file and writing it to an output file using a double-buffering mechanism.

#### _Features:_

- Efficiently handles file I/O using fixed-size buffers.
- Prevents frequent file system calls by buffering reads and writes.
- Supports flushing output to a file once the buffer is full.

#### _Key Methods:_

- void loadInput(std::ifstream& file): Loads data from an input file into the input buffer.
- char fetchInput(): Retrieves a single character from the input buffer.
- void writeOutput(char c): Writes a single character to the output buffer.
- void flushOutput(std::ostream& stream): Flushes the output buffer to the output file.

---

### 3. _Frequency Table_

#### _Description:_

The FrequencyTable class calculates and stores the frequency of characters in a given input dataset. It is essential for building encoding schemes like Huffman Coding, where character frequencies determine the encoding structure.

#### _Features:_

- Efficiently counts character frequencies using a hash map.
- Provides easy access to frequency data for encoding algorithms.

#### _Key Methods:_

- void calculateFrequency(const std::vector<char>& data): Computes the frequency of each character in the given data.
- void printFrequencyTable(): Prints the frequency of each character to the console.
- const std::unordered_map<char, int>& getFrequencyMap(): Retrieves the frequency map.

---

### 4. _Huffman Tree_

#### _Description:_

The HuffmanTree class represents a binary tree used for Huffman Coding. It is a fundamental structure for lossless data compression, where characters with higher frequencies are assigned shorter binary codes.

#### _Features:_

- Builds a binary tree based on character frequencies.
- Encodes characters into binary strings and decodes them efficiently.

#### _Key Methods:_

- void build(const std::unordered_map<char, int>& frequencyMap): Constructs the Huffman Tree from a frequency map.
- void print(): Prints the binary codes of each character in the tree.

---

### 5. _Bit Buffer_

#### _Description:_

The BitBuffer class manages bit-level operations for writing compressed data. Instead of writing individual bytes, this structure accumulates bits into a buffer and flushes them as complete bytes.

#### _Features:_

- Efficiently manages bit-level data.
- Writes compressed data bit by bit.
- Supports flushing incomplete bytes.

#### _Key Methods:_

- void writeBit(bool bit): Writes a single bit to the buffer.
- void flush(): Flushes any remaining bits as a complete byte.
- void printBuffer(): Prints the contents of the buffer as binary values.

---

### 6. _MatchFinder_

#### _Description:_

The MatchFinder class is used in LZ77 compression to find the longest matching substring in the sliding window for a given lookahead buffer. This helps encode repeated patterns efficiently.

#### _Features:_

- Identifies the longest match between the sliding window and the lookahead buffer.
- Returns the offset, length, and next character for the match.

#### _Key Methods:_

- Match findMatch(const std::string& window, const std::string& lookahead): Finds the longest match in the sliding window for the lookahead buffer.

#### _Associated Structure:_

- struct Match: Represents a match with fields for offset, length, and nextChar.

---

### 7. _LZW Dictionary_

#### _Description:_

The LZWDictionary class is used in LZW compression to map strings to unique codes and manage dynamic dictionary growth during compression. It supports efficient encoding and decoding of strings into shorter codes.

#### _Features:_

- Initializes with ASCII characters as the base dictionary.
- Dynamically adds new strings during compression.
- Provides efficient lookups and updates for string-to-code mappings.

#### _Key Methods:_

- LZWDictionary(): Initializes the dictionary with ASCII characters.
- bool contains(const std::string& key): Checks if a string exists in the dictionary.
- void addEntry(const std::string& key): Adds a new string to the dictionary with the next available code.
- int getCode(const std::string& key): Retrieves the code corresponding to a given string.

---

### _Purpose of Each Data Structure_

| Data Structure    | Purpose                                                                      |
| ----------------- | ---------------------------------------------------------------------------- |
| _Sliding Window_  | Maintains recent data for pattern matching in LZ77 compression.              |
| _BiBufferStream_  | Handles buffered file I/O for efficient data processing.                     |
| _Frequency Table_ | Computes character frequencies for building encoding trees like Huffman.     |
| _Huffman Tree_    | Encodes data into binary strings using Huffman Coding.                       |
| _Bit Buffer_      | Manages bit-level operations for writing compressed data.                    |
| _MatchFinder_     | Identifies repeated patterns for encoding in LZ77 compression.               |
| _LZW Dictionary_  | Maps strings to unique codes and dynamically updates during LZW compression. |

---

### _How to Use in the Project_

1. _Include the Header Files:_
   Add the required headers in your main file. For example:
   cpp
   #include "dataStructs/SlidingWindow.h"
   #include "dataStructs/BibufferStream.h"
   #include "dataStructs/FrequencyTable.h"
   #include "dataStructs/HuffmanTree.h"
   #include "dataStructs/BitBuffer.h"
   #include "dataStructs/MatchFinder.h"
   #include "dataStructs/LZWDictionary.h"

2. _Integrate into Compression Pipeline:_
   Use the data structures in sequence based on the compression algorithm (e.g., LZ77, Huffman, or LZW).

3. _Test Individually:_
   Test each data structure independently using the provided test cases to ensure correctness.

---

This documentation provides an overview of all the data structures, their roles in file compression, and their key functionalities. It ensures maintainability and reusability for future extensions or modifications.
