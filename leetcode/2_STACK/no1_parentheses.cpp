/**
 * @brief LeetCode 20 - Valid Parentheses
 * @difficulty Easy
 * @link https://leetcode.com/problems/valid-parentheses/
 *
 * Problem:
 * Brackets must close in the correct order and type.
 * 
 * Example: '()[]{}'->true, '(]'->false
 * 
 * Constraints: 1 <= s.length <= 10^4 */

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

class Solution {
public:
    bool isValid(std::string s) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().isValid("()") == true,         "() -> true");
    check(Solution().isValid("()[]{}") == true,     "()[]{} -> true");
    check(Solution().isValid("(]") == false,        "(] -> false");
    check(Solution().isValid("([)]") == false,      "([)] -> false");
    check(Solution().isValid("{[]}") == true,       "{[]} -> true");
    check(Solution().isValid("") == true,           "empty -> true");
    check(Solution().isValid("]") == false,         "] alone -> false");
    check(Solution().isValid("((") == false,        "(( no close -> false");
    check(Solution().isValid("({[]})") == true,     "nested -> true");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
