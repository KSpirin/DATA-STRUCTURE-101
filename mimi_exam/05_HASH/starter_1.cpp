#include <iostream>
#include <vector>
#include <cassert>

// PROBLEM: Double Hashing HashMap
// Resolve collisions using TWO hash functions:
//   H1(key) = key % size
//   H2(key) = 7 - (key % 7)
//   Probe sequence: index = (H1 + i * H2) % size

class DoubleHashMap {
private:
    struct Node {
        int key, value;
        bool active = false;
    };
    // TODO 0: Declare vector<Node> table and int size

public:
    DoubleHashMap() {
        // TODO 1: Set size = 11, resize table to 11
    }

    void put(int key, int val) {
        // TODO 2: Compute H1 = key % size, H2 = 7 - (key % 7)
        // TODO 3: Probe until empty slot or matching key
        // TODO 4: Insert {key, val, true} at found index
    }

    int get(int key) {
        // TODO 5: Probe same way as put
        // TODO 6: Return value if key matches, -1 if slot is inactive
        return -1;
    }
};

int main() {
    DoubleHashMap map;
    map.put(1, 100);
    assert(map.get(1) == 100);
    assert(map.get(2) == -1);
    std::cout << "5_HASH Coding 1 Passed!" << std::endl;
    return 0;
}
