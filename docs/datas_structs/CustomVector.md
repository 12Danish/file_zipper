# `CustomVector` Class

The `CustomVector` class is a custom implementation of a dynamic array (similar to `std::vector` in C++). It allows efficient addition of elements, dynamic resizing, and provides typical vector-like operations such as element access and size querying.

## Class Definition

### Member Variables:

- **`data`**: A pointer to the array holding the vector's elements.
- **`size`**: The current number of elements in the vector.
- **`capacity`**: The total allocated space for the vector. This is increased when needed during resizing.

### Constructor and Destructor:

- **Default Constructor**: Initializes an empty vector with no allocated space.
- **Destructor**: Frees the memory used by the vector's data.

### Copy Constructor:

Creates a new vector as a copy of another vector.

### Copy Assignment Operator:

Assigns the contents of one vector to another, ensuring proper memory management and avoiding self-assignment.

### Resize:

Increases the vector's capacity when needed, doubling the current capacity. This ensures that the vector can hold more elements as it grows.

### `append`:

Adds a new element to the vector. If the vector is full, it automatically resizes.

### `remove_last`:

Removes the last element from the vector by reducing its size.

### Element Access:

- **`operator[]` (mutable)**: Provides direct access to the element at the given index, throwing an exception if the index is out of range.
- **`operator[]` (const)**: Provides const access to the element at the given index, throwing an exception if the index is out of range.

### Size and Capacity:

- **`getSize`**: Returns the current size of the vector (i.e., the number of elements).
- **`getCapacity`**: Returns the current capacity of the vector (i.e., the total allocated space).
- **`getData`**: Returns a pointer to the internal array.

## Time Complexities

| Operation                | Time Complexity                         |
| ------------------------ | --------------------------------------- |
| Default Constructor      | O(1)                                    |
| Destructor               | O(1)                                    |
| Copy Constructor         | O(n)                                    |
| Copy Assignment Operator | O(n)                                    |
| `resize`                 | O(n)                                    |
| `append`                 | O(1) amortized (O(n) in the worst case) |
| `remove_last`            | O(1)                                    |
| `operator[]` (mutable)   | O(1)                                    |
| `operator[]` (const)     | O(1)                                    |
| `getSize`                | O(1)                                    |
| `getCapacity`            | O(1)                                    |
| `getData` (mutable)      | O(1)                                    |
| `getData` (const)        | O(1)                                    |

## Description of Operations:

- **`append`**: The `append` operation inserts an element at the end of the vector. If the vector's capacity is reached, the `resize` function is called to double the capacity. The time complexity is **O(1)** for typical cases, but if resizing occurs, it takes **O(n)** time, where `n` is the number of elements in the vector.
- **`resize`**: The resizing operation allocates a new array with double the capacity and copies the existing elements. The time complexity is **O(n)**, where `n` is the number of elements in the vector.

- **`operator[]`**: Both the mutable and const versions of the subscript operator provide direct access to an element, which is an **O(1)** operation.

- **`remove_last`**: This operation reduces the size of the vector by one, which is an **O(1)** operation.

## Example Usage:

```cpp
CustomVector<int> vec;
vec.append(10);
vec.append(20);
vec.append(30);

std::cout << "Size: " << vec.getSize() << std::endl; // Output: 3
std::cout << "Element at index 1: " << vec[1] << std::endl; // Output: 20

vec.remove_last();
std::cout << "Size after removal: " << vec.getSize() << std::endl; // Output: 2
```
