# LeetCode Style: Double Hashing HashMap

Design a `DoubleHashMap` key-value container using double hashing collision probing.

The probe sequence is computed as: `idx_i = (H1(key) + i * H2(key)) % Size`.

## Example 1:
**Input:**
```cpp
DoubleHashMap map;
map.put(1, 100);
map.get(1); // return 100
```
