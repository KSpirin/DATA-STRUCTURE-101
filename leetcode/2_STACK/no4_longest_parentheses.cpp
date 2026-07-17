/**
 * @file no4_longest_valid_parentheses.cpp
 * @brief LeetCode 32 - Longest Valid Parentheses
 * @details Difficulty: Hard
 * @link https://leetcode.com/problems/longest-valid-parentheses/
 *
 * @description
 * Given a string containing just the characters '(' and ')', return the length
 * of the longest valid (well-formed) parentheses substring.
 */

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cassert>

class Solution {
public:
    /**
     * @brief Finds the length of the longest valid parentheses substring.
     * @param s The input string containing only '(' and ')'.
     * @return The length of the longest valid parentheses substring.
     * 
     * Time Complexity: O(N) where N is the length of the string s. We make one pass over the string.
     * Space Complexity: O(N) in the worst case to store indices of brackets on the stack.
     */
    int longestValidParentheses(std::string s) {
        std::stack<int> index_stack;
        // Base case: push -1 onto stack to act as the boundary index before the start of the string.
        // This allows us to calculate lengths of valid substrings starting at index 0 correctly.
        index_stack.push(-1);
        int max_len = 0;

        for (int i = 0; i < static_cast<int>(s.length()); ++i) {
            if (s[i] == '(') {
                // For an opening parenthesis, push its index onto the stack
                index_stack.push(i);
            } else {
                // For a closing parenthesis, pop the last opening parenthesis index (or current boundary)
                index_stack.pop();

                if (index_stack.empty()) {
                    // If the stack is empty, it means we don't have an opening parenthesis to match
                    // this closing parenthesis. Thus, this index 'i' becomes the new boundary of 
                    // invalid parentheses, and we push it onto the stack.
                    index_stack.push(i);
                } else {
                    // If stack is not empty, calculate the length of current valid substring.
                    // The valid substring starts just after the index stored at the top of the stack.
                    max_len = std::max(max_len, i - index_stack.top());
                }
            }
        }

        return max_len;
    }
};

/*
 * ==========================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================
 * Input string: s = ") ( ) ( ) )"
 * Length: N = 6
 *
 * Step | i | Char | Action                      | Stack State (Bottom -> Top) | max_len | Notes
 * -----|---|------|-----------------------------|-----------------------------|---------|-------------------------------------
 * 0    | - | -    | Initialize Stack            | [ -1 ]                      | 0       | Pre-populated with boundary -1
 * 1    | 0 | ')'  | Pop -> Stack Empty          | [ ]                         | 0       | Pop -1. Stack is empty.
 *      |   |      | Push index 0 (New Boundary) | [ 0 ]                       | 0       | Index 0 becomes the new boundary.
 * 2    | 1 | '('  | Push index 1                | [ 0, 1 ]                    | 0       | Opening parenthesis.
 * 3    | 2 | ')'  | Pop index 1                 | [ 0 ]                       | 2       | Match found! len = 2 - 0 = 2. max_len = max(0, 2) = 2.
 * 4    | 3 | '('  | Push index 3                | [ 0, 3 ]                    | 2       | Opening parenthesis.
 * 5    | 4 | ')'  | Pop index 3                 | [ 0 ]                       | 4       | Match found! len = 4 - 0 = 4. max_len = max(2, 4) = 4.
 * 6    | 5 | ')'  | Pop index 0 -> Stack Empty  | [ ]                         | 4       | Pop 0. Stack is empty.
 *      |   |      | Push index 5 (New Boundary) | [ 5 ]                       | 4       | Index 5 becomes the new boundary.
 * 
 * End of loop. Returns max_len = 4.
 *
 * ==========================================
 * Complexity Analysis:
 * ==========================================
 * Time Complexity: O(N)
 * - We iterate through the string of length N exactly once.
 * - Each character is pushed and popped from the stack at most once.
 * - All stack operations (push, pop, top, empty) and standard math comparisons take O(1) time.
 * - Total time: O(N).
 *
 * Space Complexity: O(N)
 * - In the worst-case scenario, the string contains only opening brackets (e.g., "(((((("),
 *   requiring us to store all N indices on the stack.
 * - Total space: O(N).
 */

int main() {
    Solution solver;
    
    // Test Case 1: Standard case with leading and trailing invalid parentheses
    std::string s1 = ")()())";
    assert(solver.longestValidParentheses(s1) == 4);
    std::cout << "Test case 1 passed: \"" << s1 << "\" -> 4" << std::endl;

    // Test Case 2: Simple valid substring
    std::string s2 = "(()";
    assert(solver.longestValidParentheses(s2) == 2);
    std::cout << "Test case 2 passed: \"" << s2 << "\" -> 2" << std::endl;

    // Test Case 3: Empty string
    std::string s3 = "";
    assert(solver.longestValidParentheses(s3) == 0);
    std::cout << "Test case 3 passed: \"" << s3 << "\" -> 0" << std::endl;

    // Test Case 4: Longest nested & consecutive valid parentheses
    std::string s4 = "((())())";
    assert(solver.longestValidParentheses(s4) == 8);
    std::cout << "Test case 4 passed: \"" << s4 << "\" -> 8" << std::endl;

    return 0;
}
