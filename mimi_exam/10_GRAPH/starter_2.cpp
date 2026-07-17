#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// PROBLEM: Dijkstra's Algorithm - Network Delay Time
// Find shortest path from source k to ALL nodes.

class Solution {
public:
    int networkDelayTime(const std::vector<std::vector<std::pair<int,int>>>& adj, int n, int k) {
        // TODO:
        // - dist vector size n+1, filled with 1e9, dist[k] = 0
        // - Min-heap pq, push {0, k}
        // - While pq not empty: pop {d, u}, skip if d > dist[u]
        //   For each neighbor {v, w}: if dist[u]+w < dist[v], update and push
        // - Return max of all dist[1..n], or -1 if any is still 1e9

        return -1;
    }
};

int main() {
    // 2 nodes: edge from node 2 -> node 1 with delay 50
    std::vector<std::vector<std::pair<int,int>>> adj(3);
    adj[2].push_back({1, 50});
    assert(Solution().networkDelayTime(adj, 2, 2) == 50);
    std::cout << "10_GRAPH Coding 2 Passed!" << std::endl;
    return 0;
}
