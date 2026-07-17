#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// PROBLEM: LeetCode 560 - Subarray Sum Equals K
// Count subarrays whose sum equals k.

class Solution {
public:
    int subarraySum(const std::vector<int>& nums, int k) {
        // TODO:
        // - Initialize count=0, sum=0
        // - Initialize map with {0: 1}  (empty prefix has sum 0)
        // - For each num in nums:
        //   sum += num
        //   if (sum - k) is in map: count += map[sum - k]
        //   map[sum]++
        // - Return count

        return 0;
    }
};

int main() {
    // [1,1,1] with k=2: subarrays [1,1] starting at 0 and [1,1] starting at 1 -> count=2
    std::vector<int> nums = {1, 1, 1};
    assert(Solution().subarraySum(nums, 2) == 2);
    std::cout << "5_HASH Coding 3 Passed!" << std::endl;
    return 0;
}
