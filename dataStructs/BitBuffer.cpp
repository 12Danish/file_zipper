#include "BitBuffer.h"
#include <bitset>

using namespace std;

BitBuffer::BitBuffer() : currentByte(0), bitPos(0) {}

void BitBuffer::writeBit(bool bit)
{
    if (bit)
    {
        currentByte |= (1 << (7 - bitPos));
    }
    bitPos++;
    if (bitPos == 8)
    {
        buffer.push_back(currentByte);
        currentByte = 0;
        bitPos = 0;
    }
}

void BitBuffer::flush()
{
    if (bitPos > 0)
    {
        buffer.push_back(currentByte);
    }
    currentByte = 0;
    bitPos = 0;
}

void BitBuffer::printBuffer() const
{
    for (uint8_t byte : buffer)
    {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;
}
