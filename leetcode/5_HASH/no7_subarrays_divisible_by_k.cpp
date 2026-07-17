/**
 * @file no7_subarrays_divisible_by_k.cpp
 * @brief LeetCode 974: Subarray Sums Divisible by K
 * @difficulty Medium
 * @link https://leetcode.com/problems/subarray-sums-divisible-by-k/
 * 
 * Problem Description:
 * Given an integer array `nums` and an integer `k`, return the number of non-empty 
 * subarrays that have a sum divisible by `k`.
 * 
 * A subarray is a contiguous part of an array.
 */

#include <vector>
#include <unordered_map>
#include <iostream>
#include <cassert>

class Solution {
public:
    int subarraysDivByK(std::vector<int>& nums, int k) {
        // We use a frequency vector of size k to keep track of prefix sum remainders.
        // Using a vector is much faster than std::unordered_map because the range of
        // possible remainders is exactly [0, k-1], which matches a contiguous array.
        std::vector<int> remainderCounts(k, 0);
        
        // Base case: A prefix sum of 0 has occurred 1 time (before processing any elements)
        remainderCounts[0] = 1;
        
        int cumulativeSum = 0;
        int count = 0;
        
        for (int num : nums) {
            cumulativeSum += num;
            
            // In C++, the % operator can yield a negative remainder for negative values.
            // We adjust it using (cumulativeSum % k + k) % k to guarantee a positive remainder in [0, k-1].
            int rem = (cumulativeSum % k + k) % k;
            
            // If the remainder has been seen before, it means there are prefix subarrays
            // with the same remainder. The difference between those prefixes and the current prefix
            // is a subarray whose sum is divisible by k.
            count += remainderCounts[rem];
            
            // Record the current prefix sum remainder occurrence
            remainderCounts[rem]++;
        }
        
        return count;
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Input: nums = [4, 5, 0, -2, -3, 1], k = 5

Initial state:
  remainderCounts = [1, 0, 0, 0, 0]  (remainderCounts[0] = 1, others 0)
  cumulativeSum = 0
  count = 0

Iterate through elements:

1. num = 4
   - cumulativeSum = 4
   - rem = (4 % 5 + 5) % 5 = 4
   - count += remainderCounts[4] (0) -> count = 0
   - remainderCounts[4]++ -> remainderCounts = [1, 0, 0, 0, 1]

2. num = 5
   - cumulativeSum = 4 + 5 = 9
   - rem = (9 % 5 + 5) % 5 = 4
   - count += remainderCounts[4] (1) -> count = 1
   - remainderCounts[4]++ -> remainderCounts = [1, 0, 0, 0, 2]

3. num = 0
   - cumulativeSum = 9 + 0 = 9
   - rem = (9 % 5 + 5) % 5 = 4
   - count += remainderCounts[4] (2) -> count = 3
   - remainderCounts[4]++ -> remainderCounts = [1, 0, 0, 0, 3]

4. num = -2
   - cumulativeSum = 9 + (-2) = 7
   - rem = (7 % 5 + 5) % 5 = 2
   - count += remainderCounts[2] (0) -> count = 3
   - remainderCounts[2]++ -> remainderCounts = [1, 0, 1, 0, 3]

5. num = -3
   - cumulativeSum = 7 + (-3) = 4
   - rem = (4 % 5 + 5) % 5 = 4
   - count += remainderCounts[4] (3) -> count = 6
   - remainderCounts[4]++ -> remainderCounts = [1, 0, 1, 0, 4]

6. num = 1
   - cumulativeSum = 4 + 1 = 5
   - rem = (5 % 5 + 5) % 5 = 0
   - count += remainderCounts[0] (1) -> count = 7
   - remainderCounts[0]++ -> remainderCounts = [2, 0, 1, 0, 4]

Final count = 7.

================================================================================
Complexity Analysis:
- Time Complexity: O(N)
  We iterate through the array `nums` of size N exactly once. 
  Inside the loop, all operations (modulo arithmetic, array indexing, additions) are O(1).
  Thus, total time complexity is O(N).
- Space Complexity: O(k)
  We allocate a helper array/vector of size k to store the remainder frequencies.
  Thus, space complexity is O(k).
================================================================================
*/

int main() {
    Solution solver;
    std::vector<int> nums1 = {4, 5, 0, -2, -3, 1};
    int k1 = 5;
    assert(solver.subarraysDivByK(nums1, k1) == 7);
    
    std::vector<int> nums2 = {5};
    int k2 = 9;
    assert(solver.subarraysDivByK(nums2, k2) == 0);
    
    std::cout << "Subarrays Divisible by K tests passed!" << std::endl;
    return 0;
}
