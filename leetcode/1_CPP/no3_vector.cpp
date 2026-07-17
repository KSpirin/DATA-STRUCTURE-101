/**
 * @file no3_template_vector.cpp
 * @brief Custom Templated Vector Class (Implementing std::vector with Rule of 5)
 * @difficulty Medium / System Design
 * @link N/A (Standard Data Structure Implementation)
 */

/*
--------------------------------------------------------------------------------
PROBLEM DESCRIPTION
--------------------------------------------------------------------------------
Design and implement a custom templated dynamic array class (like std::vector in C++).
The class must support:
1. Dynamic resizing when capacity is reached (typically doubling).
2. Proper resource management using the C++ Rule of 5:
   - Destructor (releases heap-allocated memory).
   - Copy Constructor (deep copy).
   - Copy Assignment Operator (deep copy with self-assignment protection).
   - Move Constructor (efficient resource transfer).
   - Move Assignment Operator (efficient resource transfer, avoiding leaks).
3. Accessors and Mutators:
   - Elements access using operator[] (unchecked) and at() (checked, throws out_of_range).
   - size(), capacity(), empty(), reserve(), clear(), push_back(), pop_back().
--------------------------------------------------------------------------------
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>

template <typename T>
class Vector {
private:
    T* data_;         // Pointer to the heap-allocated array
    size_t size_;     // Number of active elements currently in the vector
    size_t capacity_; // Total allocation capacity of the dynamic array

public:
    // ---------------------------------------------------------
    // 1. CONSTRUCTORS & DESTRUCTOR
    // ---------------------------------------------------------

    /**
     * @brief Default constructor. Initializes an empty vector.
     */
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief Constructor with an initial capacity.
     * @param init_capacity The initial capacity to reserve.
     */
    explicit Vector(size_t init_capacity) 
        : data_(new T[init_capacity]), size_(0), capacity_(init_capacity) {}

    /**
     * @brief Destructor (Rule of 5 #1). Cleans up heap-allocated dynamic array.
     */
    ~Vector() {
        delete[] data_;
    }

    // ---------------------------------------------------------
    // 2. THE RULE OF 5: COPY & MOVE OPERATIONS
    // ---------------------------------------------------------

    /**
     * @brief Copy Constructor (Rule of 5 #2). Performs a deep copy of elements.
     * @param other The vector to copy from.
     */
    Vector(const Vector& other) 
        : data_(other.capacity_ > 0 ? new T[other.capacity_] : nullptr), 
          size_(other.size_), 
          capacity_(other.capacity_) {
        // Deep copy each element
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    /**
     * @brief Copy Assignment Operator (Rule of 5 #3).
     * Uses copy-and-swap idiom to ensure strong exception safety.
     * @param other The vector to assign.
     * @return Reference to this vector.
     */
    Vector& operator=(const Vector& other) {
        if (this != &other) { // Guard clause: Protect against self-assignment
            // Create a temporary copy of other
            Vector temp(other);
            // Swap resources of temp and *this
            swap(temp);
        }
        return *this;
    }

    /**
     * @brief Move Constructor (Rule of 5 #4). Transfers ownership of resources.
     * @param other The rvalue reference to move from.
     */
    Vector(Vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        // Leave the source object in a valid, empty state
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /**
     * @brief Move Assignment Operator (Rule of 5 #5).
     * Reclaims current resources and transfers ownership from the source.
     * @param other The rvalue reference to assign.
     * @return Reference to this vector.
     */
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) { // Guard clause: Protect against self-assignment
            // Free current memory
            delete[] data_;

            // Steal resources
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            // Nullify other's members to prevent double-deletion
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // ---------------------------------------------------------
    // 3. SWAP HELPER
    // ---------------------------------------------------------
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // ---------------------------------------------------------
    // 4. ELEMENT ACCESS
    // ---------------------------------------------------------

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) { // Guard clause: range check
            throw std::out_of_range("Vector::at() - index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) { // Guard clause: range check
            throw std::out_of_range("Vector::at() - index out of range");
        }
        return data_[index];
    }

    // ---------------------------------------------------------
    // 5. CAPACITY & UTILITIES
    // ---------------------------------------------------------

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        size_ = 0; // Logically clears the elements. Capacity is kept.
    }

    /**
     * @brief Reserves memory to ensure vector has at least the specified capacity.
     * @param new_cap The new capacity to request.
     */
    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) {
            return; // Guard clause: do nothing if capacity is already sufficient
        }

        // Allocate a new array of requested size
        T* new_data = new T[new_cap];
        
        // Copy existing elements to the new array
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        // Delete old array
        delete[] data_;

        // Update state
        data_ = new_data;
        capacity_ = new_cap;
    }

    // ---------------------------------------------------------
    // 6. MODIFIERS
    // ---------------------------------------------------------

    /**
     * @brief Inserts an element at the end of the vector.
     * Doubles capacity dynamically if capacity is reached.
     * @param value The value to append.
     */
    void push_back(const T& value) {
        if (size_ == capacity_) {
            // Compute new capacity (double it, or set to 1 if empty)
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        data_[size_] = value;
        ++size_;
    }

    /**
     * @brief Inserts an rvalue element at the end of the vector (move overload).
     */
    void push_back(T&& value) {
        if (size_ == capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(new_cap);
        }
        data_[size_] = std::move(value);
        ++size_;
    }

    /**
     * @brief Removes the last element from the vector.
     */
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }
};

