#include "CustomVector.h"

template <typename T>
CustomVector<T>::CustomVector() : data(nullptr), size(0), capacity(0)
{
}

template <typename T>
CustomVector<T>::~CustomVector()
{
    delete[] data;
}

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

template <typename T>
void CustomVector<T>::append(const T &value)
{
    if (size == capacity)
    {
        this->resize();
    }

    data[size++] = value;
}

template <typename T>
void CustomVector<T>::remove_last()
{
    if (size > 0)
    {
        --size;
    }
}

template <typename T>
T &CustomVector<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t CustomVector<T>::getSize() const
{
    return size;
}

template <typename T>
size_t CustomVector<T>::getCapacity() const
{
    return capacity;
}
