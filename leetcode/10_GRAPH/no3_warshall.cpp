/**
 * @brief Custom - Warshall's Transitive Closure
 * @difficulty Custom
 *
 * Problem:
 * Compute transitive closure using Warshall's algorithm.
 * Triple loop: for each k (intermediate): reach[i][j] |= reach[i][k] & reach[k][j]
 * 
 * Example: 0->1->2->3: reach[0][3] becomes 1 */

#include <iostream>
#include <vector>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<int>> warshall(std::vector<std::vector<int>> reach) {
        // TODO: triple loop k, i, j
        // if reach[i][k] && reach[k][j] -> reach[i][j] = 1
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<int>> g={{0,1,0,0},{0,0,1,0},{0,0,0,1},{0,0,0,0}};
        auto r=Solution().warshall(g);
        check(r[0][3]==1,"0 can reach 3");
        check(r[1][3]==1,"1 can reach 3");
        check(r[3][0]==0,"3 cannot reach 0");
        check(r[2][0]==0,"2 cannot reach 0");
    }
    {
        std::vector<std::vector<int>> g2={{0,0},{0,0}};
        auto r=Solution().warshall(g2);
        check(r[0][1]==0,"no edges -> no reachability");
    }
    {
        std::vector<std::vector<int>> g3={{1,1},{0,1}};
        auto r=Solution().warshall(g3);
        check(r[0][1]==1,"direct edge preserved");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
