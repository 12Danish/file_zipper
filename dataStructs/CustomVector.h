#ifndef CUSTOM_VECTOR_H // Include guard
#define CUSTOM_VECTOR_H

#include <cstddef>   // for size_t
#include <stdexcept> // for exceptions like out_of_range

template <typename T>
class CustomVector
{
private:
    T *data;
    size_t size;
    size_t capacity;

    void resize();

public:
    // Constructor
    CustomVector();

    // Destructor
    ~CustomVector();

    // Add an element to the end
    void append(const T &value);

    // Remove the last element
    void remove_last();

    // Access element at a specific index
    T &operator[](size_t index);

    const T &operator[](size_t index) const;

    // Get the current size
    size_t getSize() const;

    // Get the current capacity
    size_t getCapacity() const;
};

#include "CustomVector.cpp" // Include the source file for template implementation

#endif // CUSTOM_VECTOR_H
