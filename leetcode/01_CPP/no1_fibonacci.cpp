/**
 * @brief LeetCode 509 - Fibonacci Number
 * @difficulty Easy
 * @link https://leetcode.com/problems/fibonacci-number/
 *
 * Problem:
 * Given n, return F(n) where F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2).
 * 
 * Example: fib(4) == 3, fib(10) == 55
 * 
 * Constraints: 0 <= n <= 30 */

#include <iostream>
#include <cassert>
#include <string>

class Solution {
public:
    int fib(int n) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().fib(0) == 0,  "fib(0) == 0");
    check(Solution().fib(1) == 1,  "fib(1) == 1");
    check(Solution().fib(2) == 1,  "fib(2) == 1");
    check(Solution().fib(4) == 3,  "fib(4) == 3");
    check(Solution().fib(5) == 5,  "fib(5) == 5");
    check(Solution().fib(10) == 55, "fib(10) == 55");
    check(Solution().fib(15) == 610,"fib(15) == 610");
    check(Solution().fib(20) == 6765,"fib(20) == 6765");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
