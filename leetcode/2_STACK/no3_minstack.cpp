/**
 * @brief LeetCode 155 - Min Stack
 * @difficulty Medium
 * @link https://leetcode.com/problems/min-stack/
 *
 * Problem:
 * Stack that supports getMin() in O(1).
 * 
 * Example: push(-2,0,-3), getMin()==-3, pop(), getMin()==-2
 * 
 * Constraints: -2^31 <= val <= 2^31-1 */

#include <iostream>
#include <stack>
#include <cassert>
#include <string>

class MinStack {
public:
    void push(int val) { // TODO
    }
    void pop() { // TODO
    }
    int top() { // TODO
    }
    int getMin() { // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        MinStack ms;
        ms.push(-2); ms.push(0); ms.push(-3);
        check(ms.getMin() == -3, "min after push(-2,0,-3) == -3");
        ms.pop();
        check(ms.top() == 0,    "top after pop == 0");
        check(ms.getMin() == -2,"min after pop == -2");
    }
    {
        MinStack ms2;
        ms2.push(1);
        check(ms2.getMin() == 1, "single element min == 1");
        ms2.push(0);
        check(ms2.getMin() == 0, "min updates to 0");
        ms2.pop();
        check(ms2.getMin() == 1, "min restores to 1 after pop");
    }
    {
        MinStack ms3;
        ms3.push(5); ms3.push(3); ms3.push(7);
        check(ms3.getMin() == 3, "min of 5,3,7 == 3");
        ms3.pop();
        check(ms3.getMin() == 3, "min still 3 after removing 7");
        ms3.pop();
        check(ms3.getMin() == 5, "min now 5 after removing 3");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
