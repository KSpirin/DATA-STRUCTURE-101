# LeetCode 146. LRU Cache

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

## Example 1:
**Input:**
```cpp
LRUCache* lRUCache = new LRUCache(2);
lRUCache->put(1, 10);
lRUCache->put(2, 20);
lRUCache->get(1);    // returns 10
lRUCache->put(3, 30); // evicts key 2
lRUCache->get(2);    // returns -1 (not found)
```
