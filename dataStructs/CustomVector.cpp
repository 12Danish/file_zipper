#include "CustomVector.h"
#include <iostream>

// Default constructor
template <typename T>
CustomVector<T>::CustomVector() : data(nullptr), size(0), capacity(0) {}

// Destructor
template <typename T>
CustomVector<T>::~CustomVector()
{
    delete[] data;
}

// Copy Constructor
template <typename T>
CustomVector<T>::CustomVector(const CustomVector &other)
    : size(other.size), capacity(other.capacity)
{
    data = new T[capacity];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

// Copy Assignment Operator
template <typename T>
CustomVector<T> &CustomVector<T>::operator=(const CustomVector &other)
{
    if (this != &other) // Avoid self-assignment
    {
        delete[] data; // Free existing memory
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Resize function to increase capacity
template <typename T>
void CustomVector<T>::resize()
{
    capacity = (capacity == 0) ? 1 : capacity * 2;

    T *newData = new T[capacity];

    for (size_t i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}

// Append an element to the vector
template <typename T>
void CustomVector<T>::append(const T &value)
{
    if (size == capacity)
    {
        resize();
    }

    // If data is null (uninitialized), allocate memory
    if (!data)
    {
        data = new T[capacity];
    }

    data[size++] = value;
}

// Remove the last element from the vector
template <typename T>
void CustomVector<T>::remove_last()
{
    if (size > 0)
    {
        --size;
    }
}

// Access an element at a given index (mutable)
template <typename T>
T &CustomVector<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Access an element at a given index (const version)
template <typename T>
const T &CustomVector<T>::operator[](size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Get the current size of the vector
template <typename T>
size_t CustomVector<T>::getSize() const
{
    return size;
}

// Get the current capacity of the vector
template <typename T>
size_t CustomVector<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
T *CustomVector<T>::getData()
{
    return data;
}

template <typename T>
const T *CustomVector<T>::getData() const
{
    return data;
}