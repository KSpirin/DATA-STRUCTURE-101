/**
 * @file no7_remove_duplicate_letters.cpp
 * @brief LeetCode 316 - Remove Duplicate Letters
 * @details Difficulty: Medium
 * @link https://leetcode.com/problems/remove-duplicate-letters/
 *
 * @description
 * Given a string s, remove duplicate letters so that every letter appears once and only once.
 * You must make sure your result is the smallest in lexicographical order among all possible results.
 * Note: This problem is the same as LeetCode 1081: Smallest Subsequence of Distinct Characters.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>

class Solution {
public:
    /**
     * @brief Removes duplicate letters to form the lexicographically smallest subsequence of unique letters.
     * @param s The input string.
     * @return The lexicographically smallest unique character subsequence string.
     *
     * Time Complexity: O(N) where N is the length of string s. Each character is pushed and popped at most once.
     * Space Complexity: O(1) auxiliary space (since the alphabet size is fixed to 26 characters).
     */
    std::string removeDuplicateLetters(std::string s) {
        std::vector<int> count(26, 0);       // Track the remaining count of each character
        std::vector<bool> in_stack(26, false); // Track if a character is currently in the stack
        std::string result = "";              // We can use a std::string as a stack to avoid reversing later

        // Count frequencies of all characters in the input string
        for (char c : s) {
            count[c - 'a']++;
        }

        for (char c : s) {
            // Decrement remaining count for the current character
            count[c - 'a']--;

            // If the character is already in the result stack, skip it
            if (in_stack[c - 'a']) {
                continue;
            }

            // Pop characters from the stack if:
            // 1. The stack is not empty.
            // 2. The top character is lexicographically greater than the current character 'c'.
            // 3. The top character appears again later in the string (count > 0).
            while (!result.empty() && result.back() > c && count[result.back() - 'a'] > 0) {
                in_stack[result.back() - 'a'] = false;
                result.pop_back();
            }

            // Push current character to the stack and mark as visited
            result.push_back(c);
            in_stack[c - 'a'] = true;
        }

        return result;
    }
};

/*
 * ==========================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================
 * Input string: s = "bcabc"
 *
 * Initial state:
 * - count table: [a:1, b:2, c:2] (rest 0)
 * - in_stack table: [a:false, b:false, c:false]
 * - result stack: ""
 *
 * Step | i | Char | count[char] | in_stack? | Loop Condition & Action                     | Stack State (result) | in_stack updates
 * -----|---|------|-------------|-----------|---------------------------------------------|----------------------|----------------------
 * 1    | 0 | 'b'  | 2 -> 1      | false     | push 'b'                                    | "b"                  | b: true
 * 2    | 1 | 'c'  | 2 -> 1      | false     | 'c' > 'b', push 'c'                         | "bc"                 | c: true
 * 3    | 2 | 'a'  | 1 -> 0      | false     | 'c' > 'a' & count['c']>0 (1): pop 'c'       | "b"                  | c: false
 *      |   |      |             |           | 'b' > 'a' & count['b']>0 (1): pop 'b'       | ""                   | b: false
 *      |   |      |             |           | push 'a'                                    | "a"                  | a: true
 * 4    | 3 | 'b'  | 1 -> 0      | false     | 'b' > 'a', push 'b'                         | "ab"                 | b: true
 * 5    | 4 | 'c'  | 1 -> 0      | false     | 'c' > 'b', push 'c'                         | "abc"                | c: true
 *
 * Final Result: "abc"
 *
 * ==========================================
 * Complexity Analysis:
 * ==========================================
 * Time Complexity: O(N)
 * - We iterate through the string of length N twice. Once for counting, once for building the result.
 * - Each character is pushed to the stack (appended to result string) once.
 * - Each character is popped from the stack at most once.
 * - Checking if a character exists in the stack is O(1) via the in_stack array.
 * - Total time: O(N).
 *
 * Space Complexity: O(1)
 * - The count and in_stack arrays are of fixed size 26 (size of lowercase English alphabet).
 * - The result string (which acts as a stack) can have a maximum size of 26.
 * - Thus, space complexity is O(1) auxiliary space.
 */

int main() {
    Solution solver;

    // Test Case 1
    std::string s1 = "bcabc";
    assert(solver.removeDuplicateLetters(s1) == "abc");
    std::cout << "Test case 1 passed: " << s1 << " -> \"abc\"" << std::endl;

    // Test Case 2
    std::string s2 = "cbacdcbc";
    assert(solver.removeDuplicateLetters(s2) == "acdb");
    std::cout << "Test case 2 passed: " << s2 << " -> \"acdb\"" << std::endl;

    // Test Case 3
    std::string s3 = "bbca";
    assert(solver.removeDuplicateLetters(s3) == "bca");
    std::cout << "Test case 3 passed: " << s3 << " -> \"bca\"" << std::endl;

    return 0;
}
