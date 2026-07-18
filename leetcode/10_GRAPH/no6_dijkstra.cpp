/**
 * @brief LeetCode 743 - Network Delay Time (Dijkstra)
 * @difficulty Medium
 * @link https://leetcode.com/problems/network-delay-time/
 *
 * Problem:
 * Minimum time for signal from k to reach all n nodes. -1 if impossible.
 * 
 * Example: times=[[2,1,1],[2,3,1],[3,4,1]], n=4, k=2 -> 2
 * 
 * Constraints: 1 <= k <= n <= 100 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        // TODO (min-heap Dijkstra)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<int>> t1={{2,1,1},{2,3,1},{3,4,1}};
        check(Solution().networkDelayTime(t1,4,2)==2,"2->1,2->3->4 max=2");
    }
    {
        std::vector<std::vector<int>> t2={{1,2,1}};
        check(Solution().networkDelayTime(t2,2,1)==1,"direct edge -> 1");
    }
    {
        std::vector<std::vector<int>> t3={{1,2,1}};
        check(Solution().networkDelayTime(t3,2,2)==-1,"node 2 cannot reach 1 -> -1");
    }
    {
        std::vector<std::vector<int>> t4={{1,2,1},{2,3,2},{1,3,4}};
        check(Solution().networkDelayTime(t4,3,1)==3,"1->2->3 costs 3 < direct 4");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
