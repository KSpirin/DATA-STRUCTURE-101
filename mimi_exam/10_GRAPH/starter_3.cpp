#include <iostream>
#include <vector>
#include <cassert>

// PROBLEM: LeetCode 684 - Redundant Connection (Union-Find / DSU)
// Detect a cycle in an undirected graph.

class DSU {
private:
    // TODO 0: Declare vector<int> parent, rank

public:
    DSU(int n) {
        // TODO 1: parent[i] = i for all i, rank all 0
    }

    int find(int i) {
        // TODO 2: If parent[i] != i, recursively find root
        // Use PATH COMPRESSION: parent[i] = find(parent[i])
        return i;
    }

    bool unite(int i, int j) {
        // TODO 3: Find roots of i and j
        // If same root: already connected -> return false (CYCLE!)
        // Union by rank: attach smaller-rank root under larger-rank root
        // Return true if successfully merged
        return true;
    }
};

int main() {
    DSU dsu(4);
    assert(dsu.unite(0, 1) == true);  // 0 and 1 connected
    assert(dsu.unite(1, 2) == true);  // 1 and 2 connected
    assert(dsu.unite(0, 2) == false); // 0 and 2 already in same set -> CYCLE!
    std::cout << "10_GRAPH Coding 3 Passed!" << std::endl;
    return 0;
}
