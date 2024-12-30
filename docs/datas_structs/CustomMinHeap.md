# CustomMinHeap Data Structure

`CustomMinHeap` is a template-based implementation of a Min Heap, where each parent node is less than or equal to its child nodes. This heap is built upon a custom vector (`CustomVector`) which provides dynamic array capabilities.

### Operations and Time Complexity

1. **Constructor and Assignment Operators**

   - **Copy Constructor**:
     - Copies all elements from another `CustomMinHeap` into the new instance.
     - Time Complexity: **O(n)**, where `n` is the number of elements in the heap.
   - **Move Constructor**:
     - Transfers ownership of the heap to the new instance.
     - Time Complexity: **O(1)**.
   - **Copy Assignment Operator**:
     - Copies elements from one `CustomMinHeap` to another.
     - Time Complexity: **O(n)**.
   - **Move Assignment Operator**:
     - Moves elements from one heap to another.
     - Time Complexity: **O(1)**.

2. **Heapify Operations**

   - **heapifyUp(index)**:
     - Moves an element at the given index up to maintain the heap property.
     - Time Complexity: **O(log n)**, where `n` is the number of elements in the heap.
   - **heapifyDown(index)**:
     - Moves an element at the given index down to maintain the heap property.
     - Time Complexity: **O(log n)**, where `n` is the number of elements in the heap.

3. **Push Operation**

   - **push(val)**:
     - Adds a new element to the heap and restores the heap property by calling `heapifyUp`.
     - Time Complexity: **O(log n)**, where `n` is the number of elements in the heap.

4. **Pop Operation**

   - **pop()**:
     - Removes the top element of the heap (the smallest element) and restores the heap property by calling `heapifyDown`.
     - Time Complexity: **O(log n)**, where `n` is the number of elements in the heap.

5. **Peek Operation**

   - **top()**:
     - Returns the top element of the heap (the smallest element) without removing it.
     - Time Complexity: **O(1)**.

6. **Size and Empty Checks**
   - **empty()**:
     - Returns `true` if the heap is empty, otherwise returns `false`.
     - Time Complexity: **O(1)**.
   - **size()**:
     - Returns the number of elements in the heap.
     - Time Complexity: **O(1)**.

### Summary of Time Complexities

| Operation        | Time Complexity |
| ---------------- | --------------- |
| Copy Constructor | O(n)            |
| Move Constructor | O(1)            |
| Copy Assignment  | O(n)            |
| Move Assignment  | O(1)            |
| `heapifyUp`      | O(log n)        |
| `heapifyDown`    | O(log n)        |
| `push`           | O(log n)        |
| `pop`            | O(log n)        |
| `top`            | O(1)            |
| `empty`          | O(1)            |
| `size`           | O(1)            |
