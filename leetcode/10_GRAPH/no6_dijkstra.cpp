/**
 * @file no6_network_delay_time.cpp
 * @brief LeetCode 743: Network Delay Time
 * @difficulty Medium
 * @link https://leetcode.com/problems/network-delay-time/
 *
 * Problem Description:
 * You are given a network of n nodes, labeled from 1 to n. You are also given times,
 * a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the
 * source node, vi is the target node, and wi is the time it takes for a signal to
 * travel from source to target.
 * 
 * We will send a signal from a given node k. Return the minimum time it takes for
 * all the n nodes to receive the signal. If it is impossible for all the n nodes
 * to receive the signal, return -1.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Computes the network delay time using Dijkstra's algorithm.
     * 
     * @param times A 2D list of directed edges with travel times: (u, v, w)
     * @param n The total number of nodes in the network (1 to n)
     * @param k The source node
     * @return int The minimum time for all nodes to receive the signal, or -1 if unreachable
     */
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Step 1: Build the adjacency list representation
        // The graph is 1-indexed, so we allocate size n + 1.
        // Each entry contains pairs of (neighbor, weight).
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& edge : times) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
        }

        // Step 2: Initialize distance array with infinity (using a large constant)
        const int INF = 1e9;
        vector<int> dist(n + 1, INF);
        dist[k] = 0; // Distance to source is 0

        // Step 3: Initialize min-priority queue (min-heap)
        // Stores pair of (distance, node) to always extract the node with the minimum distance.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // If we found a shorter path to u already processed, skip this duplicate entry.
            if (d > dist[u]) {
                continue;
            }

            // Relax all neighbors of vertex u
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // Step 4: Find the maximum time required to reach any node
        int max_time = 0;
        for (int i = 1; i <= n; ++i) {
            // If any node is unreachable (still INF), return -1
            if (dist[i] == INF) {
                return -1;
            }
            max_time = max(max_time, dist[i]);
        }

        return max_time;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace networkDelayTime with the following inputs:
 * times = [[2, 1, 1], [2, 3, 1], [3, 4, 1]], n = 4, k = 2
 * 
 * 1. Adjacency List (adj):
 *    adj[1] = []
 *    adj[2] = [(1, 1), (3, 1)]
 *    adj[3] = [(4, 1)]
 *    adj[4] = []
 * 
 * 2. Initialize Distance Array & Priority Queue:
 *    dist = [INF, INF, 0, INF, INF] (indices 0 to 4, index 2 is source)
 *    pq = {(0, 2)}
 * 
 * 3. Dijkstra Iteration 1:
 *    - Pop top from pq: d = 0, u = 2.
 *    - Since d == dist[2] (0 == 0), proceed.
 *    - Neighbors of 2:
 *      - neighbor v = 1, weight = 1:
 *        - dist[2] + 1 = 0 + 1 = 1 < dist[1] (INF).
 *        - Update dist[1] = 1.
 *        - Push {1, 1} to pq.
 *      - neighbor v = 3, weight = 1:
 *        - dist[2] + 1 = 0 + 1 = 1 < dist[3] (INF).
 *        - Update dist[3] = 1.
 *        - Push {1, 3} to pq.
 *    - State: dist = [INF, 1, 0, 1, INF], pq = {(1, 1), (1, 3)}
 * 
 * 4. Dijkstra Iteration 2:
 *    - Pop top from pq: d = 1, u = 1 (or 3, min-heap chooses smallest element). Let's say u = 1.
 *    - Since d == dist[1] (1 == 1), proceed.
 *    - Neighbors of 1: none.
 *    - State: dist = [INF, 1, 0, 1, INF], pq = {(1, 3)}
 * 
 * 5. Dijkstra Iteration 3:
 *    - Pop top from pq: d = 1, u = 3.
 *    - Since d == dist[3] (1 == 1), proceed.
 *    - Neighbors of 3:
 *      - neighbor v = 4, weight = 1:
 *        - dist[3] + 1 = 1 + 1 = 2 < dist[4] (INF).
 *        - Update dist[4] = 2.
 *        - Push {2, 4} to pq.
 *    - State: dist = [INF, 1, 0, 1, 2], pq = {(2, 4)}
 * 
 * 6. Dijkstra Iteration 4:
 *    - Pop top from pq: d = 2, u = 4.
 *    - Since d == dist[4] (2 == 2), proceed.
 *    - Neighbors of 4: none.
 *    - State: dist = [INF, 1, 0, 1, 2], pq = {}
 * 
 * 7. End of Dijkstra (pq is empty).
 * 
 * 8. Scan dist array from 1 to 4:
 *    - dist[1] = 1
 *    - dist[2] = 0
 *    - dist[3] = 1
 *    - dist[4] = 2
 *    - Max value = 2. No node is INF.
 *    - Return 2.
 * 
 * Result:
 * The network delay time is 2.
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(E * log(V))
 * - V is the number of vertices, E is the number of edges.
 * - Building the adjacency list takes O(E) time.
 * - In the worst-case, every edge is relaxed once. Each relaxation pushes an
 *   element onto the priority queue, which takes O(log(V)) time.
 * - Total time for all priority queue operations is O(E * log(V)).
 * 
 * Space Complexity: O(V + E)
 * - The adjacency list stores E edges and V headers.
 * - The priority queue holds at most E items at any point.
 * - The distance array takes O(V) space.
 */

int main() {
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4;
    int k = 2;

    Solution solver;
    int delay = solver.networkDelayTime(times, n, k);

    cout << "Minimum network delay time: " << delay << " (Expected: 2)" << endl;

    return 0;
}
