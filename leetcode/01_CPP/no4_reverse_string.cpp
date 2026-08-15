/**
 * @brief LeetCode 344 - Reverse String
 * @difficulty Easy
 * @link https://leetcode.com/problems/reverse-string/
 *
 * Problem:
 * Reverse a char array in-place. O(1) extra memory.
 * 
 * Example: ['h','e','l','l','o'] -> ['o','l','l','e','h']
 * 
 * Constraints: 1 <= s.length <= 10^5 */

#include <iostream>
#include <vector>
#include <cassert>
#include <string>

class Solution {
public:
    void reverseString(std::vector<char>& s) {
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
        std::vector<char> s = {'h','e','l','l','o'};
        Solution().reverseString(s);
        check(s[0]=='o' && s[4]=='h', "hello -> olleh");
    }
    {
        std::vector<char> s = {'H','a','n','n','a','H'};
        Solution().reverseString(s);
        check(s[0]=='H' && s[5]=='H', "Hannah -> hannaH");
    }
    {
        std::vector<char> s = {'a'};
        Solution().reverseString(s);
        check(s[0]=='a', "single char unchanged");
    }
    {
        std::vector<char> s = {'a','b'};
        Solution().reverseString(s);
        check(s[0]=='b' && s[1]=='a', "ab -> ba");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
