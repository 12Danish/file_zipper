# Run-Length Encoding (RLE) Compression Algorithm

## Overview

Run-Length Encoding (RLE) is a simple compression algorithm that represents consecutive occurrences of the same data element as a single data value and a count. It is particularly useful for data that contains large sequences of repeating values.

### RLE Functions

The RLE algorithm is implemented through several key functions, each performing a specific task:

- **Compression (`rle_compress`)**: This function takes the input data and compresses it by storing each unique element and its count.
- **Decompression (`rle_decompress`)**: This function takes the compressed data and reconstructs the original data.
- **File I/O (`save_compressed_to_file`, `load_compressed_from_file`, etc.)**: These functions handle reading and writing compressed data to/from files.
- **Directory Compression/Decompression (`compress_directory`, `decompress_directory`)**: These functions handle the compression and decompression of files within directories, including recursive file exploration.

## Time and Space Complexity

### Time Complexity

The time complexity of the RLE algorithm depends on the size of the input data. In the worst case, we need to traverse through all elements in the data and count occurrences, making it **O(n)**, where **n** is the number of elements in the input data.

For directory compression and decompression, the time complexity becomes **O(n + m)**, where:

- **n** is the total number of files.
- **m** is the total size of all the files being processed.

### Space Complexity

The space complexity of RLE is also **O(n)**, as we need to store the compressed data in memory. The space required for storing the compressed data is proportional to the number of distinct data elements and their counts. For directories, additional space is required for storing file paths and content.

## Pros and Cons of RLE

### Pros:

1. **Efficient for Repetitive Data**: RLE is highly efficient when compressing data with long sequences of repeating elements, such as bitmap images or sequences of identical characters in text files.
2. **Simple to Implement**: RLE is easy to implement, requiring only basic iteration through the data and counting occurrences.
3. **Lossless Compression**: RLE is a lossless compression algorithm, meaning that the original data can be fully reconstructed from the compressed data.

### Cons:

1. **Ineffective for Distinct Data**: RLE performs poorly for data with little to no repetition. For example, compressing a sequence like `ABCDEF` would actually increase the size since each character is treated as a separate element with a count of 1.
2. **Limited Compression Ratio**: RLE offers limited compression benefits for datasets that don't have many long sequences of repeating elements.
3. **Storage Overhead**: For files with minimal repetition, RLE can result in larger file sizes due to the storage of counts and data values.

## When to Use RLE

- **Best for repetitive or predictable data**, like bitmap images, simple text with repeated characters, and sequences of similar items.
- **Not suitable for random or highly diverse data** where repetition is rare. In such cases, RLE may even lead to an increase in file size.

## Conclusion

RLE is a simple and effective compression technique for specific use cases, particularly where repetition is abundant. However, its utility diminishes when applied to data with high variability or no repeating patterns.
