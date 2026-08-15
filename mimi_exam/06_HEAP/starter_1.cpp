#include <iostream>
#include <vector>
#include <cassert>

// PROBLEM: Verify Max-Heap Property
// A max-heap requires: parent >= both children
// For index i: left child = 2*i+1, right child = 2*i+2
// Only check internal nodes (index 0 to (n-2)/2)

class Solution {
public:
    bool isMaxHeap(const std::vector<int>& arr) {
        // TODO:
        // - Loop i from 0 to (n-2)/2
        // - If left child (2i+1) exists AND arr[2i+1] > arr[i]: return false
        // - If right child (2i+2) exists AND arr[2i+2] > arr[i]: return false
        // - return true

        return false;
    }
};

int main() {
    std::vector<int> heap1 = {90, 15, 10, 7};
    std::vector<int> heap2 = {90, 100, 10};  // 100 > 90 -> invalid!
    assert(Solution().isMaxHeap(heap1) == true);
    assert(Solution().isMaxHeap(heap2) == false);
    std::cout << "6_HEAP Coding 1 Passed!" << std::endl;
    return 0;
}
