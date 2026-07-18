/**
 * @brief LeetCode 207 - Course Schedule
 * @difficulty Medium
 * @link https://leetcode.com/problems/course-schedule/
 *
 * Problem:
 * Return true if all courses can be finished (no cycle).
 * 
 * Example: n=2, [[1,0]] -> true; [[1,0],[0,1]] -> false
 * 
 * Constraints: 1 <= numCourses <= 2000 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        // TODO (Kahn's algorithm or DFS cycle detection)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::vector<int>> p1={{1,0}};
        check(Solution().canFinish(2,p1)==true,"2 courses, 0->1 -> true");
    }
    {
        std::vector<std::vector<int>> p2={{1,0},{0,1}};
        check(Solution().canFinish(2,p2)==false,"cycle -> false");
    }
    {
        std::vector<std::vector<int>> p3;
        check(Solution().canFinish(1,p3)==true,"single course -> true");
    }
    {
        std::vector<std::vector<int>> p4={{1,0},{2,1},{3,2}};
        check(Solution().canFinish(4,p4)==true,"chain 0->1->2->3 -> true");
    }
    {
        std::vector<std::vector<int>> p5={{1,0},{2,1},{0,2}};
        check(Solution().canFinish(3,p5)==false,"3-cycle -> false");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
