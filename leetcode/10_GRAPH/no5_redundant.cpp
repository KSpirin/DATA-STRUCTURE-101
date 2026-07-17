/**
 * @file no5_redundant_connection.cpp
 * @brief LeetCode 684: Redundant Connection
 * @difficulty Medium
 * @link https://leetcode.com/problems/redundant-connection/
 *
 * Problem Description:
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n,
 * with one additional edge added. The added edge has two different vertices chosen
 * from 1 to n, and was not an edge that already existed.
 * 
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the input.
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/**
 * @brief Disjoint Set Union (DSU) / Union-Find class.
 * Supports path compression and union by rank.
 */
class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        // Initialize parent of each node to itself, and ranks to 0
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
        rank.assign(n + 1, 0);
    }

    /**
     * @brief Finds the representative of the set containing node `i` with path compression.
     */
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        // Path compression: flatten the structure by pointing node directly to the root
        return parent[i] = find(parent[i]);
    }

    /**
     * @brief Unites the sets containing node `i` and node `j`.
     * Returns false if they are already in the same set (i.e., cycle detected), true otherwise.
     */
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i == root_j) {
            // Already in the same set. Adding edge between them creates a cycle.
            return false;
        }

        // Union by rank: hang the shorter tree under the taller tree
        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }

        return true;
    }
};

class Solution {
public:
    /**
     * @brief Finds the redundant edge whose removal makes the graph a tree.
     * 
     * @param edges Vector of undirected edges [u, v]
     * @return vector<int> The last edge that creates a cycle in the graph
     */
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size(); // The graph has n nodes and n edges (one cycle)
        DSU dsu(n);

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            // Attempt to union the two nodes of the edge.
            // If unite returns false, it means they are already connected,
            // meaning this edge closes a cycle and is therefore redundant.
            if (!dsu.unite(u, v)) {
                return edge;
            }
        }
        
        return {};
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace findRedundantConnection with the input:
 * edges = [[1, 2], [1, 3], [2, 3]]
 * Number of nodes n = 3. DSU initialized:
 * parent = [0, 1, 2, 3], rank = [0, 0, 0, 0]
 * 
 * 1. Process edge [1, 2]:
 *    - u = 1, v = 2
 *    - find(1) -> 1, find(2) -> 2. (Roots: 1, 2)
 *    - Roots are different. Call dsu.unite(1, 2):
 *      - rank[1] == rank[2] (both 0).
 *      - parent[2] = 1, rank[1] becomes 1.
 *      - parent state: [0, 1, 1, 3]
 *    - Returns true. No cycle.
 * 
 * 2. Process edge [1, 3]:
 *    - u = 1, v = 3
 *    - find(1) -> 1 (since parent[1] == 1)
 *    - find(3) -> 3 (since parent[3] == 3)
 *    - Roots are different (1, 3). Call dsu.unite(1, 3):
 *      - rank[1] = 1, rank[3] = 0.
 *      - rank[1] > rank[3], so parent[3] = 1.
 *      - parent state: [0, 1, 1, 1]
 *    - Returns true. No cycle.
 * 
 * 3. Process edge [2, 3]:
 *    - u = 2, v = 3
 *    - find(2):
 *      - parent[2] is 1. parent[1] is 1. Root is 1.
 *      - Path compression updates parent[2] = 1.
 *    - find(3):
 *      - parent[3] is 1. parent[1] is 1. Root is 1.
 *      - Path compression updates parent[3] = 1.
 *    - Both find(2) and find(3) return 1.
 *    - Roots are the same! dsu.unite(2, 3) returns false.
 *    - Cycle detected. return edge [2, 3].
 * 
 * Result:
 * Redundant edge is [2, 3].
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(N * alpha(N)) ≈ O(N)
 * - N is the number of nodes (and edges) in the graph.
 * - For each of the N edges, we perform DSU Find and Union operations.
 * - Using both path compression and union by rank, each operation runs in
 *   O(alpha(N)) time, where alpha is the inverse Ackermann function, which grows
 *   extremely slowly and is <= 4 for all practical values of N.
 * 
 * Space Complexity: O(N)
 * - The DSU class uses two vectors of size N + 1 (`parent` and `rank`) to
 *   keep track of set representations and tree heights.
 */

int main() {
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    
    cout << "Edges in the graph: " << endl;
    for (const auto& edge : edges) {
        cout << "[" << edge[0] << ", " << edge[1] << "] ";
    }
    cout << endl;

    Solution solver;
    vector<int> redundant = solver.findRedundantConnection(edges);

    cout << "Redundant edge to remove: [" << redundant[0] << ", " << redundant[1] << "]" << endl;
    cout << "Expected: [1, 4]" << endl;

    return 0;
}
