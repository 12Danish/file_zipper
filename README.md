# File Compression System

A C++ implementation of a file compression system that leverages both Run-Length Encoding (RLE) and Huffman compression algorithms to compress individual text files and directories efficiently.

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

```bash
git clone https://github.com/yourusername/compression-system.git
cd compression-system
```

2. Create and navigate to build directory

```bash
mkdir build
cd build
```

3. Generate build files

```bash
cmake ..
```

4. Compile the project

```bash
make
```

## Running the Program

[Instructions for running the program will be added]

## Documentation

For detailed documentation about the algorithms, implementation details, and API references, visit our [Documentation Page][doc-link].

[doc-link]: # "Documentation link to be added"
