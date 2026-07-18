/**
 * @brief LeetCode 200 - Number of Islands
 * @difficulty Medium
 * @link https://leetcode.com/problems/number-of-islands/
 *
 * Problem:
 * Count islands (connected '1' cells, 4-directional).
 * 
 * Example: [[1,1,0],[1,1,0],[0,0,1]] -> 2
 * 
 * Constraints: 1 <= m,n <= 300 */

#include <iostream>
#include <vector>
#include <cassert>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        // TODO (DFS or BFS, mark visited)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<char>> g1={{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
        check(Solution().numIslands(g1)==1,"big island -> 1");
    }
    {
        std::vector<std::vector<char>> g2={{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}};
        check(Solution().numIslands(g2)==3,"3 islands");
    }
    {
        std::vector<std::vector<char>> g3={{'1','0'},{'0','1'}};
        check(Solution().numIslands(g3)==2,"diagonal not connected -> 2");
    }
    {
        std::vector<std::vector<char>> g4={{'0'}};
        check(Solution().numIslands(g4)==0,"all water -> 0");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
