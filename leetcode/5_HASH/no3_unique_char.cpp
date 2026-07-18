/**
 * @brief LeetCode 387 - First Unique Character
 * @difficulty Easy
 * @link https://leetcode.com/problems/first-unique-character-in-a-string/
 *
 * Problem:
 * Return index of first non-repeating character, or -1 if none.
 * 
 * Example: 'leetcode' -> 0, 'aabb' -> -1
 * 
 * Constraints: 1 <= s.length <= 10^5 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>

class Solution {
public:
    int firstUniqChar(std::string s) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().firstUniqChar("leetcode") == 0,  "leetcode -> 0 (l)");
    check(Solution().firstUniqChar("loveleetcode") == 2,"loveleetcode -> 2 (v)");
    check(Solution().firstUniqChar("aabb") == -1,      "aabb -> -1");
    check(Solution().firstUniqChar("z") == 0,           "single char -> 0");
    check(Solution().firstUniqChar("aab") == 2,         "aab -> 2 (b)");
    check(Solution().firstUniqChar("abcabc") == -1,    "abcabc -> -1");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
