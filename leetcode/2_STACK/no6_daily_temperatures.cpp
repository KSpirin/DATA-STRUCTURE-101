/**
 * @brief LeetCode 739 - Daily Temperatures
 * @difficulty Medium
 * @link https://leetcode.com/problems/daily-temperatures/
 *
 * Problem:
 * For each day, return how many days until a warmer temperature. 0 if none.
 * 
 * Example: [73,74,75,71,69,72,76,73] -> [1,1,4,2,1,1,0,0]
 * 
 * Constraints: 1 <= temperatures.length <= 10^5 */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
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
        std::vector<int> t1 = {73,74,75,71,69,72,76,73};
        auto r = Solution().dailyTemperatures(t1);
        check(r[0]==1 && r[2]==4 && r[7]==0, "standard case");
    }
    {
        std::vector<int> t2 = {30,40,50,60};
        auto r = Solution().dailyTemperatures(t2);
        check(r[0]==1 && r[1]==1 && r[2]==1 && r[3]==0, "strictly increasing");
    }
    {
        std::vector<int> t3 = {60,50,40,30};
        auto r = Solution().dailyTemperatures(t3);
        check(r[0]==0 && r[1]==0 && r[3]==0, "strictly decreasing");
    }
    {
        std::vector<int> t4 = {55};
        auto r = Solution().dailyTemperatures(t4);
        check(r[0]==0, "single element -> 0");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
