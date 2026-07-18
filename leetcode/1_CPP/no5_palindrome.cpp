/**
 * @brief LeetCode 125 - Valid Palindrome
 * @difficulty Easy
 * @link https://leetcode.com/problems/valid-palindrome/
 *
 * Problem:
 * After removing non-alphanumerics and lowercasing, check if string reads same forward and back.
 * 
 * Example: 'A man, a plan, a canal: Panama' -> true
 * 
 * Constraints: 1 <= s.length <= 2*10^5 */

#include <iostream>
#include <string>
#include <cassert>

class Solution {
public:
    bool isPalindrome(std::string s) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().isPalindrome("A man, a plan, a canal: Panama") == true,  "Panama -> true");
    check(Solution().isPalindrome("race a car") == false,                       "race a car -> false");
    check(Solution().isPalindrome(" ") == true,                                 "space only -> true");
    check(Solution().isPalindrome("Was it a car or a cat I saw?") == true,     "cat/car -> true");
    check(Solution().isPalindrome("No lemon, no melon") == true,               "lemon/melon -> true");
    check(Solution().isPalindrome("hello") == false,                            "hello -> false");
    check(Solution().isPalindrome("0P") == false,                               "0P -> false");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