/*
--------------------------------------------------------------------------------
DRY-RUN TRACE: VECTOR DYNAMIC EXPANSION AND RULE OF 5
--------------------------------------------------------------------------------
Scenario:
Vector<int> v;
v.push_back(10);
v.push_back(20);
Vector<int> copy_v = v; // Copy constructor

Step-by-step Trace:
1. `Vector<int> v;`
   - Initializes v with data_ = nullptr, size_ = 0, capacity_ = 0.

2. `v.push_back(10);`
   - Checks size_ == capacity_ (0 == 0). True.
   - new_cap = (capacity_ == 0) ? 1 : 0*2 = 1.
   - Calls `v.reserve(1)`.
     - Allocates `new_data` = `new int[1]`.
     - `delete[] nullptr` (safe operation).
     - v.data_ now points to heap array size 1. v.capacity_ = 1.
   - v.data_[0] = 10;
   - v.size_ becomes 1.

3. `v.push_back(20);`
   - Checks size_ == capacity_ (1 == 1). True.
   - new_cap = capacity_ * 2 = 2.
   - Calls `v.reserve(2)`.
     - Allocates `new_data` = `new int[2]`.
     - Copies element: new_data[0] = std::move(v.data_[0]) (value 10).
     - Deletes old data_ array.
     - v.data_ now points to new heap array size 2. v.capacity_ = 2.
   - v.data_[1] = 20;
   - v.size_ becomes 2.

4. `Vector<int> copy_v = v;` (Copy Constructor)
   - Checks if other.capacity_ (2) > 0. True. Allocates `new int[2]`.
   - Sets copy_v.size_ = 2, copy_v.capacity_ = 2.
   - Loops from 0 to 1:
     - copy_v.data_[0] = v.data_[0] (10)
     - copy_v.data_[1] = v.data_[1] (20)
   - Resources are duplicated. Changes to `copy_v` do not affect `v`.

--------------------------------------------------------------------------------
COMPLEXITY ANALYSIS
--------------------------------------------------------------------------------
Time Complexity:
- push_back(): Amortized O(1). Resizing (which takes O(N) time) occurs only
  when size equals capacity. By doubling capacity, resizing happens exponentially
  infrequently.
- pop_back(): O(1). Merely decrements the size index.
- Access (operator[] and at()): O(1). Direct memory address computation.
- Copy Constructor / Assignment: O(N) to duplicate N elements.
- Move Constructor / Assignment: O(1) as it only transfers pointers.

Space Complexity:
- O(N) where N is the capacity of the vector, representing the heap storage.
--------------------------------------------------------------------------------
*/

int main() {
    try {
        std::cout << "--- 1. Testing Insertion and Growth ---" << std::endl;
        Vector<int> v;
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);

        std::cout << "v size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << "v[" << i << "] = " << v[i] << std::endl;
        }

        std::cout << "\n--- 2. Testing Copy Constructor ---" << std::endl;
        Vector<int> copy_v = v;
        copy_v[0] = 999;
        std::cout << "Original v[0] (should be 10): " << v[0] << std::endl;
        std::cout << "Copied copy_v[0] (should be 999): " << copy_v[0] << std::endl;

        std::cout << "\n--- 3. Testing Copy Assignment ---" << std::endl;
        Vector<int> assign_v;
        assign_v = v;
        std::cout << "assign_v[1] (should be 20): " << assign_v[1] << std::endl;

        std::cout << "\n--- 4. Testing Move Constructor ---" << std::endl;
        Vector<int> moved_v = std::move(v);
        std::cout << "moved_v size: " << moved_v.size() << std::endl;
        std::cout << "moved_v[2] (should be 30): " << moved_v[2] << std::endl;
        std::cout << "Is original v empty now? " << (v.empty() ? "Yes" : "No") << std::endl;

        std::cout << "\n--- 5. Testing Move Assignment ---" << std::endl;
        Vector<int> moved_assign_v;
        moved_assign_v = std::move(moved_v);
        std::cout << "moved_assign_v[0]: " << moved_assign_v[0] << std::endl;

        std::cout << "\n--- 6. Testing Exception Handling via at() ---" << std::endl;
        std::cout << "Accessing invalid index 10:" << std::endl;
        std::cout << moved_assign_v.at(10) << std::endl;

    } catch (const std::out_of_range& e) {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
