/**
 * @brief LeetCode 32 - Longest Valid Parentheses
 * @difficulty Hard
 * @link https://leetcode.com/problems/longest-valid-parentheses/
 *
 * Problem:
 * Return the length of the longest valid parentheses substring.
 * 
 * Example: '(()' -> 2, ')()())' -> 4
 * 
 * Constraints: 0 <= s.length <= 3*10^4 */

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().longestValidParentheses("(()") == 2,      "(()  -> 2");
    check(Solution().longestValidParentheses(")()())") == 4,   ")()()) -> 4");
    check(Solution().longestValidParentheses("") == 0,         "empty -> 0");
    check(Solution().longestValidParentheses("()") == 2,       "() -> 2");
    check(Solution().longestValidParentheses("()(()") == 2,    "()(( -> 2");
    check(Solution().longestValidParentheses("(()())") == 6,   "(()()) -> 6");
    check(Solution().longestValidParentheses("((()))") == 6,   "((()))-> 6");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
