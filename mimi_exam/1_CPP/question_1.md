# LeetCode Style: Rule of 3 (Dynamic Array)

Design a class `DynamicArray` that safely manages its memory allocations following the Rule of 3 (Destructor, Copy Constructor, Copy Assignment Operator).

## Example 1:
**Input:**
```cpp
DynamicArray<int> arr1(5);
arr1.push_back(10);
DynamicArray<int> arr2 = arr1; // Copy Constructor
```
**Output:**
`arr2.at(0) == 10`

## Constraints:
* Array elements are integers or floats.
* The capacity must double when the array becomes full.
