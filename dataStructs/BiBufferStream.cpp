#include "BibufferStream.h"

BiBufferStream::BiBufferStream(size_t bufferSize)
    : bufferSize(bufferSize), inputPos(0), outputPos(0), inputSize(0) {
    inputBuffer.resize(bufferSize);
    outputBuffer.resize(bufferSize);
}

void BiBufferStream::loadInput(ifstream& file) {
    file.read(inputBuffer.data(), bufferSize);
    inputSize = file.gcount();
    inputPos = 0; 
}

char BiBufferStream::fetchInput() {
    if (inputPos >= inputSize) throw out_of_range("Input buffer is empty");
    return inputBuffer[inputPos++];
}

void BiBufferStream::writeOutput(char c) {
    if (outputPos >= bufferSize) flushOutput(cout);
    outputBuffer[outputPos++] = c;
}

void BiBufferStream::flushOutput(std::ostream& stream) {
    stream.write(outputBuffer.data(), outputPos);
    outputPos = 0;
}

bool BiBufferStream::isInputEmpty() const {
    return inputPos >= inputSize;
}

bool BiBufferStream::isOutputFull() const {
    return outputPos >= bufferSize;
}