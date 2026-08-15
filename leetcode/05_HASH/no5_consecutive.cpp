/**
 * @brief LeetCode 128 - Longest Consecutive Sequence
 * @difficulty Medium
 * @link https://leetcode.com/problems/longest-consecutive-sequence/
 *
 * Problem:
 * Return length of longest consecutive elements sequence. Must be O(n).
 * 
 * Example: [100,4,200,1,3,2] -> 4 (sequence: 1,2,3,4)
 * 
 * Constraints: 0 <= nums.length <= 10^5 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        // TODO (O(n) required)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<int> n1={100,4,200,1,3,2};
        check(Solution().longestConsecutive(n1)==4, "[100,4,200,1,3,2] -> 4");
    }
    {
        std::vector<int> n2={0,3,7,2,5,8,4,6,0,1};
        check(Solution().longestConsecutive(n2)==9, "[0..8] -> 9");
    }
    {
        std::vector<int> n3={};
        check(Solution().longestConsecutive(n3)==0, "empty -> 0");
    }
    {
        std::vector<int> n4={1};
        check(Solution().longestConsecutive(n4)==1, "single -> 1");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
