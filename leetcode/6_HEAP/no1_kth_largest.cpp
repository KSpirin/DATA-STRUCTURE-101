/**
 * @brief LeetCode 215 - Kth Largest Element
 * @difficulty Medium
 * @link https://leetcode.com/problems/kth-largest-element-in-an-array/
 *
 * Problem:
 * Return the kth largest element.
 * 
 * Example: [3,2,1,5,6,4], k=2 -> 5
 * 
 * Constraints: 1 <= k <= nums.length <= 10^5 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        // TODO (min-heap of size k)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<int> n1={3,2,1,5,6,4};
        check(Solution().findKthLargest(n1,2)==5,"[3,2,1,5,6,4] k=2 -> 5");
    }
    {
        std::vector<int> n2={3,2,3,1,2,4,5,5,6};
        check(Solution().findKthLargest(n2,4)==4,"k=4 -> 4");
    }
    {
        std::vector<int> n3={1};
        check(Solution().findKthLargest(n3,1)==1,"[1] k=1 -> 1");
    }
    {
        std::vector<int> n4={7,6,5,4,3,2,1};
        check(Solution().findKthLargest(n4,1)==7,"k=1 -> max=7");
        check(Solution().findKthLargest(n4,7)==1,"k=7 -> min=1");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
