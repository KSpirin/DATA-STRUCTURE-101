/**
 * @brief LeetCode 239 - Sliding Window Maximum
 * @difficulty Hard
 * @link https://leetcode.com/problems/sliding-window-maximum/
 *
 * Problem:
 * Return max of each sliding window of size k.
 * 
 * Example: [1,3,-1,-3,5,3,6,7], k=3 -> [3,3,5,5,6,7]
 * 
 * Constraints: 1 <= k <= nums.length <= 10^5 */

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
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
        std::vector<int> n1 = {1,3,-1,-3,5,3,6,7};
        auto r = Solution().maxSlidingWindow(n1, 3);
        check(r[0]==3 && r[1]==3 && r[2]==5 && r[5]==7, "standard k=3");
    }
    {
        std::vector<int> n2 = {1};
        auto r = Solution().maxSlidingWindow(n2, 1);
        check(r[0]==1, "single element k=1");
    }
    {
        std::vector<int> n3 = {9,11};
        auto r = Solution().maxSlidingWindow(n3, 2);
        check(r[0]==11, "k=2 -> max of both");
    }
    {
        std::vector<int> n4 = {4,3,2,1};
        auto r = Solution().maxSlidingWindow(n4, 2);
        check(r[0]==4 && r[1]==3, "decreasing k=2");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
