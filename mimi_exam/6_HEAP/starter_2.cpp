#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// PROBLEM: LeetCode 215 - Kth Largest Element
// Return the Kth largest element in the array.

class Solution {
public:
    int findKthLargest(const std::vector<int>& nums, int k) {
        // TODO:
        // - Create priority_queue<int, vector<int>, greater<int>> pq  (min-heap)
        // - For each num: push num, if pq.size() > k, pop
        // - Return pq.top()

        return 0;
    }
};

int main() {
    std::vector<int> nums = {3, 2, 1, 5, 6, 4};
    assert(Solution().findKthLargest(nums, 2) == 5);  // 2nd largest = 5
    std::cout << "6_HEAP Coding 2 Passed!" << std::endl;
    return 0;
}
