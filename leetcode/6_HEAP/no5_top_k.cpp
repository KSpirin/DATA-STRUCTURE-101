/**
 * @file no5_top_k_frequent_elements.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 347: Top K Frequent Elements (Medium)
 * @link https://leetcode.com/problems/top-k-frequent-elements/
 */

/*
Problem Description:
--------------------
Given an integer array nums and an integer k, return the k most frequent elements. 
You may return the answer in any order.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Constraints:
------------
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- k is in the range [1, the number of unique elements in the array].
- It is guaranteed that the answer is unique.

Follow up: Your algorithm's time complexity must be better than O(n log n), 
where n is the array's size.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <algorithm>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        // Guard Clause: Validate inputs
        if (nums.empty() || k <= 0) {
            throw std::invalid_argument("Input array cannot be empty and k must be positive.");
        }

        // Step 1: Count frequency of each element using a hash map.
        // Time Complexity: O(N)
        std::unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Guard Clause: Verify k is within range of unique elements
        if (k > static_cast<int>(frequencyMap.size())) {
            throw std::invalid_argument("k exceeds the number of unique elements in the array.");
        }

        // Step 2: Use a Min-Heap to keep track of the k most frequent elements.
        // We store pairs of (frequency, element). 
        // A min-heap maintains the element with the smallest frequency at the top.
        // Cap the size of the heap at k:
        // - Whenever size exceeds k, we pop the top (least frequent of the k+1 elements).
        // - This leaves only the k highest frequency elements in the heap.
        // Time Complexity: O(U log k), where U is the number of unique elements.
        std::priority_queue<
            std::pair<int, int>, 
            std::vector<std::pair<int, int>>, 
            std::greater<std::pair<int, int>>
        > minHeap;

        for (const auto& [element, frequency] : frequencyMap) {
            minHeap.push({frequency, element});
            if (minHeap.size() > static_cast<size_t>(k)) {
                minHeap.pop();
            }
        }

        // Step 3: Extract the k elements from the heap into the result vector.
        // Time Complexity: O(k log k)
        std::vector<int> result;
        result.reserve(k);
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }

        // Optional: reverse to return elements sorted by frequency in descending order, 
        // although LeetCode accepts results in any order.
        std::reverse(result.begin(), result.end());

        return result;
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE
======================================================================
Input: nums = [1, 1, 1, 2, 2, 3], k = 2

1. Count Frequencies:
   frequencyMap = {
       1: 3,
       2: 2,
       3: 1
   }

2. Process frequencyMap into Min-Heap (size limit k = 2):
   - Entry {1: 3}:
     * minHeap.push({3, 1}) -> minHeap = [ {3, 1} ] (size 1 <= 2)
   - Entry {2: 2}:
     * minHeap.push({2, 2}) -> minHeap = [ {2, 2}, {3, 1} ] (size 2 <= 2)
   - Entry {3: 1}:
     * minHeap.push({1, 3}) -> minHeap = [ {1, 3}, {3, 1}, {2, 2} ] (size 3 > 2)
     * minHeap.pop()       -> Pops {1, 3} (least frequency: 1)
     * minHeap = [ {2, 2}, {3, 1} ] (size 2)

3. Extract results:
   - minHeap.top() = {2, 2} -> result.push_back(2), minHeap.pop()
   - minHeap.top() = {3, 1} -> result.push_back(1), minHeap.pop()
   - result = [2, 1]

4. Reverse result:
   - result = [1, 2] (Correct!)

======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity:
- Step 1 (Frequency map construction): O(N) where N is the size of nums.
- Step 2 (Heap insertion and sizing): O(U log k) where U is the number of unique elements.
  Since U <= N, this is at most O(N log k).
- Step 3 (Heap extraction): O(k log k).
- Total Time Complexity: O(N log k). Since k <= N, this is strictly better than O(N log N).

Space Complexity:
- Frequency Map: O(U) space to store frequencies of unique elements.
- Min-Heap: O(k) space to store at most k + 1 element-frequency pairs.
- Result Vector: O(k) space.
- Total Space Complexity: O(U + k) auxiliary space, which in the worst-case is O(N).
*/

int main() {
    Solution solver;
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;

    try {
        std::vector<int> result = solver.topKFrequent(nums, k);
        std::cout << "Top " << k << " frequent elements are: [";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << (i + 1 < result.size() ? ", " : "");
        }
        std::cout << "] (Expected: [1, 2])" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
