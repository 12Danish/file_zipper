# File Cmpression Project

A C++ implementation of a file compression system that leverages both Run-Length Encoding (RLE) and Huffman compression algorithms to compress individual text files and directories efficiently(As of now RLE can perform directory compression/zipping).

## Features

- **Dual Compression Algorithms**
  - Run-Length Encoding (RLE) for repetitive sequences
  - Huffman Coding for optimal bit-level compression
- **Flexible Input Support**
  - Single file compression
  - Directory-wide compression
- **Custom Data Structures**
  - Optimized implementations of core data structures
  - Memory-efficient operations

## Directory Structure

```
project_root/
├── dataStructs/
│   ├── CustomMinHeap.cpp     # Min heap for Huffman tree
│   ├── CustomMinHeap.h
│   ├── CustomVector.cpp      # Custom vector implementation
│   └── CustomVector.h
├── HEC/
│   ├── c_huffmanAlgo.cpp     # Huffman compression logic
│   └── c_huffman.hpp
├── RLE/            # RLE compression program
│   ├── RLE.h                # RLE algorithm header
│   └── RLE.tpp             # RLE template implementation
├── main.cpp                 # Main program entry point
```

## Requirements

- C++ compiler with C++17 support
- CMake (version 3.10 or higher)
- Standard Template Library (STL)
- Unix-like environment (Linux/MacOS) or Windows with MinGW

## Build Instructions

1. Clone the repository

2. Create and navigate to build directory

3. Generate build files

4. Compile the project

## Running the Program

The entry point for the program is main.cpp, run it to run the application.

## Documentation

For detailed documentation about the data structures, algorithms, implementation details please view the following urls:

### Data Structures:

[CustomVector](https://github.com/12Danish/file_zipper/blob/main/docs/datas_structs/CustomVector.md)

[CustomMinHeap](https://github.com/12Danish/file_zipper/blob/main/docs/datas_structs/CustomMinHeap.md)

### Algorithms

[RLE](https://github.com/12Danish/file_zipper/blob/main/docs/Algorithms/RLE.md)

[HEC](https://github.com/12Danish/file_zipper/blob/main/docs/Algorithms/HEC.md)
