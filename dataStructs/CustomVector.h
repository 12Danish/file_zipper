#ifndef CUSTOM_VECTOR_H // Include guard
#define CUSTOM_VECTOR_H

#include <cstddef>   // for size_t
#include <stdexcept> // for exceptions like out_of_range

template <typename T>
class CustomVector
{
private:
    T *data;         // Pointer to the underlying array
    size_t size;     // Current number of elements
    size_t capacity; // Current capacity of the array

    // Resize the array when capacity is exceeded
    void resize();

public:
    // Default constructor
    CustomVector();

    // Destructor

    // Copy Constructor
    CustomVector(const CustomVector &other);

    // Copy Assignment Operator
    CustomVector &operator=(const CustomVector &other);

    // Destructor
    ~CustomVector();

    // Add an element to the end
    void append(const T &value);

    // Remove the last element
    void remove_last();

    // Access element at a specific index (mutable)
    T &operator[](size_t index);

    // Access element at a specific index (const)
    const T &operator[](size_t index) const;

    // Get the current size
    size_t getSize() const;

    // Get the current capacity
    size_t getCapacity() const;

    T *getData();

    const T *getData() const;
};

// Include the source file for template implementation
#include "CustomVector.cpp"

#endif // CUSTOM_VECTOR_H
