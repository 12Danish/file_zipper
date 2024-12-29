#include "RLE.h"

int main()
{
    string inputFile = "output.txt";
    string compressedFile = "compressed.rle";
    string decompressedFile = "decompressed.txt";

    // Process compression and decompression
    RLE<char>::compress_directory("/home/dan/Desktop/cpp/assignment", "/home/dan/Desktop/cpp/file_zipper/RLE/dir.rle");
    RLE<char>::decompress_directory("/home/dan/Desktop/cpp/file_zipper/RLE/dir.rle", "/home/dan/Desktop/cpp/");
    // RLE<char>::process_compression(inputFile, compressedFile);
    // RLE<char>::process_decompression(compressedFile, decompressedFile);

    return 0;
}
