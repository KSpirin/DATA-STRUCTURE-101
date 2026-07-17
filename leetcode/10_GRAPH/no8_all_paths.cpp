/**
 * @file no8_all_paths.cpp
 * @brief LeetCode 797: All Paths From Source to Target
 * @difficulty Medium
 * @link https://leetcode.com/problems/all-paths-from-source-to-target/
 *
 * Problem Description:
 * Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1,
 * find all possible paths from node 0 to node n - 1 and return them in any order.
 * The graph is given as follows: graph[i] is a list of all nodes you can visit
 * from node i (i.e., there is a directed edge from node i to node graph[i][j]).
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    /**
     * @brief Helper function for backtracking DFS to find all paths.
     * 
     * @param graph The adjacency list of the graph
     * @param current The current node being visited
     * @param path The current path from source to 'current'
     * @param result The collection of all paths found
     */
    void dfs(const vector<vector<int>>& graph, int current, vector<int>& path, vector<vector<int>>& result) {
        // If we reach the target node (n - 1), store the path
        if (current == graph.size() - 1) {
            result.push_back(path);
            return;
        }

        // Traverse all neighbors of the current node
        for (int neighbor : graph[current]) {
            path.push_back(neighbor);      // Choose
            dfs(graph, neighbor, path, result); // Recurse
            path.pop_back();               // Backtrack (Undo Choose)
        }
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> result;
        if (graph.empty()) return result;

        vector<int> path = {0}; // Start path with the source node 0
        dfs(graph, 0, path, result);

        return result;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace the algorithm on the following DAG with n = 4:
 * 
 * graph = [[1, 2], [3], [3], []]
 * Visual representation:
 *   0 -> 1 -> 3
 *   0 -> 2 -> 3
 * 
 * 1. Initialization:
 *    - result = []
 *    - path = [0]
 *    - Call dfs(graph, 0, path, result):
 *      - current = 0 (not target 3).
 *      - Neighbors of 0 are 1 and 2.
 * 
 * 2. Process neighbor 1:
 *    - path.push_back(1) -> path = [0, 1]
 *    - Call dfs(graph, 1, path, result):
 *      - current = 1 (not target 3).
 *      - Neighbors of 1 is 3.
 *      - Process neighbor 3:
 *        - path.push_back(3) -> path = [0, 1, 3]
 *        - Call dfs(graph, 3, path, result):
 *          - current = 3 (is target 3!).
 *          - result.push_back([0, 1, 3]) -> result = [[0, 1, 3]]
 *          - Returns.
 *        - path.pop_back() -> path = [0, 1]
 *      - Returns.
 *    - path.pop_back() -> path = [0]
 * 
 * 3. Process neighbor 2:
 *    - path.push_back(2) -> path = [0, 2]
 *    - Call dfs(graph, 2, path, result):
 *      - current = 2 (not target 3).
 *      - Neighbors of 2 is 3.
 *      - Process neighbor 3:
 *        - path.push_back(3) -> path = [0, 2, 3]
 *        - Call dfs(graph, 3, path, result):
 *          - current = 3 (is target 3!).
 *          - result.push_back([0, 2, 3]) -> result = [[0, 1, 3], [0, 2, 3]]
 *          - Returns.
 *        - path.pop_back() -> path = [0, 2]
 *      - Returns.
 *    - path.pop_back() -> path = [0]
 * 
 * 4. DFS(0) completes.
 *    Result = [[0, 1, 3], [0, 2, 3]]
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(2^N * N)
 * - In the worst-case directed acyclic graph (a complete DAG), for a graph with
 *   N nodes, there can be 2^(N-2) paths from 0 to N-1.
 * - For each path, copying the path of length at most N into the result vector
 *   takes O(N) time.
 * - Therefore, the time complexity is bounded by O(2^N * N).
 * 
 * Space Complexity: O(N)
 * - The recursion stack can grow up to O(N) deep because of recursion depth.
 * - The temporary path variable also takes O(N) space.
 * - (Excluding the output result space, which is O(2^N * N)).
 */

int main() {
    vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};

    Solution solver;
    vector<vector<int>> paths = solver.allPathsSourceTarget(graph);

    cout << "Paths from 0 to 3:" << endl;
    for (const auto& path : paths) {
        cout << "[ ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
