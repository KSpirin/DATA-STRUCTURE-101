#include <iostream>
#include <cassert>

// PROBLEM: Move Semantics - UniquePtr
// Copying is DELETED. You must implement MOVE only.

template <typename T>
class UniquePtr {
private:
    T* ptr;
public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}
    ~UniquePtr() { delete ptr; }

    // Copying is not allowed
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // TODO 1: Move Constructor
    // - Take ownership of other.ptr
    // - Set other.ptr to nullptr so it doesn't double-delete
    UniquePtr(UniquePtr&& other) noexcept {

    }

    // TODO 2: Move Assignment Operator
    // - Check self-assignment
    // - Delete current ptr, then steal other.ptr
    // - Set other.ptr to nullptr
    UniquePtr& operator=(UniquePtr&& other) noexcept {

        return *this;
    }

    T& operator*() const { return *ptr; }
    T* get() const { return ptr; }
};

int main() {
    UniquePtr<int> p1(new int(42));
    UniquePtr<int> p2(std::move(p1));     // Move Constructor
    assert(p1.get() == nullptr);           // p1 must be empty now
    assert(*p2 == 42);
    std::cout << "1_CPP Coding 2 Passed!" << std::endl;
    return 0;
}
