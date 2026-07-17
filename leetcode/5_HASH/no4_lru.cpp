/**
 * @file no4_lru_cache.cpp
 * @brief LeetCode 146: LRU Cache
 * @difficulty Medium
 * @link https://leetcode.com/problems/lru-cache/
 * 
 * Problem Description:
 * Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
 * 
 * Implement the LRUCache class:
 * - LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
 * - int get(int key) Return the value of the key if the key exists, otherwise return -1.
 * - void put(int key, int value) Update the value of the key if the key exists. Otherwise, add 
 *   the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, 
 *   evict the least recently used key.
 * 
 * The functions get and put must each run in O(1) average time complexity.
 */

#include <unordered_map>
#include <iostream>
#include <cassert>

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    // Helper function to add node right after head (MRU position)
    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Helper function to remove an existing node from the linked list
    void removeNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Helper function to move a node to the head (marking as most recently used)
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    // Helper function to pop the tail node (LRU position)
    Node* popTail() {
        Node* res = tail->prev;
        removeNode(res);
        return res;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        // Clean up memory
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr->next;
            delete curr;
            curr = temp;
        }
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        Node* node = it->second;
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            // Key already exists, update value and move to head
            Node* node = it->second;
            node->value = value;
            moveToHead(node);
        } else {
            // New key-value pair
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addNode(newNode);

            if (cache.size() > capacity) {
                // Evict the LRU node
                Node* lru = popTail();
                cache.erase(lru->key);
                delete lru;
            }
        }
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Input Operations:
LRUCache cache(2);
cache.put(1, 1); // cache = {1:1}, MRU -> 1 -> LRU
cache.put(2, 2); // cache = {2:2, 1:1}, MRU -> 2 -> 1 -> LRU
cache.get(1);    // returns 1, cache = {1:1, 2:2}, MRU -> 1 -> 2 -> LRU
cache.put(3, 3); // evicts key 2, cache = {3:3, 1:1}, MRU -> 3 -> 1 -> LRU
cache.get(2);    // returns -1 (evicted)
cache.put(4, 4); // evicts key 1, cache = {4:4, 3:3}, MRU -> 4 -> 3 -> LRU
cache.get(1);    // returns -1 (evicted)
cache.get(3);    // returns 3, cache = {3:3, 4:4}, MRU -> 3 -> 4 -> LRU
cache.get(4);    // returns 4, cache = {4:4, 3:3}, MRU -> 4 -> 3 -> LRU

Initial state (capacity = 2):
  head <-> tail
  cache = {}

1. put(1, 1):
  newNode = [1, 1]
  addNode(newNode): head <-> [1, 1] <-> tail
  cache = {1: [1, 1]}

2. put(2, 2):
  newNode = [2, 2]
  addNode(newNode): head <-> [2, 2] <-> [1, 1] <-> tail
  cache = {1: [1, 1], 2: [2, 2]}

3. get(1):
  find(1) -> returns [1, 1]
  moveToHead([1, 1]):
    removeNode([1, 1]): head <-> [2, 2] <-> tail
    addNode([1, 1]): head <-> [1, 1] <-> [2, 2] <-> tail
  returns 1

4. put(3, 3):
  newNode = [3, 3]
  addNode(newNode): head <-> [3, 3] <-> [1, 1] <-> [2, 2] <-> tail
  cache = {1: [1, 1], 2: [2, 2], 3: [3, 3]}
  size (3) > capacity (2):
    lru = popTail() -> removes [2, 2], returns [2, 2]
    cache.erase(2)
    delete [2, 2]
  Result: head <-> [3, 3] <-> [1, 1] <-> tail, cache = {1: [1, 1], 3: [3, 3]}

5. get(2):
  find(2) -> not found, returns -1

6. put(4, 4):
  newNode = [4, 4]
  addNode(newNode): head <-> [4, 4] <-> [3, 3] <-> [1, 1] <-> tail
  cache = {1: [1, 1], 3: [3, 3], 4: [4, 4]}
  size (3) > capacity (2):
    lru = popTail() -> removes [1, 1]
    cache.erase(1)
    delete [1, 1]
  Result: head <-> [4, 4] <-> [3, 3] <-> tail, cache = {3: [3, 3], 4: [4, 4]}

7. get(1):
  find(1) -> not found, returns -1

8. get(3):
  find(3) -> returns [3, 3]
  moveToHead([3, 3]): head <-> [3, 3] <-> [4, 4] <-> tail
  returns 3

9. get(4):
  find(4) -> returns [4, 4]
  moveToHead([4, 4]): head <-> [4, 4] <-> [3, 3] <-> tail
  returns 4

================================================================================
Complexity Analysis:
- Time Complexity:
  - get(key): O(1) average. Hash map lookup is O(1), and double linked list node relocation is O(1).
  - put(key, value): O(1) average. Hash map lookup and insertion are O(1), node addition/removal is O(1).
- Space Complexity: O(C), where C is the capacity of the cache. We store at most C + 2 nodes in the 
  doubly linked list and C items in the hash map.
================================================================================
*/

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1);
    cache.put(3, 3);    // evicts key 2
    assert(cache.get(2) == -1);
    cache.put(4, 4);    // evicts key 1
    assert(cache.get(1) == -1);
    assert(cache.get(3) == 3);
    assert(cache.get(4) == 4);

    std::cout << "LRU Cache tests passed!" << std::endl;
    return 0;
}
