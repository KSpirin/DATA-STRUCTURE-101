/**
 * @brief LeetCode 70 - Climbing Stairs
 * @difficulty Easy
 * @link https://leetcode.com/problems/climbing-stairs/
 *
 * Problem:
 * You can climb 1 or 2 steps. Return the number of distinct ways to reach step n.
 * 
 * Example: n=2 -> 2, n=3 -> 3
 * 
 * Constraints: 1 <= n <= 45 */

#include <iostream>
#include <cassert>
#include <string>

class Solution {
public:
    int climbStairs(int n) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().climbStairs(1) == 1,  "n=1 -> 1");
    check(Solution().climbStairs(2) == 2,  "n=2 -> 2");
    check(Solution().climbStairs(3) == 3,  "n=3 -> 3");
    check(Solution().climbStairs(4) == 5,  "n=4 -> 5");
    check(Solution().climbStairs(5) == 8,  "n=5 -> 8");
    check(Solution().climbStairs(6) == 13, "n=6 -> 13");
    check(Solution().climbStairs(10) == 89,"n=10 -> 89");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
