/**
 * @file no1_valid_parentheses.cpp
 * @brief LeetCode 20 - Valid Parentheses
 * @details Difficulty: Easy
 * @link https://leetcode.com/problems/valid-parentheses/
 *
 * @description
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 */

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cassert>

class Solution {
public:
    /**
     * @brief Checks if the input string containing parentheses is valid.
     * @param s The input string.
     * @return true if valid, false otherwise.
     * 
     * Time Complexity: O(N) where N is the length of the string. We iterate through the string exactly once.
     * Space Complexity: O(N) in the worst case (e.g., "(((..."), where we push all characters onto the stack.
     */
    bool isValid(std::string s) {
        // A stack to keep track of the opening parentheses
        std::stack<char> char_stack;
        
        // Hash map to map closing brackets to their corresponding opening brackets
        // This makes matching O(1) and clean.
        std::unordered_map<char, char> bracket_map = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        // Iterate through each character in the string
        for (char c : s) {
            // Check if the character is a closing bracket
            if (bracket_map.count(c)) {
                // If the stack is empty, there is no matching opening bracket for this closing bracket
                if (char_stack.empty()) {
                    return false;
                }
                
                // Get the top element of the stack
                char top_element = char_stack.top();
                
                // If the top element matches the expected opening bracket, pop it
                if (top_element == bracket_map[c]) {
                    char_stack.pop();
                } else {
                    // Mismatched bracket type (e.g., '(' matched with ']')
                    return false;
                }
            } else {
                // It is an opening bracket, push it onto the stack
                char_stack.push(c);
            }
        }

        // If the stack is empty, all opening brackets were successfully matched and closed
        return char_stack.empty();
    }
};

/*
 * ==========================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================
 * Input string: s = "{ [ ] ( ) }"
 *
 * Step | Char | Action                  | Stack State (Bottom -> Top) | Notes
 * -----|------|-------------------------|-----------------------------|-------------------------------------
 * 0    | -    | Initialize Stack        | [ ]                         | Stack is empty
 * 1    | '{'  | Push '{'                | [ '{' ]                     | Opening tag
 * 2    | '['  | Push '['                | [ '{', '[' ]                | Opening tag
 * 3    | ']'  | Pop & Match '[' vs '['  | [ '{' ]                     | Matches bracket_map[']'] = '['
 * 4    | '('  | Push '('                | [ '{', '(' ]                | Opening tag
 * 5    | ')'  | Pop & Match '(' vs '('  | [ '{' ]                     | Matches bracket_map[')'] = '('
 * 6    | '}'  | Pop & Match '{' vs '{'  | [ ]                         | Matches bracket_map['}'] = '{'
 * 
 * End of string: Stack is empty -> returns true.
 *
 * ==========================================
 * Complexity Analysis:
 * ==========================================
 * Time Complexity: O(N)
 * - We loop through the string of length N exactly once.
 * - Map lookups, stack pushes, and stack pops all take O(1) time.
 * - Total time: O(N).
 *
 * Space Complexity: O(N)
 * - In the worst-case scenario, the string contains only opening brackets (e.g., "(((((((["),
 *   requiring us to store all N characters in the stack.
 * - The unordered_map occupies a constant O(1) space since it only stores 3 static mappings.
 */

int main() {
    Solution solver;
    
    // Test Case 1: Valid string
    std::string s1 = "{[]()}";
    assert(solver.isValid(s1) == true);
    std::cout << "Test case 1 passed: \"" << s1 << "\" is valid." << std::endl;

    // Test Case 2: Invalid matching order
    std::string s2 = "([)]";
    assert(solver.isValid(s2) == false);
    std::cout << "Test case 2 passed: \"" << s2 << "\" is invalid." << std::endl;

    // Test Case 3: Extra closing bracket
    std::string s3 = "()[]{}(";
    assert(solver.isValid(s3) == false);
    std::cout << "Test case 3 passed: \"" << s3 << "\" is invalid (unclosed '(')." << std::endl;

    return 0;
}
