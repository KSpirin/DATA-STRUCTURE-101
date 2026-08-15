/**
 * @brief LeetCode 150 - Evaluate Reverse Polish Notation
 * @difficulty Medium
 * @link https://leetcode.com/problems/evaluate-reverse-polish-notation/
 *
 * Problem:
 * Evaluate arithmetic expression in Reverse Polish Notation.
 * Operators: +, -, *, /. Division truncates toward zero.
 * 
 * Example: ["4","13","5","/","+"] -> 6
 * 
 * Constraints: 1 <= tokens.length <= 10^4 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cassert>

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<std::string> t1 = {"2","1","+","3","*"};
        check(Solution().evalRPN(t1) == 9, "(2+1)*3 == 9");
    }
    {
        std::vector<std::string> t2 = {"4","13","5","/","+"};
        check(Solution().evalRPN(t2) == 6, "4+(13/5) == 6");
    }
    {
        std::vector<std::string> t3 = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
        check(Solution().evalRPN(t3) == 22, "complex expr == 22");
    }
    {
        std::vector<std::string> t4 = {"3","4","+"};
        check(Solution().evalRPN(t4) == 7, "3+4 == 7");
    }
    {
        std::vector<std::string> t5 = {"5","1","2","+","4","*","+","3","-"};
        check(Solution().evalRPN(t5) == 14, "5+((1+2)*4)-3 == 14");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
