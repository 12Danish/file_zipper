#include <iostream>
#include "../dataStructs/CustomVector.h" // Include CustomVector.h from the dataStructs directory

int main()
{
    // Create a CustomVector of integers
    CustomVector<int> vec;

    // Test append function
    vec.append(10);
    vec.append(20);
    vec.append(30);

    // Print elements using operator[]
    for (size_t i = 0; i < vec.getSize(); ++i)
    {
        std::cout << "Element at index " << i << ": " << vec[i] << std::endl;
    }

    // Test remove_last function
    vec.remove_last();
    std::cout << "After removing last element, size: " << vec.getSize() << std::endl;

    // Print final elements after removal
    for (size_t i = 0; i < vec.getSize(); ++i)
    {
        std::cout << "Element at index " << i << ": " << vec[i] << std::endl;
    }

    return 0;
}
