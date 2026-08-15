/**
 * @brief LeetCode 973 - K Closest Points to Origin
 * @difficulty Medium
 * @link https://leetcode.com/problems/k-closest-points-to-origin/
 *
 * Problem:
 * Return the k closest points to origin. Distance = sqrt(x^2+y^2).
 * 
 * Example: [[1,3],[-2,2]], k=1 -> [[-2,2]]
 * 
 * Constraints: 1 <= k <= points.length <= 10^4 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
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
        std::vector<std::vector<int>> p1={{1,3},{-2,2}};
        auto r=Solution().kClosest(p1,1);
        check(r.size()==1&&r[0][0]==-2&&r[0][1]==2,"closest of (1,3),(-2,2) is (-2,2)");
    }
    {
        std::vector<std::vector<int>> p2={{3,3},{5,-1},{-2,4}};
        auto r=Solution().kClosest(p2,2);
        check(r.size()==2,"k=2 -> 2 results");
    }
    {
        std::vector<std::vector<int>> p3={{0,1}};
        auto r=Solution().kClosest(p3,1);
        check(r[0][0]==0&&r[0][1]==1,"single point -> itself");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
