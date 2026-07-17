# LeetCode Style: Unique Pointer Move Semantics

Design a class `UniquePtr` that implements standard move semantics. The class must disable the copy constructor and copy assignment operator.

## Example 1:
**Input:**
```cpp
UniquePtr<int> p1(new int(42));
UniquePtr<int> p2(std::move(p1)); // Move Constructor
```
**Output:**
`p1.get() == nullptr && *p2 == 42`

## Constraints:
* The source pointer must be set to `nullptr` after a move.
