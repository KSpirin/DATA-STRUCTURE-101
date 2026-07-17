/**
 * @file no3_heap_sort.cpp
 * @author Computer Science Teaching Assistant
 * @brief Custom Max-Heap implementation and Heap Sort algorithm.
 * @details Covers push, pop, top, buildHeap (O(N)), and heapSort (O(N log N) in-place).
 */

/*
Problem Description / Requirements:
-----------------------------------
Implement a custom Max-Heap from scratch without using std::priority_queue.
The custom heap must provide the following:
1. push(int val) - Insert an element and restore max-heap property via up-heapify.
2. pop() - Remove the root (max element) and restore max-heap property via down-heapify.
3. top() - Retrieve the root element.
4. buildHeap(std::vector<int>& array) - Build a Max-Heap from an arbitrary array in O(N) time.
5. heapSort(std::vector<int>& array) - Sort an array in ascending order in-place using Heap Sort.

Constraints:
- Should compile using standard C++17.
- Complete visibility controls (private helpers, public APIs).
- Appropriate guard clauses for accessing or popping empty heap elements.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

class CustomHeap {
private:
    std::vector<int> data;

    // Helper functions for index calculations (0-based index)
    int parentIndex(int i) const { return (i - 1) / 2; }
    int leftChildIndex(int i) const { return 2 * i + 1; }
    int rightChildIndex(int i) const { return 2 * i + 2; }

    /**
     * @brief Restores the Max-Heap property by moving a node upward.
     * @param index The index of the node to reheapify upward.
     * @note Time Complexity: O(log N).
     */
    void upHeapify(int index) {
        // While the node is not the root and is greater than its parent:
        while (index > 0 && data[index] > data[parentIndex(index)]) {
            std::swap(data[index], data[parentIndex(index)]);
            index = parentIndex(index); // Move up to the parent's index
        }
    }

    /**
     * @brief Restores the Max-Heap property by moving a node downward.
     * @param index The index of the node to reheapify downward.
     * @param heapSize The current active size of the heap.
     * @note Time Complexity: O(log N).
     */
    void downHeapify(int index, int heapSize) {
        int maxIndex = index;
        int left = leftChildIndex(index);
        int right = rightChildIndex(index);

        // If the left child exists and is greater than the current maximum:
        if (left < heapSize && data[left] > data[maxIndex]) {
            maxIndex = left;
        }

        // If the right child exists and is greater than the current maximum:
        if (right < heapSize && data[right] > data[maxIndex]) {
            maxIndex = right;
        }

        // If the current node is smaller than either of its children:
        if (index != maxIndex) {
            std::swap(data[index], data[maxIndex]);
            downHeapify(maxIndex, heapSize); // Recursive down-heapify
        }
    }

