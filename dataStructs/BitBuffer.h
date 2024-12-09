#ifndef BIT_BUFFER_H
#define BIT_BUFFER_H

#include <vector>
#include <iostream>
#include <cstdint>

using namespace std;

class BitBuffer
{
private:
    vector<uint8_t> buffer;
    uint8_t currentByte;
    int bitPos;

public:
    BitBuffer();
    void writeBit(bool bit);
    void flush();
    void printBuffer() const;
};

#endif // BIT_BUFFER_H
