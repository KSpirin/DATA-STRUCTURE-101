/**
 * @brief LeetCode 797 - All Paths From Source to Target
 * @difficulty Medium
 * @link https://leetcode.com/problems/all-paths-from-source-to-target/
 *
 * Problem:
 * All paths from node 0 to node n-1 in a DAG.
 * 
 * Example: [[1,2],[3],[3],[]] -> [[0,1,3],[0,2,3]]
 * 
 * Constraints: n == graph.length, 2 <= n <= 15 */

#include <iostream>
#include <vector>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& graph) {
        // TODO (DFS + backtracking)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<int>> g1={{1,2},{3},{3},{}};
        auto r=Solution().allPathsSourceTarget(g1);
        check(r.size()==2,"graph has 2 paths");
        check((r[0]==std::vector<int>{0,1,3}||r[1]==std::vector<int>{0,1,3}),"path 0-1-3 exists");
        check((r[0]==std::vector<int>{0,2,3}||r[1]==std::vector<int>{0,2,3}),"path 0-2-3 exists");
    }
    {
        std::vector<std::vector<int>> g2={{1},{}}; 
        auto r=Solution().allPathsSourceTarget(g2);
        check(r.size()==1&&r[0][0]==0&&r[0][1]==1,"direct path 0->1");
    }
    {
        std::vector<std::vector<int>> g3={{4,3,1},{3,2,4},{3},{4},{}};
        auto r=Solution().allPathsSourceTarget(g3);
        check(r.size()==4,"4 paths in complex graph");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
