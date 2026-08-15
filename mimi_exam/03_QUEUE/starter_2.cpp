#include <iostream>
#include <queue>
#include <cassert>

// PROBLEM: LeetCode 225 - Implement Stack using Queues
// Stack is LIFO, Queue is FIFO.
// TRICK: After pushing, rotate all old elements to the BACK of q1.
// That way q1.front() is always the most recently pushed (LIFO!).

class MyStack {
private:
    // TODO 0: Declare two queues: q1 (main), q2 (helper)
    // std::queue<int> q1, q2;

public:
    void push(int x) {
        // TODO 1: Push x into q2
        // TODO 2: Move everything from q1 into q2
        // TODO 3: Swap q1 and q2
        // Result: newest element is now at q1.front()
    }

    int pop() {
        // TODO 4: Return and remove q1.front()
        return 0;
    }

    int top() {
        // TODO 5: Return q1.front() without removing
        return 0;
    }

    bool empty() {
        // TODO 6: Return q1.empty()
        return true;
    }
};

int main() {
    MyStack s;
    s.push(1); s.push(2);
    assert(s.top() == 2);
    assert(s.pop() == 2);
    assert(s.top() == 1);
    std::cout << "3_QUEUE Coding 2 Passed!" << std::endl;
    return 0;
}
