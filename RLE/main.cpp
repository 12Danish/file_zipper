#include "RLE.h"

int main()
{
    string inputFile = "input.txt";
    string compressedFile = "compressed.rle";
    string decompressedFile = "decompressed.txt";

    // Process compression and decompression
    RLE<char>::process_compression(inputFile, compressedFile);
    RLE<char>::process_decompression(compressedFile, decompressedFile);

    return 0;
}
