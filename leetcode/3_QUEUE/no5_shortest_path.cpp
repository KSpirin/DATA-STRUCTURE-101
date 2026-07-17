/**
 * @file no5_shortest_path_binary_matrix.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 1091: Shortest Path in Binary Matrix
 * @difficulty Medium
 * @link https://leetcode.com/problems/shortest-path-in-binary-matrix/
 * 
 * @details
 * Problem Description:
 * Given an `n x n` binary matrix `grid`, return the length of the shortest clear path 
 * in the matrix. If there is no clear path, return -1.
 * 
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to 
 * the bottom-right cell (i.e., (n - 1, n - 1)) such that:
 * 1. All the visited cells of the path are 0.
 * 2. All the adjacent cells of the path are 8-directionally connected (i.e., they are 
 *    different and share an edge or a corner).
 * 
 * The length of a clear path is the number of visited cells in this path.
 * 
 * Constraints:
 * - n == grid.length
 * - n == grid[i].length
 * - 1 <= n <= 100
 * - grid[i][j] is 0 or 1
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
private:
    // Definition of a grid cell to store coordinates and the current path distance
    struct Cell {
        int r; // Row index
        int c; // Column index
        int dist; // Path length from (0, 0) to this cell
    };

public:
    /**
     * @brief Finds the length of the shortest clear path in a binary matrix.
     * @details This problem is solved using Breadth-First Search (BFS) starting from 
     * the top-left cell (0, 0) to the bottom-right cell (n - 1, n - 1).
     * BFS is optimal because it guarantees finding the shortest path in an unweighted grid 
     * by exploring all paths level-by-level (expanding outwards like a wave).
     * 
     * @param grid The input n x n binary grid.
     * @return The length of the shortest clear path, or -1 if no such path exists.
     * 
     * @time_complexity O(N^2) where N is the grid dimension. In the worst case, we visit every cell once.
     * @space_complexity O(N^2) in the worst case for the BFS queue size and/or the visited grid mapping.
     */
    int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
        int n = grid.size();

        // Guard Clause 1: If the start cell or destination cell is blocked (contains 1), no path is possible.
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1;
        }

        // BFS Queue to keep track of cells to visit
        std::queue<Cell> q;

        // Push start cell (0, 0) with a path distance of 1
        q.push({0, 0, 1});
        // Mark the start cell as visited (we modify grid in-place to save memory)
        grid[0][0] = 1; 

        // Define the 8 directions (up, down, left, right, and 4 diagonals)
        const int dRow[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dCol[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        while (!q.empty()) {
            Cell curr = q.front();
            q.pop();

            // Check if we have reached the destination cell (n - 1, n - 1)
            if (curr.r == n - 1 && curr.c == n - 1) {
                return curr.dist;
            }

            // Explore all 8 adjacent directions
            for (int i = 0; i < 8; ++i) {
                int nr = curr.r + dRow[i];
                int nc = curr.c + dCol[i];

                // Check bounds and make sure the target cell is clear (0)
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                    // Mark as visited BEFORE pushing to queue to avoid duplicate entries in queue
                    grid[nr][nc] = 1; 
                    q.push({nr, nc, curr.dist + 1});
                }
            }
        }

        // Destination is unreachable
        return -1;
    }
};

/**
 * ============================================================================
 *                             MANUAL DRY-RUN TRACE
 * ============================================================================
 * Input Grid:
 * [ [0, 0, 0],
 *   [1, 1, 0],
 *   [1, 1, 0] ]
 * 
 * N = 3. Target: (2, 2)
 * 
 * 1. Initial Check: grid[0][0] is 0, grid[2][2] is 0. Valid.
 * 2. Enqueue (0, 0) with distance 1. Mark grid[0][0] = 1.
 *    - Queue state: [ {(0,0), dist=1} ]
 * 
 * 3. Pop {(0,0), dist=1} from queue.
 *    - Explore 8 directions:
 *      * (0, 1): Value is 0. Mark grid[0][1] = 1. Enqueue {(0,1), dist=2}.
 *      * (1, 0): Value is 1 (Blocked).
 *      * (1, 1): Value is 1 (Blocked).
 *    - Queue state: [ {(0,1), dist=2} ]
 * 
 * 4. Pop {(0,1), dist=2} from queue.
 *    - Explore 8 directions:
 *      * (0, 0): Already visited (Value is 1).
 *      * (0, 2): Value is 0. Mark grid[0][2] = 1. Enqueue {(0,2), dist=3}.
 *      * (1, 0), (1, 1): Blocked.
 *      * (1, 2): Value is 0. Mark grid[1][2] = 1. Enqueue {(1,2), dist=3}.
 *    - Queue state: [ {(0,2), dist=3}, {(1,2), dist=3} ]
 * 
 * 5. Pop {(0,2), dist=3} from queue.
 *    - Explore 8 directions:
 *      * (0, 1), (1, 2): Already visited.
 *      * (1, 1): Blocked.
 *    - Queue state: [ {(1,2), dist=3} ]
 * 
 * 6. Pop {(1,2), dist=3} from queue.
 *    - Explore 8 directions:
 *      * (2, 2): Value is 0. Mark grid[2][2] = 1. Enqueue {(2,2), dist=4}.
 *      * Others: Blocked or Visited.
 *    - Queue state: [ {(2,2), dist=4} ]
 * 
 * 7. Pop {(2,2), dist=4} from queue.
 *    - Since row == N-1 && col == N-1, return dist = 4.
 * 
 * Final returned path length: 4
 */

int main() {
    Solution solver;

    // Test Case 1: Simple 3x3 Grid with path
    std::vector<std::vector<int>> grid1 = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    assert(solver.shortestPathBinaryMatrix(grid1) == 4);

    // Test Case 2: 2x2 Grid with straight diagonal path
    std::vector<std::vector<int>> grid2 = {
        {0, 1},
        {1, 0}
    };
    assert(solver.shortestPathBinaryMatrix(grid2) == 2);

    // Test Case 3: Blocked Start
    std::vector<std::vector<int>> grid3 = {
        {1, 0},
        {0, 0}
    };
    assert(solver.shortestPathBinaryMatrix(grid3) == -1);

    // Test Case 4: No Path Possible
    std::vector<std::vector<int>> grid4 = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    assert(solver.shortestPathBinaryMatrix(grid4) == -1);

    std::cout << "All assertions for Shortest Path in Binary Matrix passed successfully!" << std::endl;
    return 0;
}
