# LeetCode 155. Min Stack

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

## Example 1:
**Input:**
```cpp
MinStack* minStack = new MinStack();
minStack->push(-2);
minStack->push(0);
minStack->push(-3);
minStack->getMin(); // return -3
minStack->pop();
minStack->top();    // return 0
minStack->getMin(); // return -2
```
