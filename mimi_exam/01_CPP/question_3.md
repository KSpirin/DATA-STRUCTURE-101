# LeetCode Style: Custom Iterator for IntArray

Implement an Iterator nested class inside `IntContainer` to support range-based `for` loops.

## Example 1:
**Input:**
```cpp
IntContainer container;
int sum = 0;
for (int val : container) sum += val;
```
**Output:**
`sum == 100`
