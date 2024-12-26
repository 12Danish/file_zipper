#ifndef CUSTOM_MINHEAP_H
#define CUSTOM_MINHEAP_H
#include "CustomVector.h"
#include <stdexcept>

template <typename T>
class CustomMinHeap
{
private:
    CustomVector<T> heap;

    // Helper functions
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    // Constructors
    CustomMinHeap() = default; // Default constructor

    // Copy constructor
    CustomMinHeap(const CustomMinHeap &other);

    // Move constructor
    CustomMinHeap(CustomMinHeap &&other) noexcept;

    // Copy assignment operator
    CustomMinHeap &operator=(const CustomMinHeap &other);

    // Move assignment operator
    CustomMinHeap &operator=(CustomMinHeap &&other) noexcept;

    // Destructor
    ~CustomMinHeap() = default;

    // Core methods
    void push(const T &val);
    T pop();
    T top() const;
    bool empty() const;
    size_t size() const;
};

#include "CustomMinHeap.cpp"
#endif // CUSTOM_MINHEAP_H
