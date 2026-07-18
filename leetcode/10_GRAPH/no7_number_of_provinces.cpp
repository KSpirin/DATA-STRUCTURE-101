/**
 * @brief LeetCode 547 - Number of Provinces
 * @difficulty Medium
 * @link https://leetcode.com/problems/number-of-provinces/
 *
 * Problem:
 * Count connected components (provinces) in adjacency matrix.
 * 
 * Example: [[1,1,0],[1,1,0],[0,0,1]] -> 2
 * 
 * Constraints: 1 <= n <= 200 */

#include <iostream>
#include <vector>
#include <cassert>

class Solution {
public:
    int findCircleNum(std::vector<std::vector<int>>& isConnected) {
        // TODO (DFS/BFS or Union-Find)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<int>> g1={{1,1,0},{1,1,0},{0,0,1}};
        check(Solution().findCircleNum(g1)==2,"2 provinces");
    }
    {
        std::vector<std::vector<int>> g2={{1,0,0},{0,1,0},{0,0,1}};
        check(Solution().findCircleNum(g2)==3,"all isolated -> 3");
    }
    {
        std::vector<std::vector<int>> g3={{1,1,1},{1,1,1},{1,1,1}};
        check(Solution().findCircleNum(g3)==1,"all connected -> 1");
    }
    {
        std::vector<std::vector<int>> g4={{1}};
        check(Solution().findCircleNum(g4)==1,"1 city -> 1 province");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
