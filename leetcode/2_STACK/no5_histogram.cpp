/**
 * @file no5_largest_rectangle_histogram.cpp
 * @brief LeetCode 84 - Largest Rectangle in Histogram
 * @details Difficulty: Hard
 * @link https://leetcode.com/problems/largest-rectangle-in-histogram/
 *
 * @description
 * Given an array of integers heights representing the histogram's bar height
 * where the width of each bar is 1, return the area of the largest rectangle
 * in the histogram.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>

class Solution {
public:
    /**
     * @brief Computes the largest rectangle area in a histogram.
     * @param heights A vector of bar heights.
     * @return The maximum rectangle area.
     * 
     * Time Complexity: O(N) where N is the number of bars. Each index is pushed and popped at most once.
     * Space Complexity: O(N) in the worst case for the monotonic stack.
     */
    int largestRectangleArea(std::vector<int>& heights) {
        std::stack<int> index_stack;
        int max_area = 0;
        
        // We append a dummy height of 0 at the end of the heights array.
        // This ensures that all remaining elements in the stack are popped 
        // and processed before the function returns.
        std::vector<int> extended_heights = heights;
        extended_heights.push_back(0);
        
        for (int i = 0; i < static_cast<int>(extended_heights.size()); ++i) {
            // While the current bar is shorter than the bar at the top of the stack,
            // we pop the top bar and calculate the area of the rectangle with that popped bar
            // as the smallest/limiting height.
            while (!index_stack.empty() && extended_heights[i] < extended_heights[index_stack.top()]) {
                int height = extended_heights[index_stack.top()];
                index_stack.pop();
                
                // The right boundary is the current index 'i' (exclusive)
                // The left boundary is the new top of the stack (exclusive). 
                // If the stack is empty, it means there are no elements to the left 
                // that are shorter than 'height', so the left boundary is -1.
                int left_boundary = index_stack.empty() ? -1 : index_stack.top();
                int width = i - left_boundary - 1;
                
                max_area = std::max(max_area, height * width);
            }
            
            // Push the current index onto the stack to maintain monotonic increasing order
            index_stack.push(i);
        }
        
        return max_area;
    }
};

/*
 * ==========================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================
 * Input heights: [ 2, 1, 5, 6, 2, 3 ]
 * Extended heights (with dummy 0): [ 2, 1, 5, 6, 2, 3, 0 ], Size = 7
 *
 * Step | i | H[i] | Stack (Bottom->Top) | Action / Computation                             | max_area | Notes
 * -----|---|------|---------------------|--------------------------------------------------|----------|-----------------------------------------
 * 0    | 0 | 2    | [ 0 ]               | Push 0                                           | 0        | Stack empty, just push
 * 1    | 1 | 1    | [ ]                 | H[0]=2 > H[1]=1. Pop 0.                          | 2        |
 *      |   |      |                     | height = 2, left = -1, width = 1 - (-1) - 1 = 1.  |          | Area = 2 * 1 = 2.
 *      |   |      | [ 1 ]               | Push 1                                           | 2        | Maintain order
 * 2    | 2 | 5    | [ 1, 2 ]            | H[2]=5 >= H[1]=1. Push 2                         | 2        | Monotonic increasing
 * 3    | 3 | 6    | [ 1, 2, 3 ]         | H[3]=6 >= H[2]=5. Push 3                         | 2        | Monotonic increasing
 * 4    | 4 | 2    | [ 1, 2 ]            | H[4]=2 < H[3]=6. Pop 3.                          | 6        |
 *      |   |      |                     | height = 6, left = 2, width = 4 - 2 - 1 = 1.     |          | Area = 6 * 1 = 6.
 *      |   |      | [ 1 ]               | H[4]=2 < H[2]=5. Pop 2.                          | 10       |
 *      |   |      |                     | height = 5, left = 1, width = 4 - 1 - 1 = 2.     |          | Area = 5 * 2 = 10.
 *      |   |      | [ 1, 4 ]            | H[4]=2 >= H[1]=1. Push 4                         | 10       | Maintain order
 * 5    | 5 | 3    | [ 1, 4, 5 ]         | H[5]=3 >= H[4]=2. Push 5                         | 10       | Monotonic increasing
 * 6    | 6 | 0    | [ 1, 4 ]            | H[6]=0 < H[5]=3. Pop 5.                          | 10       |
 *      |   |      |                     | height = 3, left = 4, width = 6 - 4 - 1 = 1.     |          | Area = 3 * 1 = 3.
 *      |   |      | [ 1 ]               | H[6]=0 < H[4]=2. Pop 4.                          | 10       |
 *      |   |      |                     | height = 2, left = 1, width = 6 - 1 - 1 = 4.     |          | Area = 2 * 4 = 8.
 *      |   |      | [ ]                 | H[6]=0 < H[1]=1. Pop 1.                          | 10       |
 *      |   |      |                     | height = 1, left = -1, width = 6 - (-1) - 1 = 6.  |          | Area = 1 * 6 = 6.
 *      |   |      | [ 6 ]               | Push 6                                           | 10       | End of loop
 *
 * End of loop. Returns max_area = 10.
 *
 * ==========================================
 * Complexity Analysis:
 * ==========================================
 * Time Complexity: O(N)
 * - Each bar index is pushed onto the stack exactly once and popped at most once.
 * - The while loop condition runs at most N times in total over the entire execution.
 * - This amortized analysis guarantees O(N) linear runtime.
 *
 * Space Complexity: O(N)
 * - The extended_heights vector takes O(N) memory.
 * - The stack stores at most N indices (e.g., when heights are strictly increasing).
 * - Total auxiliary space is O(N).
 */

int main() {
    Solution solver;
    
    // Test Case 1: Standard case with peaks and valleys
    std::vector<int> h1 = {2, 1, 5, 6, 2, 3};
    assert(solver.largestRectangleArea(h1) == 10);
    std::cout << "Test case 1 passed: {2, 1, 5, 6, 2, 3} -> 10" << std::endl;

    // Test Case 2: Sorted ascending heights
    std::vector<int> h2 = {1, 2, 3, 4, 5};
    assert(solver.largestRectangleArea(h2) == 9); // rectangle [3, 4, 5] -> width=3, min_height=3, area=9
    std::cout << "Test case 2 passed: {1, 2, 3, 4, 5} -> 9" << std::endl;

    // Test Case 3: All equal heights
    std::vector<int> h3 = {2, 2, 2, 2};
    assert(solver.largestRectangleArea(h3) == 8); // height 2, width 4 -> area 8
    std::cout << "Test case 3 passed: {2, 2, 2, 2} -> 8" << std::endl;

    // Test Case 4: Single element
    std::vector<int> h4 = {4};
    assert(solver.largestRectangleArea(h4) == 4);
    std::cout << "Test case 4 passed: {4} -> 4" << std::endl;

    return 0;
}
