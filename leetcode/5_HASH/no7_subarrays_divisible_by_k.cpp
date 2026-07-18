/**
 * @brief LeetCode 974 - Subarrays Divisible by K
 * @difficulty Medium
 * @link https://leetcode.com/problems/subarray-sums-divisible-by-k/
 *
 * Problem:
 * Return count of subarrays whose sum is divisible by k.
 * 
 * Example: [4,5,0,-2,-3,1], k=5 -> 7
 * 
 * Constraints: 1 <= nums.length <= 3*10^4, 2 <= k <= 10^4 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

class Solution {
public:
    int subarraysDivByK(std::vector<int>& nums, int k) {
        // TODO (prefix sum + remainder map)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<int> n1={4,5,0,-2,-3,1};
        check(Solution().subarraysDivByK(n1,5)==7,"[4,5,0,-2,-3,1] k=5 -> 7");
    }
    {
        std::vector<int> n2={5};
        check(Solution().subarraysDivByK(n2,5)==1,"[5] k=5 -> 1");
    }
    {
        std::vector<int> n3={1,2,3,4,5};
        check(Solution().subarraysDivByK(n3,5)==4,"[1..5] k=5 -> 4");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
