#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cassert>

// PROBLEM: LeetCode 150 - Evaluate Reverse Polish Notation
// Each token is either a number or an operator (+, -, *, /)
// Use a STACK: push numbers, pop two when you see an operator.

class Solution {
public:
    int evalRPN(const std::vector<std::string>& tokens) {
        // TODO: Iterate through tokens
        // - If token is a number -> push to stack
        // - If token is an operator -> pop b then a, compute (a op b), push result
        // - Return stack top at the end

        return 0;
    }
};

int main() {
    // ["4", "13", "5", "/", "+"] means: 4 + (13 / 5) = 4 + 2 = 6
    std::vector<std::string> expr = {"4", "13", "5", "/", "+"};
    assert(Solution().evalRPN(expr) == 6);
    std::cout << "2_STACK Coding 1 Passed!" << std::endl;
    return 0;
}
