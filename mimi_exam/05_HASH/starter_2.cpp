#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>

// PROBLEM: LeetCode 146 - LRU Cache
// Least Recently Used: when full, evict the LEAST recently used key.

class LRUCache {
private:
    // TODO 0: Declare:
    //   int cap;
    //   std::list<std::pair<int,int>> cache;           // {key, val}
    //   std::unordered_map<int, list<...>::iterator> map;

public:
    LRUCache(int capacity) {
        // TODO 1: Set cap = capacity
    }

    int get(int key) {
        // TODO 2: If key not in map, return -1
        // TODO 3: Move accessed node to front (erase + push_front + update map)
        // TODO 4: Return value
        return -1;
    }

    void put(int key, int value) {
        // TODO 5: If key exists, erase it from list
        // TODO 6: If cache is full (size >= cap), erase LRU from back + map
        // TODO 7: Push {key, value} to front, update map
    }
};

int main() {
    LRUCache lru(2);
    lru.put(1, 10); lru.put(2, 20);
    assert(lru.get(1) == 10);
    lru.put(3, 30);              // evicts key 2
    assert(lru.get(2) == -1);   // key 2 is gone
    std::cout << "5_HASH Coding 2 Passed!" << std::endl;
    return 0;
}
