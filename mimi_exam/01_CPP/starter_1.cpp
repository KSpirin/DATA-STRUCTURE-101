#include <iostream>
#include <cassert>

// PROBLEM: Rule of 3 - DynamicArray
// You must implement 3 special member functions so the array manages memory safely.

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;
public:
    DynamicArray(size_t cap = 10) : capacity(cap), size(0) {
        data = new T[capacity];
    }

    // TODO 1: Destructor
    // - Free the heap-allocated `data` array
    ~DynamicArray() {

    }

    // TODO 2: Copy Constructor
    // - Allocate NEW memory (deep copy, not shallow)
    // - Copy each element from `other` into the new array
    DynamicArray(const DynamicArray& other) {

    }

    // TODO 3: Copy Assignment Operator
    // - Check for self-assignment (this != &other)
    // - Delete old memory, then deep copy from `other`
    DynamicArray& operator=(const DynamicArray& other) {

        return *this;
    }

    void push_back(const T& val) {
        if (size == capacity) {
            capacity *= 2;
            T* new_data = new T[capacity];
            for (size_t i = 0; i < size; ++i) new_data[i] = data[i];
            delete[] data;
            data = new_data;
        }
        data[size++] = val;
    }
    T& at(size_t index) { return data[index]; }
    size_t getSize() const { return size; }
};

int main() {
    DynamicArray<int> arr1(5);
    arr1.push_back(10);
    DynamicArray<int> arr2 = arr1;        // calls Copy Constructor
    assert(arr2.at(0) == 10);
    DynamicArray<int> arr3;
    arr3 = arr2;                           // calls Copy Assignment
    assert(arr3.at(0) == 10);
    std::cout << "1_CPP Coding 1 Passed!" << std::endl;
    return 0;
}
