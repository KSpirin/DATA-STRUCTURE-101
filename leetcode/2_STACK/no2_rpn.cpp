/**
 * @file no2_evaluate_rpn.cpp
 * @brief LeetCode 150 - Evaluate Reverse Polish Notation
 * @details Difficulty: Medium
 * @link https://leetcode.com/problems/evaluate-reverse-polish-notation/
 *
 * @description
 * You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.
 * Valid operators are '+', '-', '*', and '/'. Each operand may be an integer or another expression.
 * The division between two integers always truncates toward zero.
 * It is guaranteed that the given RPN expression is always valid. That means the expression would always evaluate
 * to a result, and there will not be any division by zero operations.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cassert>

class Solution {
public:
    /**
     * @brief Evaluates the value of an arithmetic expression in Reverse Polish Notation.
     * @param tokens List of operands and operators.
     * @return The evaluated integer result.
     *
     * Time Complexity: O(N) where N is the number of tokens. We process each token exactly once.
     * Space Complexity: O(N) in the worst case (e.g., all tokens are operands except the last few).
     */
    int evalRPN(std::vector<std::string>& tokens) {
        std::stack<long long> val_stack;

        for (const std::string& token : tokens) {
            // Check if the current token is an operator
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Pop the second operand first (due to LIFO behavior)
                long long operand2 = val_stack.top();
                val_stack.pop();

                // Pop the first operand second
                long long operand1 = val_stack.top();
                val_stack.pop();

                long long result = 0;
                if (token == "+") {
                    result = operand1 + operand2;
                } else if (token == "-") {
                    result = operand1 - operand2;
                } else if (token == "*") {
                    result = operand1 * operand2;
                } else if (token == "/") {
                    // Division truncates toward zero by default in C++ integer division
                    result = operand1 / operand2;
                }

                // Push the result back onto the stack
                val_stack.push(result);
            } else {
                // The token is an operand (integer), convert it and push onto the stack
                val_stack.push(std::stoll(token));
            }
        }

        // The remaining element on the stack is the final result of the expression
        return static_cast<int>(val_stack.top());
    }
};

/*
 * ==========================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================
 * Input tokens: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
 * 
 * Token | Type     | Action                            | Stack State (Bottom -> Top)   | Computation
 * ------|----------|-----------------------------------|-------------------------------|------------------------
 * "10"  | Operand  | Push 10                           | [ 10 ]                        | -
 * "6"   | Operand  | Push 6                            | [ 10, 6 ]                     | -
 * "9"   | Operand  | Push 9                            | [ 10, 6, 9 ]                  | -
 * "3"   | Operand  | Push 3                            | [ 10, 6, 9, 3 ]               | -
 * "+"   | Operator | Pop 3 & 9, Push 9 + 3 = 12        | [ 10, 6, 12 ]                 | 9 + 3 = 12
 * "-11" | Operand  | Push -11                          | [ 10, 6, 12, -11 ]            | -
 * "*"   | Operator | Pop -11 & 12, Push 12 * -11 = -132| [ 10, 6, -132 ]               | 12 * (-11) = -132
 * "/"   | Operator | Pop -132 & 6, Push 6 / -132 = 0   | [ 10, 0 ]                     | 6 / -132 = 0 (truncated)
 * "*"   | Operator | Pop 0 & 10, Push 10 * 0 = 0       | [ 0 ]                         | 10 * 0 = 0
 * "17"  | Operand  | Push 17                           | [ 0, 17 ]                     | -
 * "+"   | Operator | Pop 17 & 0, Push 0 + 17 = 17      | [ 17 ]                        | 0 + 17 = 17
 * "5"   | Operand  | Push 5                            | [ 17, 5 ]                     | -
 * "+"   | Operator | Pop 5 & 17, Push 17 + 5 = 22      | [ 22 ]                        | 17 + 5 = 22
 *
 * Final Result: 22
 *
 * ==========================================
 * Complexity Analysis:
 * ==========================================
 * Time Complexity: O(N)
 * - We traverse the array of strings of size N exactly once.
 * - For each token, we perform constant time O(1) operations: parsing a number or popping/pushing stack.
 *
 * Space Complexity: O(N)
 * - In the worst-case scenario (e.g., all tokens are numbers followed by operators at the end),
 *   the stack will store up to N/2 + 1 elements.
 */

int main() {
    Solution solver;

    // Test case 1: Standard expression
    std::vector<std::string> tokens1 = {"2", "1", "+", "3", "*"};
    // (2 + 1) * 3 = 9
    assert(solver.evalRPN(tokens1) == 9);
    std::cout << "Test case 1 passed: Result = 9" << std::endl;

    // Test case 2: Division and truncation
    std::vector<std::string> tokens2 = {"4", "13", "5", "/", "+"};
    // 4 + (13 / 5) = 4 + 2 = 6
    assert(solver.evalRPN(tokens2) == 6);
    std::cout << "Test case 2 passed: Result = 6" << std::endl;

    // Test case 3: Larger expression with negatives
    std::vector<std::string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    assert(solver.evalRPN(tokens3) == 22);
    std::cout << "Test case 3 passed: Result = 22" << std::endl;

    return 0;
}
