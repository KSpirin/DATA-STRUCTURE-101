/**
 * @brief LeetCode 1 - Two Sum
 * @difficulty Easy
 * @link https://leetcode.com/problems/two-sum/
 *
 * Problem:
 * Return indices of two numbers that add up to target. Exactly one solution.
 * 
 * Example: [2,7,11,15], target=9 -> [0,1]
 * 
 * Constraints: 2 <= nums.length <= 10^4 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<int> n1={2,7,11,15};
        auto r=Solution().twoSum(n1,9);
        check(r[0]==0&&r[1]==1, "[2,7,11,15] target=9 -> [0,1]");
    }
    {
        std::vector<int> n2={3,2,4};
        auto r=Solution().twoSum(n2,6);
        check(r[0]==1&&r[1]==2, "[3,2,4] target=6 -> [1,2]");
    }
    {
        std::vector<int> n3={3,3};
        auto r=Solution().twoSum(n3,6);
        check(r[0]==0&&r[1]==1, "[3,3] target=6 -> [0,1]");
    }
    {
        std::vector<int> n4={1,2,3,4,5};
        auto r=Solution().twoSum(n4,9);
        check(r[0]==3&&r[1]==4, "[1..5] target=9 -> [3,4]");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
