/**
 * @file no3_min_stack.cpp
 * @brief LeetCode 155 - Min Stack
 * @details Difficulty: Medium
 * @link https://leetcode.com/problems/min-stack/
 *
 * @description
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * Implement the MinStack class:
 * - MinStack() initializes the stack object.
 * - void push(int val) pushes the element val onto the stack.
 * - void pop() removes the element on the top of the stack.
 * - int top() gets the top element of the stack.
 * - int getMin() retrieves the minimum element in the stack.
 *
 * You must implement a solution with O(1) time complexity for each function.
 */

#include <iostream>
#include <stack>
#include <algorithm>
#include <cassert>

class MinStack {
private:
    std::stack<int> main_stack;  // Stores all the elements
    std::stack<int> min_stack;   // Stores the history of minimum elements

public:
    /**
     * @brief Construct a new Min Stack object.
     */
    MinStack() {
        // No explicit initialization needed as standard stacks self-initialize
    }
    
    /**
     * @brief Pushes val onto the stack.
     * @param val Value to push.
     * 
     * Time Complexity: O(1)
     */
    void push(int val) {
        main_stack.push(val);
        
        // If min_stack is empty or val is less than or equal to the current minimum,
        // push val onto the min_stack. We use '<=' to handle duplicate minimums properly.
        if (min_stack.empty() || val <= min_stack.top()) {
            min_stack.push(val);
        }
    }
    
    /**
     * @brief Removes the element on the top of the stack.
     * 
     * Time Complexity: O(1)
     */
    void pop() {
        // If the top element of the main stack matches the current minimum,
        // we must pop it from the min_stack as well to maintain correct minimum state.
        if (main_stack.top() == min_stack.top()) {
            min_stack.pop();
        }
        main_stack.pop();
    }
    
    /**
     * @brief Gets the top element of the stack.
     * @return The top element.
     * 
     * Time Complexity: O(1)
     */
    int top() {
        return main_stack.top();
    }
    
    /**
     * @brief Retrieves the minimum element in the stack.
     * @return The minimum element.
     * 
     * Time Complexity: O(1)
     */
    int getMin() {
        return min_stack.top();
    }
};

/*
 * ==========================================================
 * DESIGN ALTERNATIVES & DECISION RATIONALE
 * ==========================================================
 * 1. Two-Stack Approach (Implemented here):
 *    - Uses a main stack for values and an auxiliary min stack for tracking the minimums.
 *    - Memory optimization: We only push to the min stack if the new element is <= current min.
 * 
 * 2. Pair-Stack Approach (storing std::pair<int, int>):
 *    - Keeps values and current minimums together in a single stack: std::stack<std::pair<value, current_min>>.
 *    - Pros: Highly readable and avoids synchronization checks between two stacks.
 *    - Cons: Extra memory overhead as every single node stores duplicate minimum values.
 *
 * ==========================================================
 * MANUAL DRY RUN / EXECUTION TRACE
 * ==========================================================
 * Sequence of Calls:
 * MinStack* minStack = new MinStack();
 * minStack->push(-2);
 * minStack->push(0);
 * minStack->push(-3);
 * minStack->getMin(); // return -3
 * minStack->pop();
 * minStack->top();    // return 0
 * minStack->getMin(); // return -2
 *
 * Trace:
 * Step | Operation    | Arg  | Main Stack (Bottom->Top) | Min Stack (Bottom->Top) | Return Val | Notes
 * -----|--------------|------|--------------------------|-------------------------|------------|---------------------------------
 * 1    | push         | -2   | [ -2 ]                   | [ -2 ]                  | -          | -2 is pushed to both stacks.
 * 2    | push         | 0    | [ -2, 0 ]                | [ -2 ]                  | -          | 0 > -2, so min_stack is untouched.
 * 3    | push         | -3   | [ -2, 0, -3 ]            | [ -2, -3 ]              | -          | -3 <= -2, push to min_stack.
 * 4    | getMin       | -    | [ -2, 0, -3 ]            | [ -2, -3 ]              | -3         | Reads top of min_stack.
 * 5    | pop          | -    | [ -2, 0 ]                | [ -2 ]                  | -          | main_stack.top() == min_stack.top() (-3), popped from both.
 * 6    | top          | -    | [ -2, 0 ]                | [ -2 ]                  | 0          | Reads top of main_stack.
 * 7    | getMin       | -    | [ -2, 0 ]                | [ -2 ]                  | -2         | Reads top of min_stack.
 *
 * ==========================================================
 * Complexity Analysis:
 * ==========================================================
 * Time Complexity:
 * - push(): O(1) - Pushing to standard stacks takes constant time.
 * - pop(): O(1) - Popping from standard stacks takes constant time.
 * - top(): O(1) - Accessing top takes constant time.
 * - getMin(): O(1) - Accessing top of min_stack takes constant time.
 *
 * Space Complexity: O(N)
 * - In the worst case (e.g., elements pushed in non-increasing order: 5, 4, 3, 2, 1),
 *   both the main stack and the min stack will store N elements, taking O(N) auxiliary space.
 */

int main() {
    MinStack* minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    
    assert(minStack->getMin() == -3);
    std::cout << "getMin() passed: returned -3" << std::endl;
    
    minStack->pop();
    assert(minStack->top() == 0);
    std::cout << "top() passed: returned 0" << std::endl;
    
    assert(minStack->getMin() == -2);
    std::cout << "getMin() passed: returned -2" << std::endl;
    
    delete minStack;
    return 0;
}
