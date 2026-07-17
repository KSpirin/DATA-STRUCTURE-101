/**
 * @file no2_course_schedule.cpp
 * @brief LeetCode 207: Course Schedule (Kahn's Topological Sort)
 * @difficulty Medium
 * @link https://leetcode.com/problems/course-schedule/
 *
 * Problem Description:
 * There are a total of numCourses courses you have to take, labeled from 0 to
 * numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi]
 * indicates that you must take course bi first if you want to take course ai.
 * For example, the pair [0, 1], indicates that to take course 0 you must first
 * take course 1.
 * Return true if you can finish all courses. Otherwise, return false.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * @brief Determines if all courses can be finished using Kahn's Topological Sort.
     * 
     * @param numCourses Total number of courses
     * @param prerequisites Prerequisite pairs where prerequisites[i] = [dest, src]
     * @return true If the course dependency graph is a DAG (can finish all courses)
     * @return false If a cycle is detected (cannot finish all courses)
     */
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Guard clause for edge case
        if (numCourses <= 0) return true;

        // Build the Adjacency List and compute the in-degrees of all vertices
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);

        for (const auto& edge : prerequisites) {
            int dest = edge[0]; // Course to take after
            int src = edge[1];  // Prerequisite course
            
            adj[src].push_back(dest);
            inDegree[dest]++;
        }

        // Enqueue all courses that have no prerequisites (in-degree == 0)
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Keep track of the number of courses successfully processed
        int visitedCourses = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            visitedCourses++;

            // For each course v dependent on course u
            for (int v : adj[u]) {
                inDegree[v]--; // Decrement in-degree since prerequisite u is completed
                
                // If course v now has no unmet prerequisites, enqueue it
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // If we visited all courses, no cycle exists; otherwise, there is a cycle
        return visitedCourses == numCourses;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace Kahn's algorithm on numCourses = 4, and prerequisites = [[1,0], [2,0], [3,1], [3,2]]:
 * Graph Structure:
 *   0 -> 1 -> 3
 *   0 -> 2 -> 3
 * 
 * 1. Build Adjacency List & Indegrees:
 *    - Edge 0 -> 1: adj[0] = {1}, inDegree[1] = 1
 *    - Edge 0 -> 2: adj[0] = {1, 2}, inDegree[2] = 1
 *    - Edge 1 -> 3: adj[1] = {3}, inDegree[3] = 1
 *    - Edge 2 -> 3: adj[2] = {3}, inDegree[3] = 2
 *    - Adjacency List:
 *        0: [1, 2]
 *        1: [3]
 *        2: [3]
 *        3: []
 *    - In-Degrees:
 *        0: 0, 1: 1, 2: 1, 3: 2
 * 
 * 2. Initialize Queue:
 *    - Push vertices with inDegree == 0.
 *    - Queue: [0]
 * 
 * 3. Process Queue:
 *    - Dequeue u = 0. visitedCourses = 1.
 *      - Neighbor v = 1: decrement inDegree[1] to 0. Enqueue 1.
 *      - Neighbor v = 2: decrement inDegree[2] to 0. Enqueue 2.
 *      - Queue: [1, 2]
 * 
 *    - Dequeue u = 1. visitedCourses = 2.
 *      - Neighbor v = 3: decrement inDegree[3] to 1.
 *      - Queue: [2]
 * 
 *    - Dequeue u = 2. visitedCourses = 3.
 *      - Neighbor v = 3: decrement inDegree[3] to 0. Enqueue 3.
 *      - Queue: [3]
 * 
 *    - Dequeue u = 3. visitedCourses = 4.
 *      - No neighbors.
 *      - Queue: []
 * 
 * 4. Termination:
 *    - Queue is empty.
 *    - visitedCourses (4) == numCourses (4).
 *    - Returns: true.
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(V + E)
 * - V is numCourses, E is the number of prerequisites.
 * - Initializing adjacency list takes O(V + E).
 * - Each vertex is enqueued and dequeued exactly once: O(V).
 * - We traverse every edge in the graph exactly once to decrement in-degree: O(E).
 * 
 * Space Complexity: O(V + E)
 * - The adjacency list stores V headers and E edges: O(V + E).
 * - The in-degree vector and queue take O(V) space.
 */

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    Solution solver;
    if (solver.canFinish(numCourses, prerequisites)) {
        cout << "All courses can be completed successfully! (Expected: true)" << endl;
    } else {
        cout << "Cycle detected! Cannot complete courses. (Expected: false)" << endl;
    }

    return 0;
}
