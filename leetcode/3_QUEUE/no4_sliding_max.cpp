/**
 * @file no4_sliding_window_maximum.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 239: Sliding Window Maximum
 * @difficulty Hard
 * @link https://leetcode.com/problems/sliding-window-maximum/
 * 
 * @details
 * Problem Description:
 * You are given an array of integers `nums`, there is a sliding window of size `k`
 * which is moving from the very left of the array to the very right. You can only
 * see the `k` numbers in the window. Each time the sliding window moves right by
 * one position.
 * 
 * Return the max sliding window.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * - 1 <= k <= nums.length
 */

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

class Solution {
public:
    /**
     * @brief Finds the maximum element in each sliding window of size k.
     * @details This solution uses a Monotonic Queue implemented via a std::deque.
     * The deque stores indices of the elements in `nums` rather than the values.
     * It maintains two properties:
     * 1. Monotonicity: The values corresponding to indices in the deque are stored in strictly decreasing order.
     *    To maintain this, before inserting a new element, we pop all elements from the back of the deque
     *    which are smaller than or equal to the new element.
     * 2. Window Bound: The element at the front of the deque must represent an index within the current window range [i - k + 1, i].
     *    Indices older than `i - k + 1` are popped from the front of the deque.
     * 
     * The maximum value of the current window is always at the index stored at the front of the deque.
     * 
     * @param nums The input array of integers.
     * @param k The size of the sliding window.
     * @return A vector containing the maximum element for each sliding window.
     * 
     * @time_complexity O(N) where N is the number of elements in `nums`. Each index is pushed and popped from the deque at most once.
     * @space_complexity O(K) for the deque storing at most K elements at any time.
     */
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
        std::vector<int> result;
        std::deque<int> dq; // Monotonic deque storing indices of elements

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            // 1. Remove indices that are out of the current sliding window boundary [i - k + 1, i]
            if (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }

            // 2. Remove all elements from the back of the queue that are smaller than or equal to nums[i].
            // These elements can never be the maximum because nums[i] is newer and larger.
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // 3. Append the current element's index to the deque
            dq.push_back(i);

            // 4. The window has size k once the index i reaches k - 1
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};

/**
 * ============================================================================
 *                             MANUAL DRY-RUN TRACE
 * ============================================================================
 * Input: nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
 * Expected Output: [3, 3, 5, 5, 6, 7]
 * 
 * | Step (i) | nums[i] | Window Range [i-k+1, i] | Action / Deque State (Indices) | Deque Values      | Output Added     |
 * | :---:    | :---:   | :---:                   | :---                           | :---              | :---             |
 * | **0**    | 1       | [ -2, 0 ]               | Push index 0. dq = [0]         | [1]               | - (i < k-1)      |
 * | **1**    | 3       | [ -1, 1 ]               | 1 <= 3, pop 0. Push 1. dq = [1]| [3]               | - (i < k-1)      |
 * | **2**    | -1      | [ 0, 2 ]                | Push 2. dq = [1, 2]            | [3, -1]           | nums[1] = 3      |
 * | **3**    | -3      | [ 1, 3 ]                | Push 3. dq = [1, 2, 3]         | [3, -1, -3]       | nums[1] = 3      |
 * | **4**    | 5       | [ 2, 4 ]                | Pop 1 (out of range, 1 < 2).   |                   |                  |
 * |          |         |                         | Pop 3, 2 (value <= 5).         |                   |                  |
 * |          |         |                         | Push 4. dq = [4]               | [5]               | nums[4] = 5      |
 * | **5**    | 3       | [ 3, 5 ]                | Push 5. dq = [4, 5]            | [5, 3]            | nums[4] = 5      |
 * | **6**    | 6       | [ 4, 6 ]                | Pop 5, 4 (value <= 6).         |                   |                  |
 * |          |         |                         | Push 6. dq = [6]               | [6]               | nums[6] = 6      |
 * | **7**    | 7       | [ 5, 7 ]                | Pop 6 (value <= 7).            |                   |                  |
 * |          |         |                         | Push 7. dq = [7]               | [7]               | nums[7] = 7      |
 * 
 * Final output vector: [3, 3, 5, 5, 6, 7]
 */

int main() {
    Solution solver;
    
    // Test Case 1: Standard Example
    std::vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    std::vector<int> expected1 = {3, 3, 5, 5, 6, 7};
    assert(solver.maxSlidingWindow(nums1, k1) == expected1);

    // Test Case 2: Array size equals window size (k)
    std::vector<int> nums2 = {1, -1};
    int k2 = 1;
    std::vector<int> expected2 = {1, -1};
    assert(solver.maxSlidingWindow(nums2, k2) == expected2);

    // Test Case 3: Decreasing Array
    std::vector<int> nums3 = {5, 4, 3, 2, 1};
    int k3 = 3;
    std::vector<int> expected3 = {5, 4, 3};
    assert(solver.maxSlidingWindow(nums3, k3) == expected3);

    // Test Case 4: Increasing Array
    std::vector<int> nums4 = {1, 2, 3, 4, 5};
    int k4 = 2;
    std::vector<int> expected4 = {2, 3, 4, 5};
    assert(solver.maxSlidingWindow(nums4, k4) == expected4);

    std::cout << "All assertions for Sliding Window Maximum passed successfully!" << std::endl;
    return 0;
}
