/**
 * @file no7_number_of_provinces.cpp
 * @brief LeetCode 547: Number of Provinces
 * @difficulty Medium
 * @link https://leetcode.com/problems/number-of-provinces/
 *
 * Problem Description:
 * There are n cities. Some of them are connected, while some are not. If city a
 * is connected directly with city b, and city b is connected directly with city c,
 * then city a is connected indirectly with city c.
 * A province is a group of directly or indirectly connected cities and no other
 * cities outside of the group.
 * You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the
 * i-th city and the j-th city are directly connected, and isConnected[i][j] = 0
 * otherwise.
 * Return the total number of provinces.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    /**
     * @brief Helper function to perform DFS to find all cities in the same province.
     * 
     * @param isConnected The adjacency matrix representing city connections
     * @param visited A vector tracking visited status of each city
     * @param u The current city index
     */
    void dfs(const vector<vector<int>>& isConnected, vector<bool>& visited, int u) {
        visited[u] = true;
        int n = isConnected.size();
        for (int v = 0; v < n; ++v) {
            // If city v is connected to u and hasn't been visited yet
            if (isConnected[u][v] == 1 && !visited[v]) {
                dfs(isConnected, visited, v);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.empty()) return 0;
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                provinces++;
                dfs(isConnected, visited, i);
            }
        }

        return provinces;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace the algorithm on the following isConnected matrix (n = 3):
 * 
 * isConnected:
 * [
 *   [1, 1, 0],
 *   [1, 1, 0],
 *   [0, 0, 1]
 * ]
 * 
 * 1. Initialization:
 *    - visited = [false, false, false]
 *    - provinces = 0
 * 
 * 2. Iteration (i = 0):
 *    - visited[0] is false.
 *    - Increment provinces to 1.
 *    - Call dfs(isConnected, visited, 0):
 *      - Mark visited[0] = true. (visited = [true, false, false])
 *      - Check connections for city 0:
 *        - v = 0: isConnected[0][0] == 1, but visited[0] is true. Skip.
 *        - v = 1: isConnected[0][1] == 1, and visited[1] is false. Call dfs(isConnected, visited, 1):
 *          - Mark visited[1] = true. (visited = [true, true, false])
 *          - Check connections for city 1:
 *            - v = 0: isConnected[1][0] == 1, but visited[0] is true. Skip.
 *            - v = 1: isConnected[1][1] == 1, but visited[1] is true. Skip.
 *            - v = 2: isConnected[1][2] == 0. Skip.
 *          - dfs(1) returns.
 *        - v = 2: isConnected[0][2] == 0. Skip.
 *      - dfs(0) returns.
 * 
 * 3. Iteration (i = 1):
 *    - visited[1] is true. Skip.
 * 
 * 4. Iteration (i = 2):
 *    - visited[2] is false.
 *    - Increment provinces to 2.
 *    - Call dfs(isConnected, visited, 2):
 *      - Mark visited[2] = true. (visited = [true, true, true])
 *      - Check connections for city 2:
 *        - v = 0: isConnected[2][0] == 0. Skip.
 *        - v = 1: isConnected[2][1] == 0. Skip.
 *        - v = 2: isConnected[2][2] == 1, but visited[2] is true. Skip.
 *      - dfs(2) returns.
 * 
 * 5. Loop completes. Total provinces = 2.
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(N^2)
 * - N is the number of cities.
 * - The adjacency matrix has size N x N. We visit each node once and check all 
 *   its potential neighbors in O(N) time. Thus, the total time complexity is O(N^2).
 * 
 * Space Complexity: O(N)
 * - The visited array requires O(N) space.
 * - The recursion stack for DFS can grow up to O(N) in the worst-case scenario 
 *   where all cities are connected in a single linear province.
 */

int main() {
    vector<vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };

    Solution solver;
    int provinces = solver.findCircleNum(isConnected);
    cout << "Number of provinces: " << provinces << " (Expected: 2)" << endl;

    return 0;
}
