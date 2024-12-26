#include "CustomMinHeap.h"
#include <utility> // For std::move

// Copy constructor
template <typename T>
CustomMinHeap<T>::CustomMinHeap(const CustomMinHeap &other) : heap(other.heap) {}

// Move constructor
template <typename T>
CustomMinHeap<T>::CustomMinHeap(CustomMinHeap &&other) noexcept : heap(std::move(other.heap)) {}

// Copy assignment operator
template <typename T>
CustomMinHeap<T> &CustomMinHeap<T>::operator=(const CustomMinHeap &other)
{
    if (this != &other)
    {
        heap = other.heap;
    }
    return *this;
}

// Move assignment operator
template <typename T>
CustomMinHeap<T> &CustomMinHeap<T>::operator=(CustomMinHeap &&other) noexcept
{
    if (this != &other)
    {
        heap = std::move(other.heap);
    }
    return *this;
}

// Heapify up
template <typename T>
void CustomMinHeap<T>::heapifyUp(int index)
{
    while (index != 0 && heap[parent(index)] > heap[index])
    {
        std::swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

// Heapify down
template <typename T>
void CustomMinHeap<T>::heapifyDown(int index)
{
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.getSize() && heap[left] < heap[smallest])
    {
        smallest = left;
    }

    if (right < heap.getSize() && heap[right] < heap[smallest])
    {
        smallest = right;
    }

    if (smallest != index)
    {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

// Push a new value onto the heap
template <typename T>
void CustomMinHeap<T>::push(const T &val)
{
    heap.append(val);
    heapifyUp(heap.getSize() - 1);
}

// Pop the top value from the heap
template <typename T>
T CustomMinHeap<T>::pop()
{
    if (heap.getSize() == 0)
    {
        throw std::underflow_error("Heap is empty");
    }

    T root = heap[0];
    heap[0] = heap[heap.getSize() - 1];
    heap.remove_last();

    heapifyDown(0);
    return root;
}

// Peek at the top value without removing it
template <typename T>
T CustomMinHeap<T>::top() const
{
    if (heap.getSize() == 0)
    {
        throw std::underflow_error("Heap is empty");
    }
    return heap[0];
}

// Check if the heap is empty
template <typename T>
bool CustomMinHeap<T>::empty() const
{
    return heap.getSize() == 0;
}

// Get the size of the heap
template <typename T>
size_t CustomMinHeap<T>::size() const
{
    return heap.getSize();
}