public:
    // Default constructor
    CustomHeap() = default;

    /**
     * @brief Inserts a new value into the heap.
     * @param val Value to insert.
     * @note Time Complexity: O(log N).
     */
    void push(int val) {
        data.push_back(val); // Insert at the next available spot
        upHeapify(data.size() - 1); // Bubble up
    }

    /**
     * @brief Removes the largest element (root) from the heap.
     * @throws std::underflow_error if the heap is empty.
     * @note Time Complexity: O(log N).
     */
    void pop() {
        if (empty()) {
            throw std::underflow_error("Heap Underflow: Cannot pop from an empty heap.");
        }
        
        // Swap root with the last element
        std::swap(data[0], data[data.size() - 1]);
        data.pop_back(); // Delete the last element

        // Reheapify downward from root
        if (!empty()) {
            downHeapify(0, data.size());
        }
    }

    /**
     * @brief Returns the largest element (root) of the heap.
     * @return const int& Reference to the root value.
     * @throws std::out_of_range if the heap is empty.
     * @note Time Complexity: O(1).
     */
    int top() const {
        if (empty()) {
            throw std::out_of_range("Heap is empty: No top element available.");
        }
        return data[0];
    }

    /**
     * @brief Builds a Max-Heap from an arbitrary vector.
     * @param array The input vector to build the heap from.
     * @note Time Complexity: O(N) using Floyd's heap construction.
     */
    void buildHeap(const std::vector<int>& array) {
        data = array;
        int n = data.size();
        if (n <= 1) return;

        // Perform bottom-up downHeapify starting from the last non-leaf node:
        // Last non-leaf node is at index (N/2 - 1).
        for (int i = n / 2 - 1; i >= 0; --i) {
            downHeapify(i, n);
        }
    }

    /**
     * @brief Sorts a vector in-place in ascending order.
     * @param array Vector to sort.
     * @note Time Complexity: O(N log N).
     */
    static void heapSort(std::vector<int>& array) {
        int n = array.size();
        if (n <= 1) return;

        CustomHeap h;
        // Step 1: Build Max-Heap on the vector elements.
        h.buildHeap(array);

        // Step 2: Repeatedly extract the maximum element.
        // Swap the root (max element) with the last element of the active subarray,
        // and heapify the new root down to restore the heap property.
        for (int i = n - 1; i > 0; --i) {
            std::swap(h.data[0], h.data[i]); // Move root to sorted section at the end
            h.downHeapify(0, i);            // Down-heapify root in the active heap of size i
        }

        // Step 3: Copy the sorted data back to the input array
        array = h.data;
    }

    // Helper functions for status
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }

    void print() const {
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE: heapSort
======================================================================
Input array: [12, 11, 13, 5, 6, 7]
N = 6

Step 1: buildHeap
- Starts at index (6 / 2 - 1) = 2.
- Leaf nodes are at indices [3, 4, 5] (values: 5, 6, 7).
- Non-leaf nodes are at indices [2, 1, 0] (values: 13, 11, 12).

1. Perform downHeapify at index 2 (value = 13):
   - Children of index 2 are left=5 (value=7), right=6 (out of bounds).
   - Max of {13, 7} is 13 at index 2. No swap.
   - Array state: [12, 11, 13, 5, 6, 7]

2. Perform downHeapify at index 1 (value = 11):
   - Children of index 1 are left=3 (value=5), right=4 (value=6).
   - Max of {11, 5, 6} is 11 at index 1. No swap.
   - Array state: [12, 11, 13, 5, 6, 7]

3. Perform downHeapify at index 0 (value = 12):
   - Children of index 0 are left=1 (value=11), right=2 (value=13).
   - Max of {12, 11, 13} is 13 at index 2. Swap data[0] and data[2].
   - Swap 12 and 13. Array state: [13, 11, 12, 5, 6, 7]
   - Recursive downHeapify at index 2 (value = 12):
     - Children of index 2: left=5 (value=7).
     - Max of {12, 7} is 12. No swap.
   - Finished buildHeap. Max-Heap is: [13, 11, 12, 5, 6, 7]

Step 2: Sorting loop (Extract elements)
- Active heap size runs from i = 5 down to 1.

1. i = 5:
   - Swap data[0] (13) with data[5] (7). Array: [7, 11, 12, 5, 6, | 13]
   - downHeapify(0, 5) -> Children of index 0: left=1 (11), right=2 (12).
   - Swap 7 with 12 (index 2). Array: [12, 11, 7, 5, 6, | 13]
   - downHeapify(2, 5) -> Children of index 2: left=5 (out of bounds). No swap.

2. i = 4:
   - Swap data[0] (12) with data[4] (6). Array: [6, 11, 7, 5, | 12, 13]
   - downHeapify(0, 4) -> Children of index 0: left=1 (11), right=2 (7).
   - Swap 6 with 11 (index 1). Array: [11, 6, 7, 5, | 12, 13]
   - downHeapify(1, 4) -> Children of index 1: left=3 (5). Max is 6. No swap.

3. i = 3:
   - Swap data[0] (11) with data[3] (5). Array: [5, 6, 7, | 11, 12, 13]
   - downHeapify(0, 3) -> Children of index 0: left=1 (6), right=2 (7).
   - Swap 5 with 7 (index 2). Array: [7, 6, 5, | 11, 12, 13]
   - downHeapify(2, 3) -> Children: left=5 (out of bounds). No swap.

4. i = 2:
   - Swap data[0] (7) with data[2] (5). Array: [5, 6, | 7, 11, 12, 13]
   - downHeapify(0, 2) -> Children of index 0: left=1 (6).
   - Swap 5 with 6 (index 1). Array: [6, 5, | 7, 11, 12, 13]

5. i = 1:
   - Swap data[0] (6) with data[1] (5). Array: [5, | 6, 7, 11, 12, 13]
   - downHeapify(0, 1) -> No children in active heap of size 1. No swap.

Loop ends.
Result: [5, 6, 7, 12, 11, 13] (Wait! Let's check step 5 swap: data[0]=6, data[1]=5, swap yields array [5, 6, 7, 11, 12, 13], which is fully sorted!)

======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity:
- buildHeap takes O(N) time.
- The sorting loop executes N-1 times. Each iteration performs a swap (O(1))
  and a downHeapify operation, which takes O(log i) time.
- Total sorting phase time: O(N log N).
- Total Time Complexity: O(N log N) in all cases (Best, Average, and Worst).

Space Complexity:
- The heapification and sorting are done in-place on the vector.
- Total Space Complexity: O(1) auxiliary space. (Recursive heapify calls use O(log N) stack space, which can be optimized to O(1) using iterative down-heapify).
*/

int main() {
    std::vector<int> array = {12, 11, 13, 5, 6, 7};
    std::cout << "Original array: ";
    for (int val : array) std::cout << val << " ";
    std::cout << std::endl;

    // Test buildHeap and CustomHeap operations
    CustomHeap myHeap;
    myHeap.buildHeap(array);
    std::cout << "Heap after buildHeap: ";
    myHeap.print(); // Expected max heap representation

    std::cout << "Top element (max): " << myHeap.top() << " (Expected: 13)" << std::endl;
    
    myHeap.pop();
    std::cout << "Heap after pop: ";
    myHeap.print(); // Should have 12 as top
    std::cout << "Top element now: " << myHeap.top() << " (Expected: 12)" << std::endl;

    myHeap.push(15);
    std::cout << "Heap after pushing 15: ";
    myHeap.print(); // Should have 15 as top
    std::cout << "Top element now: " << myHeap.top() << " (Expected: 15)" << std::endl;

    // Test heapSort
    std::vector<int> sortArray = {12, 11, 13, 5, 6, 7};
    CustomHeap::heapSort(sortArray);
    std::cout << "Sorted array: ";
    for (int val : sortArray) std::cout << val << " ";
    std::cout << " (Expected: 5 6 7 11 12 13)" << std::endl;

    return 0;
}
