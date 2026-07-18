/**
 * @brief LeetCode 684 - Redundant Connection
 * @difficulty Medium
 * @link https://leetcode.com/problems/redundant-connection/
 *
 * Problem:
 * Find the edge that creates a cycle (Union-Find / DSU).
 * 
 * Example: [[1,2],[1,3],[2,3]] -> [2,3]
 * 
 * Constraints: n == edges.length, 3 <= n <= 1000 */

#include <iostream>
#include <vector>
#include <cassert>

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        // TODO (Union-Find: unite returns false on cycle)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<int>> e1={{1,2},{1,3},{2,3}};
        auto r=Solution().findRedundantConnection(e1);
        check(r[0]==2&&r[1]==3,"[1-2,1-3,2-3] -> [2,3]");
    }
    {
        std::vector<std::vector<int>> e2={{1,2},{2,3},{3,4},{1,4},{1,5}};
        auto r=Solution().findRedundantConnection(e2);
        check(r[0]==1&&r[1]==4,"last edge completing cycle");
    }
    {
        std::vector<std::vector<int>> e3={{1,2},{2,3},{1,3}};
        auto r=Solution().findRedundantConnection(e3);
        check(r.size()==2,"result has 2 elements");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
