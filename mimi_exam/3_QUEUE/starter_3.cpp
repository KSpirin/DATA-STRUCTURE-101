#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

// PROBLEM: LeetCode 239 - Sliding Window Maximum
// For each window of size k, return the maximum element.
// - Remove indices outside the window from the FRONT
// - Remove indices with smaller values from the BACK (they can never be max)

class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
        // TODO:
        // - Create result vector and deque dq
        // - For each index i:
        //   1. If dq.front() is out of window (== i-k), pop front
        //   2. While dq not empty AND nums[dq.back()] < nums[i], pop back
        //   3. Push i to back of dq
        //   4. If i >= k-1, push nums[dq.front()] to result

        return {};
    }
};

int main() {
    // {1,3,-1,-3,5} with k=3 -> {3,3,5}
    std::vector<int> nums = {1, 3, -1, -3, 5};
    std::vector<int> res = Solution().maxSlidingWindow(nums, 3);
    assert(res[0] == 3 && res[1] == 3 && res[2] == 5);
    std::cout << "3_QUEUE Coding 3 Passed!" << std::endl;
    return 0;
}
