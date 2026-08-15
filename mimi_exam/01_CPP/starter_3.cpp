#include <iostream>
#include <cassert>

// PROBLEM: Custom Iterator
// Make the range-based for loop `for (int val : container)` work
// by implementing the 3 iterator operators below.

class IntContainer {
private:
    int data[5];
public:
    IntContainer() {
        for(int i = 0; i < 5; ++i) data[i] = i * 10;  // {0, 10, 20, 30, 40}
    }

    class Iterator {
    private:
        int* ptr;
    public:
        Iterator(int* p) : ptr(p) {}

        // TODO 1: operator* — return the value the iterator points to
        int& operator*() {

        }

        // TODO 2: operator++ (prefix) — move iterator to next element, return *this
        Iterator& operator++() {

            return *this;
        }

        // TODO 3: operator!= — return true if iterators point to different locations
        bool operator!=(const Iterator& other) const {

        }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end()   { return Iterator(data + 5); }
};

int main() {
    IntContainer container;
    int sum = 0;
    for (int val : container) sum += val;
    assert(sum == 100);  // 0 + 10 + 20 + 30 + 40 = 100
    std::cout << "1_CPP Coding 3 Passed!" << std::endl;
    return 0;
}
