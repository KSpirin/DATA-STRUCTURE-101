/**
 * @file no1_number_of_islands.cpp
 * @brief LeetCode 200: Number of Islands
 * @difficulty Medium
 * @link https://leetcode.com/problems/number-of-islands/
 *
 * Problem Description:
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and
 * '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically. You may assume all four edges of the grid are
 * all surrounded by water.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    /**
     * @brief Helper function to perform DFS traversal on the grid.
     * Sinks the island by changing '1's to '0's to track visited status.
     * 
     * @param grid The binary grid reference
     * @param r The current row index
     * @param c The current column index
     */
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int nr = grid.size();
        int nc = grid[0].size();

        // Guard clauses to prevent index out of bounds and to stop searching on water/visited land
        if (r < 0 || c < 0 || r >= nr || c >= nc || grid[r][c] == '0') {
            return;
        }

        // Mark the current cell as visited by sinking it to '0'
        grid[r][c] = '0';

        // Traverse all 4 cardinal directions (Up, Down, Left, Right)
        dfs(grid, r - 1, c); // Up
        dfs(grid, r + 1, c); // Down
        dfs(grid, r, c - 1); // Left
        dfs(grid, r, c + 1); // Right
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;

        int nr = grid.size();
        int nc = grid[0].size();
        int num_islands = 0;

        // Iterate through every cell in the grid
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                // If a piece of land is found, it marks the start of a new island
                if (grid[r][c] == '1') {
                    ++num_islands;
                    // Trigger DFS to traverse and sink the entire connected island
                    dfs(grid, r, c);
                }
            }
        }

        return num_islands;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace the algorithm on the following 4x5 grid:
 * 
 * Grid:
 * [
 *   ["1", "1", "0", "0", "0"],
 *   ["1", "1", "0", "0", "0"],
 *   ["0", "0", "1", "0", "0"],
 *   ["0", "0", "0", "1", "1"]
 * ]
 * 
 * 1. Iteration (r=0, c=0):
 *    - grid[0][0] == '1'. Increment num_islands to 1.
 *    - Call dfs(grid, 0, 0):
 *      - Mark grid[0][0] = '0'.
 *      - dfs(grid, -1, 0) -> Returns (Out of bounds).
 *      - dfs(grid, 1, 0): (grid[1][0] is '1')
 *        - Mark grid[1][0] = '0'.
 *        - dfs(grid, 0, 0) -> Returns (already '0').
 *        - dfs(grid, 2, 0) -> Returns (grid[2][0] is '0').
 *        - dfs(grid, 1, -1) -> Returns (Out of bounds).
 *        - dfs(grid, 1, 1): (grid[1][1] is '1')
 *          - Mark grid[1][1] = '0'.
 *          - dfs(grid, 0, 1): (grid[0][1] is '1')
 *            - Mark grid[0][1] = '0'.
 *            - All neighbors of (0,1) are '0' or out of bounds. Returns.
 *          - Neighbors of (1,1) are now all '0' or out of bounds. Returns.
 *        - Returns back to dfs(grid, 0, 0).
 *      - dfs(grid, 0, -1) -> Returns (Out of bounds).
 *      - dfs(grid, 0, 1) -> Returns (already '0').
 *    - Grid state after first island is processed:
 *      [
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "1", "0", "0"],
 *        ["0", "0", "0", "1", "1"]
 *      ]
 * 
 * 2. Continue scanning until (r=2, c=2):
 *    - grid[2][2] == '1'. Increment num_islands to 2.
 *    - Call dfs(grid, 2, 2):
 *      - Mark grid[2][2] = '0'.
 *      - Neighbors are all '0'. Returns.
 *    - Grid state:
 *      [
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "1", "1"]
 *      ]
 * 
 * 3. Continue scanning until (r=3, c=3):
 *    - grid[3][3] == '1'. Increment num_islands to 3.
 *    - Call dfs(grid, 3, 3):
 *      - Mark grid[3][3] = '0'.
 *      - dfs(grid, 3, 4): (grid[3][4] is '1')
 *        - Mark grid[3][4] = '0'.
 *        - Neighbors are all '0' or out of bounds. Returns.
 *      - Returns.
 *    - Grid state:
 *      [
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "0", "0"],
 *        ["0", "0", "0", "0", "0"]
 *      ]
 * 
 * 4. Scan finishes. Total num_islands = 3.
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(M * N)
 * - M is the number of rows, N is the number of columns.
 * - We visit every node in the grid at most a constant number of times (at most
 *   5 times: once in the outer loops, and up to 4 times from its neighbors).
 * 
 * Space Complexity: O(M * N)
 * - In the worst-case scenario where the entire grid is land ('1'), the call
 *   stack for DFS can grow to O(M * N) depth.
 */

int main() {
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    Solution solver;
    int islands = solver.numIslands(grid);
    cout << "Number of islands: " << islands << " (Expected: 3)" << endl;

    return 0;
}
