# Huffman Coding Algorithm

Huffman coding is an optimal algorithm for lossless data compression. It assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters, making the overall encoded file smaller.

## Function Descriptions

### 1. **createArr()**

Initializes an array of size 128, where each element corresponds to a character (ASCII values 0-127), and each element is an object of type `Node` initialized with a frequency of 0.

### 2. **traverse(Node \*r, string str)**

Traverses the Huffman tree and assigns a binary code (as a string) to each leaf node (character).

### 3. **binToDec(string inStr)**

Converts a binary string into its decimal equivalent.

### 4. **decToBin(int inNum)**

Converts a decimal integer to its binary string representation, ensuring the result is 8 bits long by padding with leading zeros if necessary.

### 5. **buildTree(char a_code, string &path)**

Builds the Huffman tree by following the path (a string of '0' and '1' characters) from the root.

### 6. **createMinHeap()**

Reads the input file, counts the frequency of each character, and constructs a priority queue (min-heap) of `Node` objects.

### 7. **createTree()**

Constructs the Huffman tree by repeatedly extracting the two nodes with the lowest frequencies from the min-heap and creating a new internal node with these nodes as children.

### 8. **createCodes()**

Generates Huffman codes for all the characters by traversing the Huffman tree and assigning binary codes to each leaf node.

### 9. **saveEncodedFile()**

Encodes the input file using the Huffman tree and saves the encoded data in a binary format.

### 10. **saveDecodedFile()**

Decodes a Huffman encoded file using the Huffman tree and saves the reconstructed data to an output file.

### 11. **getTree()**

Reconstructs the Huffman tree by reading the metadata from the encoded file and building the tree accordingly.

### 12. **compress()**

Combines the steps of creating the min-heap, building the tree, generating the codes, and saving the encoded file.

### 13. **decompress()**

Reconstructs the tree from the encoded file and decodes it to reconstruct the original data.

---

## Overall Time and Space Complexity

**Time Complexity:**  
The overall time complexity of the Huffman coding algorithm is dominated by the process of creating the Huffman tree and encoding/decoding the file.  
**Total Time Complexity:** O(m + n log n)  
Where m is the number of characters in the input file, and n is the number of unique characters.

**Space Complexity:**  
The space complexity is dominated by the storage of the Huffman tree, the input file, and the encoded data.  
**Total Space Complexity:** O(m + n)

---

## Pros and Cons

### Pros:

- **Optimality:** Huffman coding provides the optimal compression for a given set of characters and their frequencies.
- **Lossless Compression:** It is a lossless algorithm, meaning the original data can be perfectly reconstructed.
- **Efficient:** The algorithm is efficient in both time and space, especially for small to medium-sized files.

### Cons:

- **Not Ideal for Small Data:** For very small datasets, the overhead of storing the Huffman tree may outweigh the benefits of compression.
- **Single-pass Compression:** The algorithm requires a second pass over the data during encoding and decoding, which may not be as efficient for streaming applications.
- **Static Nature:** The algorithm assumes the frequency distribution of the data is known beforehand. If the data distribution changes, the tree needs to be rebuilt.

---

## Conclusion

Huffman coding is a widely used and effective algorithm for lossless data compression. Its simplicity and optimality make it suitable for a variety of applications, from file compression to network data transmission. However, it is not always the most efficient for small datasets or dynamic data streams.
