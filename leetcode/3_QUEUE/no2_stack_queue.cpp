/**
 * @file no2_stack_using_queues.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 225: Implement Stack using Queues
 * @difficulty Easy
 * @link https://leetcode.com/problems/implement-stack-using-queues/
 * 
 * @details
 * Problem Description:
 * Implement a last-in-first-out (LIFO) stack using only queues. The implemented stack 
 * should support all the functions of a normal stack (push, top, pop, and empty).
 * 
 * Implement the MyStack class:
 * - void push(int x): Pushes element x to the top of the stack.
 * - int pop(): Removes the element on the top of the stack and returns it.
 * - int top(): Returns the element on the top of the stack.
 * - bool empty(): Returns true if the stack is empty, false otherwise.
 * 
 * Notes:
 * - You must use only standard operations of a queue, which means that only push to back, 
 *   peek/pop from front, size and is empty operations are valid.
 * - Depending on your language, the queue may not be supported natively. You may simulate 
 *   a queue using a list or deque (double-ended queue) as long as you use only a queue's 
 *   standard operations.
 */

#include <iostream>
#include <queue>
#include <cassert>

class MyStack {
private:
    std::queue<int> q;

public:
    /**
     * @brief Initialize the stack.
     */
    MyStack() {}
    
    /**
     * @brief Pushes element x to the top of the stack.
     * @details By pushing the new element to the back of the queue, and then 
     * rotating the queue (dequeuing the first size-1 elements and enqueuing them back),
     * we reverse the queue so that the newly added element is placed at the front.
     * This achieves LIFO behavior using a single queue.
     * 
     * @time_complexity O(N) where N is the number of elements in the stack.
     * @space_complexity O(1) auxiliary space.
     */
    void push(int x) {
        int current_size = q.size();
        q.push(x);
        
        // Rotate the queue: move the first `current_size` elements to the back
        for (int i = 0; i < current_size; ++i) {
            int front_element = q.front();
            q.pop();
            q.push(front_element);
        }
    }
    
    /**
     * @brief Removes the element on the top of the stack and returns it.
     * @time_complexity O(1)
     * @space_complexity O(1)
     */
    int pop() {
        if (empty()) {
            return -1;
        }
        int top_element = q.front();
        q.pop();
        return top_element;
    }
    
    /**
     * @brief Get the top element.
     * @time_complexity O(1)
     * @space_complexity O(1)
     */
    int top() {
        if (empty()) {
            return -1;
        }
        return q.front();
    }
    
    /**
     * @brief Returns whether the stack is empty.
     * @time_complexity O(1)
     * @space_complexity O(1)
     */
    bool empty() {
        return q.empty();
    }
};

/**
 * ==========================================
 *          MANUAL DRY-RUN TRACE
 * ==========================================
 * Let's trace the operations:
 * 
 * 1. MyStack stack;
 *    - q = []
 * 
 * 2. stack.push(1);
 *    - current_size = q.size() = 0
 *    - q.push(1) -> q = [1]
 *    - loop runs 0 times.
 *    - State: q = [1]
 * 
 * 3. stack.push(2);
 *    - current_size = q.size() = 1
 *    - q.push(2) -> q = [1, 2] (front is 1, rear is 2)
 *    - Loop i = 0:
 *        - front_element = q.front() = 1
 *        - q.pop() -> q = [2]
 *        - q.push(1) -> q = [2, 1] (front is 2, rear is 1)
 *    - State: q = [2, 1]
 * 
 * 4. stack.top() -> Returns 2 (q.front() is 2)
 * 
 * 5. stack.pop() -> Returns 2
 *    - top_element = q.front() = 2
 *    - q.pop() -> q = [1]
 *    - Returns 2. State: q = [1]
 * 
 * 6. stack.empty() -> Returns false
 */

int main() {
    MyStack* myStack = new MyStack();
    myStack->push(1);
    myStack->push(2);
    assert(myStack->top() == 2);   // returns 2
    assert(myStack->pop() == 2);   // returns 2
    assert(myStack->empty() == false); // returns False
    
    std::cout << "All assertions passed successfully!" << std::endl;
    delete myStack;
    return 0;
}
