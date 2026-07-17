/**
 * @file no5_longest_consecutive_sequence.cpp
 * @brief LeetCode 128: Longest Consecutive Sequence
 * @difficulty Medium
 * @link https://leetcode.com/problems/longest-consecutive-sequence/
 * 
 * Problem Description:
 * Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
 * You must write an algorithm that runs in O(n) time.
 */

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cassert>

class Solution {
public:
    int longestConsecutive(const std::vector<int>& nums) {
        // Insert all numbers into an unordered_set to allow O(1) lookups
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int longestStreak = 0;

        // Iterate through each number in the set
        for (int num : numSet) {
            // Check if this number is the start of a sequence.
            // If num - 1 exists in the set, then 'num' is not the start of a new sequence
            // because the sequence containing 'num' started at some number smaller than 'num'.
            if (numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentStreak = 1;

                // Keep incrementing currentNum and checking if the next consecutive number is in the set
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                // Update the maximum streak found so far
                longestStreak = std::max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Input: nums = [100, 4, 200, 1, 3, 2]

Initial state:
  numSet = {1, 2, 3, 4, 100, 200}
  longestStreak = 0

Iterate through elements in numSet:
(Note: Set traversal order may vary, but let's assume we visit in this order for trace)

1. num = 100
   Is 99 (num - 1) in set? No. (This is the start of a sequence)
   Loop while currentNum + 1 is in set:
     Is 101 in set? No.
   Streak for 100 is 1.
   longestStreak = max(0, 1) = 1.

2. num = 4
   Is 3 (num - 1) in set? Yes. (Skip, since 4 is not the start of a sequence)

3. num = 200
   Is 199 (num - 1) in set? No. (This is the start of a sequence)
   Loop while currentNum + 1 is in set:
     Is 201 in set? No.
   Streak for 200 is 1.
   longestStreak = max(1, 1) = 1.

4. num = 1
   Is 0 (num - 1) in set? No. (This is the start of a sequence)
   Loop while currentNum + 1 is in set:
     Is 2 in set? Yes. (streak = 2)
     Is 3 in set? Yes. (streak = 3)
     Is 4 in set? Yes. (streak = 4)
     Is 5 in set? No.
   Streak for 1 is 4.
   longestStreak = max(1, 4) = 4.

5. num = 3
   Is 2 (num - 1) in set? Yes. (Skip)

6. num = 2
   Is 1 (num - 1) in set? Yes. (Skip)

Final output: 4
================================================================================
Complexity Analysis:
- Time Complexity: O(N)
  Although the time complexity contains a nested while loop, the while loop only runs 
  for the start of a sequence. Each element is visited at most twice: once in the outer 
  loop, and at most once during the inner while loop traversal. Thus, it runs in linear time.
- Space Complexity: O(N)
  We store all N unique numbers in an unordered_set, taking O(N) extra space.
================================================================================
*/

int main() {
    Solution solver;
    std::vector<int> nums = {100, 4, 200, 1, 3, 2};
    int result = solver.longestConsecutive(nums);
    assert(result == 4);

    std::vector<int> emptyNums = {};
    assert(solver.longestConsecutive(emptyNums) == 0);

    std::vector<int> duplicateNums = {1, 2, 0, 1};
    assert(solver.longestConsecutive(duplicateNums) == 3); // Sequence is 0, 1, 2

    std::cout << "Longest Consecutive Sequence tests passed!" << std::endl;
    return 0;
}
