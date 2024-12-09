#ifndef SLIDINGWINDOW_H
#define SLIDINGWINDOW_H

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class slidingWindow {
private:
    vector<char> buffer; 
    size_t size;             
    size_t start;            
    size_t currentSize;      

public:

    slidingWindow(size_t maxSize);

    void add(char c);

    char get(size_t pos) const;

    size_t getCurrentSize() const;

    void printWindow() const;
};

#endif 
