/**
 * @file no1_kth_largest.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 215: Kth Largest Element in an Array (Medium)
 * @link https://leetcode.com/problems/kth-largest-element-in-an-array/
 */

/*
Problem Description:
--------------------
Given an integer array nums and an integer k, return the kth largest element in the array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.
Can you solve it without sorting in O(n) time complexity?

Example 1:
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

Constraints:
1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        // Guard Clause: Validate inputs
        if (nums.empty() || k <= 0 || k > static_cast<int>(nums.size())) {
            throw std::invalid_argument("Invalid values for nums or k.");
        }

        // We use a Min-Heap (priority_queue with greater comparator).
        // A min-heap stores the smallest elements at the top.
        // By keeping the heap size capped at k:
        // - The heap will store the k largest elements seen so far.
        // - The root (top) of the heap will be the smallest of these k largest elements,
        //   which is exactly the kth largest element in the entire array.
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

        for (int num : nums) {
            minHeap.push(num);
            
            // If the size exceeds k, pop the smallest element.
            if (minHeap.size() > static_cast<size_t>(k)) {
                minHeap.pop();
            }
        }

        // The top of the heap is the kth largest element.
        return minHeap.top();
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE
======================================================================
Input: nums = [3, 2, 1, 5, 6, 4], k = 2

Iterative execution trace:
----------------------------------------------------------------------
1. Process num = 3:
   - minHeap.push(3) -> Heap: [3]
   - minHeap.size() (1) <= k (2) -> No pop.
   
2. Process num = 2:
   - minHeap.push(2) -> Heap: [2, 3] (Min-Heap property: 2 is root)
   - minHeap.size() (2) <= k (2) -> No pop.

3. Process num = 1:
   - minHeap.push(1) -> Heap: [1, 3, 2] (Min-Heap property: 1 is root)
   - minHeap.size() (3) > k (2) -> Pop root.
   - minHeap.pop() -> Removed 1. Heap: [2, 3]

4. Process num = 5:
   - minHeap.push(5) -> Heap: [2, 3, 5] (Min-Heap property: 2 is root)
   - minHeap.size() (3) > k (2) -> Pop root.
   - minHeap.pop() -> Removed 2. Heap: [3, 5]

5. Process num = 6:
   - minHeap.push(6) -> Heap: [3, 5, 6] (Min-Heap property: 3 is root)
   - minHeap.size() (3) > k (2) -> Pop root.
   - minHeap.pop() -> Removed 3. Heap: [5, 6]

6. Process num = 4:
   - minHeap.push(4) -> Heap: [4, 6, 5] (Min-Heap property: 4 is root)
   - minHeap.size() (3) > k (2) -> Pop root.
   - minHeap.pop() -> Removed 4. Heap: [5, 6]

End of Loop.
Return minHeap.top() -> returns 5. (Correct: 5 is the 2nd largest element).
======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity: 
- For each of the N elements, we insert it into a heap of size at most k+1.
- Each insertion/removal takes O(log k) time.
- Total Time Complexity: O(N log k). 
- Since k <= N, this is faster than sorting the entire array which takes O(N log N).

Space Complexity:
- We store at most k+1 elements in the min-heap.
- Total Space Complexity: O(k) auxiliary space.
*/

int main() {
    Solution solver;
    std::vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    try {
        int result = solver.findKthLargest(nums, k);
        std::cout << "Kth (" << k << ") largest element is: " << result << " (Expected: 5)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
