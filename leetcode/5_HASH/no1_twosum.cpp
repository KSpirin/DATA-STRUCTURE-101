/**
 * @file no1_two_sum.cpp
 * @brief LeetCode 1: Two Sum
 * @difficulty Easy
 * @link https://leetcode.com/problems/two-sum/
 * 
 * Problem Description:
 * Given an array of integers `nums` and an integer `target`, return indices of the two numbers 
 * such that they add up to `target`.
 * You may assume that each input would have exactly one solution, and you may not use the same 
 * element twice. You can return the answer in any order.
 */

#include <vector>
#include <unordered_map>
#include <iostream>
#include <cassert>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // Hash map to store element value as key and its index as value
        std::unordered_map<int, int> numMap;
        
        // Loop through the input array
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            
            // Check if complement exists in our map
            if (numMap.find(complement) != numMap.end()) {
                // If found, return the index of the complement and current index
                return {numMap[complement], i};
            }
            
            // Otherwise, store current element and its index in map
            numMap[nums[i]] = i;
        }
        
        // No solution found (though problem statement guarantees one exists)
        return {};
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Input: nums = [2, 7, 11, 15], target = 9

Initial state:
  numMap = {}

Iter 1: i = 0
  nums[0] = 2
  complement = 9 - 2 = 7
  Is 7 in numMap? No.
  Insert (2 -> 0) into numMap.
  numMap = {2: 0}

Iter 2: i = 1
  nums[1] = 7
  complement = 9 - 7 = 2
  Is 2 in numMap? Yes! (Associated index is 0)
  Return {0, 1}

Output: [0, 1]
================================================================================
Complexity Analysis:
- Time Complexity: O(N)
  We traverse the list containing N elements exactly once. Each lookup in the 
  hash table costs only O(1) time on average.
- Space Complexity: O(N)
  The extra space required depends on the number of items stored in the hash table, 
  which stores at most N elements.
================================================================================
*/

int main() {
    Solution solver;
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> result = solver.twoSum(nums, target);
    
    assert(result.size() == 2);
    assert(result[0] == 0 && result[1] == 1);
    
    std::cout << "Two Sum test passed! Indices: " << result[0] << ", " << result[1] << std::endl;
    return 0;
}
