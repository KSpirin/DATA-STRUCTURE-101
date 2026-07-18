/**
 * @brief LeetCode 49 - Group Anagrams
 * @difficulty Medium
 * @link https://leetcode.com/problems/group-anagrams/
 *
 * Problem:
 * Group strings that are anagrams of each other.
 * 
 * Example: ['eat','tea','tan','ate','nat','bat'] -> [['bat'],['nat','tan'],['ate','eat','tea']]
 * 
 * Constraints: 1 <= strs.length <= 10^4 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
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
        std::vector<std::string> s1={"eat","tea","tan","ate","nat","bat"};
        auto r=Solution().groupAnagrams(s1);
        check(r.size()==3, "6 words -> 3 groups");
    }
    {
        std::vector<std::string> s2={""};
        auto r=Solution().groupAnagrams(s2);
        check(r.size()==1, "empty string -> 1 group");
    }
    {
        std::vector<std::string> s3={"a"};
        auto r=Solution().groupAnagrams(s3);
        check(r.size()==1 && r[0][0]=="a", "single char -> 1 group");
    }
    {
        std::vector<std::string> s4={"abc","bca","cab","xyz","zyx"};
        auto r=Solution().groupAnagrams(s4);
        check(r.size()==2, "abc group + xyz group -> 2 groups");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
