/**
 * @brief LeetCode 994 - Rotting Oranges
 * @difficulty Medium
 * @link https://leetcode.com/problems/rotting-oranges/
 *
 * Problem:
 * 0=empty,1=fresh,2=rotten. Rotten spreads 4-directionally each minute.
 * Return minutes until no fresh remains, or -1 if impossible.
 * 
 * Example: [[2,1,1],[1,1,0],[0,1,1]] -> 4 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid) {
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
        std::vector<std::vector<int>> g1 = {{2,1,1},{1,1,0},{0,1,1}};
        check(Solution().orangesRotting(g1) == 4, "standard -> 4");
    }
    {
        std::vector<std::vector<int>> g2 = {{2,1,1},{0,1,1},{1,0,1}};
        check(Solution().orangesRotting(g2) == -1, "isolated fresh -> -1");
    }
    {
        std::vector<std::vector<int>> g3 = {{0,2}};
        check(Solution().orangesRotting(g3) == 0, "no fresh -> 0");
    }
    {
        std::vector<std::vector<int>> g4 = {{1}};
        check(Solution().orangesRotting(g4) == -1, "single fresh, no rotten -> -1");
    }
    {
        std::vector<std::vector<int>> g5 = {{2}};
        check(Solution().orangesRotting(g5) == 0, "single rotten -> 0");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
