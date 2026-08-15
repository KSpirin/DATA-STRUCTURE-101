/**
 * @brief LeetCode 225 - Implement Stack using Queues
 * @difficulty Easy
 * @link https://leetcode.com/problems/implement-stack-using-queues/
 *
 * Problem:
 * LIFO stack using only two FIFO queues.
 * 
 * Example: push(1),push(2),top()==2,pop()==2
 * 
 * Constraints: 1 <= x <= 9, at most 100 calls */

#include <iostream>
#include <queue>
#include <cassert>
#include <string>

class MyStack {
public:
    void push(int x) { // TODO
    }
    int pop() { // TODO
    }
    int top() { // TODO
    }
    bool empty() { // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        MyStack s;
        check(s.empty() == true, "initially empty");
        s.push(1); s.push(2);
        check(s.top() == 2,       "top after push 1,2 == 2");
        check(s.pop() == 2,       "pop returns 2");
        check(s.top() == 1,       "top now 1");
        check(s.empty() == false, "not empty");
        check(s.pop() == 1,       "pop returns 1");
        check(s.empty() == true,  "empty after all pops");
    }
    {
        MyStack s2;
        s2.push(5); s2.push(3); s2.push(8);
        check(s2.pop() == 8, "LIFO: pop 8 first");
        check(s2.pop() == 3, "LIFO: pop 3 second");
        check(s2.top() == 5, "top is 5");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
