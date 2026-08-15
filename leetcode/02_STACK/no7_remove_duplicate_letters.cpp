/**
 * @brief LeetCode 316 - Remove Duplicate Letters
 * @difficulty Hard
 * @link https://leetcode.com/problems/remove-duplicate-letters/
 *
 * Problem:
 * Remove duplicate letters so each appears once, in smallest lexicographic order.
 * 
 * Example: 'bcabc' -> 'abc', 'cbacdcbc' -> 'acdb'
 * 
 * Constraints: 1 <= s.length <= 10^4 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cassert>

class Solution {
public:
    std::string removeDuplicateLetters(std::string s) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().removeDuplicateLetters("bcabc") == "abc",    "bcabc -> abc");
    check(Solution().removeDuplicateLetters("cbacdcbc") == "acdb", "cbacdcbc -> acdb");
    check(Solution().removeDuplicateLetters("abcd") == "abcd",    "abcd -> abcd (no dup)");
    check(Solution().removeDuplicateLetters("aaaa") == "a",        "aaaa -> a");
    check(Solution().removeDuplicateLetters("ba") == "ba",         "ba -> ba");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
