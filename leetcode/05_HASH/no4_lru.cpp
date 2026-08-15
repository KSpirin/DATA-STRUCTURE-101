/**
 * @brief LeetCode 146 - LRU Cache
 * @difficulty Medium
 * @link https://leetcode.com/problems/lru-cache/
 *
 * Problem:
 * LRU Cache: get and put in O(1). Evict least recently used when full.
 * 
 * Constraints: 1 <= capacity <= 3000, 0 <= key,value <= 10^4 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>

class LRUCache {
public:
    LRUCache(int capacity) { // TODO
    }
    int get(int key) { // TODO (return -1 if not found)
    }
    void put(int key, int value) { // TODO (evict LRU if over capacity)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        LRUCache c(2);
        c.put(1,1); c.put(2,2);
        check(c.get(1)==1,  "get(1)==1");
        c.put(3,3);
        check(c.get(2)==-1, "key 2 evicted -> -1");
        check(c.get(3)==3,  "get(3)==3");
        c.put(4,4);
        check(c.get(1)==-1, "key 1 evicted -> -1");
        check(c.get(3)==3,  "get(3) still 3");
        check(c.get(4)==4,  "get(4)==4");
    }
    {
        LRUCache c2(1);
        c2.put(2,1);
        check(c2.get(2)==1, "cap=1 get(2)==1");
        c2.put(3,2);
        check(c2.get(2)==-1,"evicted 2 -> -1");
        check(c2.get(3)==2, "get(3)==2");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
