#include <iostream>
#include <stack>
#include <cassert>

// PROBLEM: LeetCode 155 - Min Stack
// A stack that also returns the minimum in O(1).

class MinStack {
private:
    // TODO 0: Declare two stacks here
    //   std::stack<int> s;      <- main data stack
    //   std::stack<int> min_s;  <- tracks running minimum

public:
    void push(int val) {
        // TODO 1: Push val to main stack
        // TODO 2: If min_s is empty OR val <= min_s.top(), push val to min_s too
    }

    void pop() {
        // TODO 3: If s.top() == min_s.top(), pop min_s
        // TODO 4: Pop main stack
    }

    int top() {
        // TODO 5: Return main stack top
        return 0;
    }

    int getMin() {
        // TODO 6: Return min_s top
        return 0;
    }
};

int main() {
    MinStack ms;
    ms.push(-2); ms.push(0); ms.push(-3);
    assert(ms.getMin() == -3);
    ms.pop();
    assert(ms.top() == 0);
    assert(ms.getMin() == -2);
    std::cout << "2_STACK Coding 2 Passed!" << std::endl;
    return 0;
}
