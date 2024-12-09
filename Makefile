# Compiler and flags
CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g

# Source files and target
SRC = FileZipper.cpp \
      dataStructs/BiBufferStream.cpp \
      dataStructs/FrequencyTable.cpp \
      dataStructs/BitBuffer.cpp \
      dataStructs/HuffmanTree.cpp \
      dataStructs/LZWDictionary.cpp \
      dataStructs/MatchFinder.cpp \
      dataStructs/SlidingWindow.cpp
TARGET = FileZipper

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean up
clean:
	rm -f $(TARGET)
