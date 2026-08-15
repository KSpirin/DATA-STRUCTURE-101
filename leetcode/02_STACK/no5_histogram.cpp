/**
 * @brief LeetCode 84 - Largest Rectangle in Histogram
 * @difficulty Hard
 * @link https://leetcode.com/problems/largest-rectangle-in-histogram/
 *
 * Problem:
 * Return the area of the largest rectangle that can be formed in a histogram.
 * 
 * Example: [2,1,5,6,2,3] -> 10
 * 
 * Constraints: 1 <= heights.length <= 10^5 */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
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
        std::vector<int> h1 = {2,1,5,6,2,3};
        check(Solution().largestRectangleArea(h1) == 10, "[2,1,5,6,2,3] -> 10");
    }
    {
        std::vector<int> h2 = {2,4};
        check(Solution().largestRectangleArea(h2) == 4, "[2,4] -> 4");
    }
    {
        std::vector<int> h3 = {1};
        check(Solution().largestRectangleArea(h3) == 1, "[1] -> 1");
    }
    {
        std::vector<int> h4 = {1,1,1,1};
        check(Solution().largestRectangleArea(h4) == 4, "[1,1,1,1] -> 4");
    }
    {
        std::vector<int> h5 = {5,4,3,2,1};
        check(Solution().largestRectangleArea(h5) == 9, "decreasing -> 9");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
