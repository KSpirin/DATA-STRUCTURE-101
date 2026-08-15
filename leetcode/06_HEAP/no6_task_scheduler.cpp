/**
 * @brief LeetCode 621 - Task Scheduler
 * @difficulty Medium
 * @link https://leetcode.com/problems/task-scheduler/
 *
 * Problem:
 * Return minimum intervals to finish all tasks with cooldown n between same-type tasks.
 * 
 * Example: ['A','A','A','B','B','B'], n=2 -> 8
 * 
 * Constraints: 1 <= tasks.length <= 10^4, 0 <= n <= 100 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cassert>

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
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
        std::vector<char> t1={'A','A','A','B','B','B'};
        check(Solution().leastInterval(t1,2)==8,"AAA BBB n=2 -> 8");
    }
    {
        std::vector<char> t2={'A','A','A','B','B','B'};
        check(Solution().leastInterval(t2,0)==6,"n=0 -> 6 (no cooldown)");
    }
    {
        std::vector<char> t3={'A','A','A','A','A','A','B','C','D','E','F','G'};
        check(Solution().leastInterval(t3,2)==16,"heavy A n=2 -> 16");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
