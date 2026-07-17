/**
 * @file no2_design_hashmap.cpp
 * @brief LeetCode 706: Design HashMap (Separate Chaining Implementation)
 * @difficulty Easy (Medium complexity when custom-implemented)
 * @link https://leetcode.com/problems/design-hashmap/
 * 
 * Problem Description:
 * Design a HashMap without using any built-in hash table libraries.
 * Implement the MyHashMap class:
 * - MyHashMap() initializes the object with an empty map.
 * - void put(int key, int value) inserts a (key, value) pair into the HashMap. 
 *   If the key already exists in the map, update the corresponding value.
 * - int get(int key) returns the value to which the specified key is mapped, 
 *   or -1 if this map contains no mapping for the key.
 * - void remove(key) removes the key and its corresponding value if the map 
 *   contains the mapping for the key.
 */

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <cassert>

class MyHashMap {
private:
    struct HashNode {
        int key;
        int value;
        HashNode(int k, int v) : key(k), value(v) {}
    };

    // A large prime table size helps minimize collisions.
    // Constraints: 0 <= key, value <= 10^6. Calls at most 10^4.
    static const int BUCKETS = 19997; // A prime number
    std::vector<std::list<HashNode>> table;

    // Hash function using modulo division
    int hashFunction(int key) const {
        return key % BUCKETS;
    }

public:
    MyHashMap() : table(BUCKETS) {}

    void put(int key, int value) {
        int bucketIndex = hashFunction(key);
        auto& chain = table[bucketIndex];
        
        // Search if key already exists to update value
        for (auto& node : chain) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        
        // If not found, insert new node at the end of the chain
        chain.emplace_back(key, value);
    }

    int get(int key) const {
        int bucketIndex = hashFunction(key);
        const auto& chain = table[bucketIndex];
        
        // Search the chain
        for (const auto& node : chain) {
            if (node.key == key) {
                return node.value;
            }
        }
        
        // Key not found
        return -1;
    }

    void remove(int key) {
        int bucketIndex = hashFunction(key);
        auto& chain = table[bucketIndex];
        
        // Find node and erase it from list
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                return;
            }
        }
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Operations:
  MyHashMap myHashMap;
  myHashMap.put(1, 1);
  myHashMap.put(2, 2);
  myHashMap.get(1);      // returns 1
  myHashMap.get(3);      // returns -1 (not found)
  myHashMap.put(2, 1);   // update existing key 2 with value 1
  myHashMap.get(2);      // returns 1
  myHashMap.remove(2);   // remove key 2
  myHashMap.get(2);      // returns -1 (removed)

Trace:
1. Initialize `MyHashMap` with 19997 empty linked list chains.
2. `put(1, 1)`:
   - Index = 1 % 19997 = 1.
   - List at index 1 is empty. Append {1, 1}.
3. `put(2, 2)`:
   - Index = 2 % 19997 = 2.
   - List at index 2 is empty. Append {2, 2}.
4. `get(1)`:
   - Index = 1 % 19997 = 1.
   - Traverse list at index 1: found node with key 1, return its value (1).
5. `get(3)`:
   - Index = 3 % 19997 = 3.
   - List at index 3 is empty. Return -1.
6. `put(2, 1)`:
   - Index = 2 % 19997 = 2.
   - Traverse list at index 2. Found node with key 2. Update value to 1.
7. `get(2)`:
   - Index = 2 % 19997 = 2.
   - Traverse list at index 2. Found node with key 2. Return value (1).
8. `remove(2)`:
   - Index = 2 % 19997 = 2.
   - Traverse list at index 2. Found node with key 2. Erase node. List at index 2 is now empty.
9. `get(2)`:
   - Index = 2 % 19997 = 2.
   - List at index 2 is empty. Return -1.
================================================================================
Complexity Analysis:
- Time Complexity:
  - Put: O(1) on average, O(N) worst-case (if all keys hash to the same bucket).
  - Get: O(1) on average, O(N) worst-case.
  - Remove: O(1) on average, O(N) worst-case.
  where N is the number of keys inserted. With BUCKETS = 19997 and uniform distribution,
  the expected chain length is very small (O(1)).
- Space Complexity: O(K + M)
  where K is the number of buckets (19997) and M is the number of unique elements inserted.
================================================================================
*/

int main() {
    MyHashMap map;
    map.put(1, 1);
    map.put(2, 2);
    assert(map.get(1) == 1);
    assert(map.get(3) == -1);
    map.put(2, 1);
    assert(map.get(2) == 1);
    map.remove(2);
    assert(map.get(2) == -1);
    
    std::cout << "Design HashMap test passed!" << std::endl;
    return 0;
}
