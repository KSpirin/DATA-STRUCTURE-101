/**
 * @brief LeetCode 1091 - Shortest Path in Binary Matrix
 * @difficulty Medium
 * @link https://leetcode.com/problems/shortest-path-in-binary-matrix/
 *
 * Problem:
 * Shortest clear path (8-directional) from (0,0) to (n-1,n-1). Clear = all 0s.
 * 
 * Example: [[0,1],[1,0]] -> 2
 * 
 * Constraints: n == grid.length, 1 <= n <= 100 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
public:
    int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
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
        std::vector<std::vector<int>> g1 = {{0,1},{1,0}};
        check(Solution().shortestPathBinaryMatrix(g1) == 2, "2x2 -> 2");
    }
    {
        std::vector<std::vector<int>> g2 = {{0,0,0},{1,1,0},{1,1,0}};
        check(Solution().shortestPathBinaryMatrix(g2) == 4, "3x3 -> 4");
    }
    {
        std::vector<std::vector<int>> g3 = {{1,0},{0,0}};
        check(Solution().shortestPathBinaryMatrix(g3) == -1, "start blocked -> -1");
    }
    {
        std::vector<std::vector<int>> g4 = {{0}};
        check(Solution().shortestPathBinaryMatrix(g4) == 1, "1x1 -> 1");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
