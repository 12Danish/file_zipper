#ifndef BIBUFFERSTREAM_H
#define BIBUFFERSTREAM_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class BiBufferStream {
private:
	vector<char> inputBuffer;
	vector<char> outputBuffer;
	size_t inputPos;
	size_t outputPos;
	size_t inputSize;
	size_t bufferSize;

public:
	BiBufferStream(size_t bufferSize);

	void loadInput(ifstream &file);

	char fetchInput();

	void writeOutput(char c);

	void flushOutput(ostream& stream);

	bool isInputEmpty() const;

	bool isOutputFull() const;
};


#endif 
