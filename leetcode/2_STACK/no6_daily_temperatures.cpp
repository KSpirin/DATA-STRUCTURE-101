/**
 * @file no6_daily_temperatures.cpp
 * @brief LeetCode 739 - Daily Temperatures
 * @details Difficulty: Medium
 * @link https://leetcode.com/problems/daily-temperatures/
 *
 * @description
 * Given an array of integers temperatures represents the daily temperatures,
 * return an array answer such that answer[i] is the number of days you have to wait
 * after the i-th day to get a warmer temperature. If there is no future day for which
 * this is possible, keep answer[i] == 0 instead.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

class Solution {
public:
    /**
     * @brief Computes the number of days to wait for a warmer temperature.
     * @param temperatures Vector of daily temperatures.
     * @return A vector representing the waiting days.
     *
     * Time Complexity: O(N) where N is the number of elements in temperatures.
     *                  Each element is pushed and popped from the stack at most once.
     * Space Complexity: O(N) for the monotonic stack storing indices.
     */
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        int n = temperatures.size();
        std::vector<int> answer(n, 0);
        std::stack<int> s; // Monotonic decreasing stack storing indices

        for (int i = 0; i < n; ++i) {
            // While the stack is not empty and the current temperature is warmer
            // than the temperature at the index stored at the top of the stack.
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                int prev_index = s.top();
                s.pop();
                answer[prev_index] = i - prev_index;
            }
            s.push(i); // Push the current day index
        }

        return answer;
    }
};

/*
 * ==========================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================
 * Input: temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 * Output array initialized: answer = [0, 0, 0, 0, 0, 0, 0, 0]
 * Stack s stores indices of temperatures in a monotonic decreasing sequence of values.
 *
 * Step | i | Temp | Stack Action & Loop condition | Stack State (Top -> Bottom) | answer updates | Notes
 * -----|---|------|------------------------------|-----------------------------|----------------|--------------------------------------
 * 0    | - | -    | Initialize                   | [ ]                         | [0,0,0,0,0,0,0,0] |
 * 1    | 0 | 73   | push 0                       | [0]                         | [0,0,0,0,0,0,0,0] | s.top()=0 (73)
 * 2    | 1 | 74   | 74 > 73 (s.top()=0): pop 0   | [ ]                         | answer[0] = 1-0 = 1 | 74 is warmer than 73
 *      |   |      | push 1                       | [1]                         | [1,0,0,0,0,0,0,0] | s.top()=1 (74)
 * 3    | 2 | 75   | 75 > 74 (s.top()=1): pop 1   | [ ]                         | answer[1] = 2-1 = 1 | 75 is warmer than 74
 *      |   |      | push 2                       | [2]                         | [1,1,0,0,0,0,0,0] | s.top()=2 (75)
 * 4    | 3 | 71   | 71 <= 75: push 3             | [3, 2]                      | [1,1,0,0,0,0,0,0] | s.top()=3 (71)
 * 5    | 4 | 69   | 69 <= 71: push 4             | [4, 3, 2]                   | [1,1,0,0,0,0,0,0] | s.top()=4 (69)
 * 6    | 5 | 72   | 72 > 69 (s.top()=4): pop 4   | [3, 2]                      | answer[4] = 5-4 = 1 | 72 is warmer than 69
 *      |   |      | 72 > 71 (s.top()=3): pop 3   | [2]                         | answer[3] = 5-3 = 2 | 72 is warmer than 71
 *      |   |      | 72 <= 75 (s.top()=2): push 5 | [5, 2]                      | [1,1,0,2,1,0,0,0] | s.top()=5 (72)
 * 7    | 6 | 76   | 76 > 72 (s.top()=5): pop 5   | [2]                         | answer[5] = 6-5 = 1 | 76 is warmer than 72
 *      |   |      | 76 > 75 (s.top()=2): pop 2   | [ ]                         | answer[2] = 6-2 = 4 | 76 is warmer than 75
 *      |   |      | push 6                       | [6]                         | [1,1,4,2,1,1,0,0] | s.top()=6 (76)
 * 8    | 7 | 73   | 73 <= 76: push 7             | [7, 6]                      | [1,1,4,2,1,1,0,0] | s.top()=7 (73)
 *
 * Final answer: [1, 1, 4, 2, 1, 1, 0, 0]
 *
 * ==========================================
 * Complexity Analysis:
 * ==========================================
 * Time Complexity: O(N)
 * - Although there is a nested while loop, every index from 0 to N-1 is pushed onto the stack
 *   exactly once, and popped from the stack at most once.
 * - This means the while loop executes at most N times in total over the entire process.
 * - Hence, amortized complexity per element is O(1), leading to an overall time complexity of O(N).
 *
 * Space Complexity: O(N)
 * - The stack stores at most N indices in the worst-case scenario (e.g., when temperatures are strictly
 *   decreasing, such as [100, 90, 80, 70], no element is popped until the end or ever).
 * - Output vector requires O(N) space, which is typically required for the output, but the auxiliary space
 *   is O(N) for the stack.
 */

int main() {
    Solution solver;

    // Test Case 1
    std::vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    std::vector<int> expected1 = {1, 1, 4, 2, 1, 1, 0, 0};
    assert(solver.dailyTemperatures(temps1) == expected1);
    std::cout << "Test case 1 passed!" << std::endl;

    // Test Case 2
    std::vector<int> temps2 = {30, 40, 50, 60};
    std::vector<int> expected2 = {1, 1, 1, 0};
    assert(solver.dailyTemperatures(temps2) == expected2);
    std::cout << "Test case 2 passed!" << std::endl;

    // Test Case 3
    std::vector<int> temps3 = {30, 30, 30};
    std::vector<int> expected3 = {0, 0, 0};
    assert(solver.dailyTemperatures(temps3) == expected3);
    std::cout << "Test case 3 passed!" << std::endl;

    return 0;
}
