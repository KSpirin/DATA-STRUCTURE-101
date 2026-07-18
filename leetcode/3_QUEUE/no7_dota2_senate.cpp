/**
 * @brief LeetCode 649 - Dota2 Senate
 * @difficulty Medium
 * @link https://leetcode.com/problems/dota2-senate/
 *
 * Problem:
 * Each senator can ban the next opponent. Return the winning party.
 * 
 * Example: 'RD'->Radiant, 'RDD'->Dire
 * 
 * Constraints: 1 <= senate.length <= 10^4 */

#include <iostream>
#include <string>
#include <queue>
#include <cassert>

class Solution {
public:
    std::string predictPartyVictory(std::string senate) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    check(Solution().predictPartyVictory("RD") == "Radiant",    "RD -> Radiant");
    check(Solution().predictPartyVictory("RDD") == "Dire",       "RDD -> Dire");
    check(Solution().predictPartyVictory("RRDD") == "Radiant",  "RRDD -> Radiant");
    check(Solution().predictPartyVictory("RDRD") == "Radiant",  "RDRD -> Radiant");
    check(Solution().predictPartyVictory("D") == "Dire",         "D -> Dire");
    check(Solution().predictPartyVictory("R") == "Radiant",      "R -> Radiant");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
