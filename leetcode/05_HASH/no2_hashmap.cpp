/**
 * @brief LeetCode 706 - Design HashMap
 * @difficulty Easy
 * @link https://leetcode.com/problems/design-hashmap/
 *
 * Problem:
 * Design HashMap without built-in hash libraries.
 * 
 * Constraints: 0 <= key, value <= 10^6, at most 10^4 calls */

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

class MyHashMap {
public:
    MyHashMap() { // TODO
    }
    void put(int key, int value) { // TODO
    }
    int get(int key) { // TODO (return -1 if not found)
    }
    void remove(int key) { // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    MyHashMap m;
    m.put(1,1); m.put(2,2);
    check(m.get(1)==1, "get(1) == 1");
    check(m.get(3)==-1,"get(3) not exist == -1");
    m.put(2,1);
    check(m.get(2)==1, "update put(2,1) -> get(2)==1");
    m.remove(2);
    check(m.get(2)==-1,"after remove(2) -> -1");
    m.put(0,0);
    check(m.get(0)==0, "put/get 0 -> 0");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
