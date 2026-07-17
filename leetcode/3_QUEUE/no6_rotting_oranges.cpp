/**
 * @file no6_rotting_oranges.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 994: Rotting Oranges
 * @difficulty Medium
 * @link https://leetcode.com/problems/rotting-oranges/
 * 
 * @details
 * Problem Description:
 * You are given an `m x n` `grid` where each cell can have one of three values:
 * - `0` representing an empty cell,
 * - `1` representing a fresh orange, or
 * - `2` representing a rotten orange.
 * 
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. 
 * If this is impossible, return `-1`.
 * 
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 10
 * - grid[i][j] is 0, 1, or 2.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

class Solution {
private:
    // Structure to store grid coordinates
    struct Cell {
        int r; // Row index
        int c; // Column index
    };

public:
    /**
     * @brief Computes the minimum minutes to rot all fresh oranges.
     * @details This is solved using Breadth-First Search (BFS) starting with all 
     * initially rotten oranges in the queue. Since rotting spreads 4-directionally 
     * step-by-step (level-by-level), BFS simulates the minute-by-minute process perfectly.
     * 
     * @param grid The input m x n grid representing the state of oranges.
     * @return The minimum number of minutes, or -1 if some fresh oranges remain unreachable.
     * 
     * @time_complexity O(M * N) where M is the number of rows and N is the number of columns.
     * We visit each cell at most a constant number of times.
     * @space_complexity O(M * N) in the worst case for the queue if all oranges are rotten.
     */
    int orangesRotting(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        std::queue<Cell> q;
        int freshCount = 0;

        // Step 1: Scan grid to count fresh oranges and enqueue initial rotten ones
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        // Guard Clause: If there are no fresh oranges to rot, 0 minutes are needed.
        if (freshCount == 0) {
            return 0;
        }

        int minutes = 0;
        // Direction vectors for 4-directional moves (up, down, left, right)
        const int dRow[] = {-1, 1, 0, 0};
        const int dCol[] = {0, 0, -1, 1};

        // Step 2: Multi-source BFS
        while (!q.empty()) {
            int levelSize = q.size();
            bool rottedAnyThisMinute = false;

            // Process all rotten oranges at the current minute level
            for (int i = 0; i < levelSize; ++i) {
                Cell curr = q.front();
                q.pop();

                // Check all 4-directional neighbors
                for (int d = 0; d < 4; ++d) {
                    int nr = curr.r + dRow[d];
                    int nc = curr.c + dCol[d];

                    // Check bounds and whether neighbor is a fresh orange
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        // Rot the fresh orange
                        grid[nr][nc] = 2;
                        freshCount--;
                        // Add newly rotten orange to queue
                        q.push({nr, nc});
                        rottedAnyThisMinute = true;
                    }
                }
            }

            // Increment minutes only if we actually rotted at least one orange at this level
            if (rottedAnyThisMinute) {
                minutes++;
            }
        }

        // Step 3: If there are still fresh oranges left, they were isolated
        return (freshCount == 0) ? minutes : -1;
    }
};

/**
 * ============================================================================
 *                             MANUAL DRY-RUN TRACE
 * ============================================================================
 * Input Grid:
 * [ [2, 1, 1],
 *   [1, 1, 0],
 *   [0, 1, 1] ]
 * 
 * Initial Scan:
 * - Rotten found at (0, 0). Queue = [ {(0,0)} ]
 * - Fresh count = 6 (at (0,1), (0,2), (1,0), (1,1), (2,1), (2,2))
 * - freshCount = 6, minutes = 0.
 * 
 * --- Minute 1 ---
 * - Level size = 1. Pop {(0,0)}.
 * - Neighbors of (0,0):
 *   * (0,1) is fresh. Rot it (value=2). freshCount = 5. Queue = [ {(0,1)} ]
 *   * (1,0) is fresh. Rot it (value=2). freshCount = 4. Queue = [ {(0,1)}, {(1,0)} ]
 * - We rotted oranges, so minutes = 1.
 * 
 * --- Minute 2 ---
 * - Level size = 2.
 * - Pop {(0,1)}:
 *   * Neighbors: (0,2) is fresh. Rot it (value=2). freshCount = 3. Queue = [ {(1,0)}, {(0,2)} ]
 *   * Neighbors: (1,1) is fresh. Rot it (value=2). freshCount = 2. Queue = [ {(1,0)}, {(0,2)}, {(1,1)} ]
 * - Pop {(1,0)}:
 *   * Neighbors: Already rotten or empty.
 * - We rotted oranges, so minutes = 2.
 * 
 * --- Minute 3 ---
 * - Level size = 3.
 * - Pop {(0,2)}:
 *   * Neighbors: Already rotten or empty.
 * - Pop {(1,1)}:
 *   * Neighbors: (2,1) is fresh. Rot it (value=2). freshCount = 1. Queue = [ {(2,1)} ]
 * - Pop {(1,0)}: (already popped).
 * - We rotted oranges, so minutes = 3.
 * 
 * --- Minute 4 ---
 * - Level size = 1. Pop {(2,1)}.
 *   * Neighbors: (2,2) is fresh. Rot it (value=2). freshCount = 0. Queue = [ {(2,2)} ]
 * - We rotted oranges, so minutes = 4.
 * 
 * --- Minute 5 ---
 * - Level size = 1. Pop {(2,2)}.
 *   * Neighbors: None are fresh.
 * - No oranges rotted, minutes remains 4.
 * 
 * Queue is empty. freshCount is 0.
 * Returns minutes = 4.
 */

int main() {
    Solution solver;

    // Test Case 1: Standard case where all oranges can rot
    std::vector<std::vector<int>> gridTest1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    assert(solver.orangesRotting(gridTest1) == 4);

    // Test Case 2: One orange will never rot
    std::vector<std::vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    assert(solver.orangesRotting(grid2) == -1);

    // Test Case 3: Empty grid / No fresh oranges
    std::vector<std::vector<int>> grid3 = {
        {0, 2}
    };
    assert(solver.orangesRotting(grid3) == 0);

    // Test Case 4: Only fresh oranges, no rotten ones
    std::vector<std::vector<int>> grid4 = {
        {1, 1},
        {1, 1}
    };
    assert(solver.orangesRotting(grid4) == -1);

    std::cout << "All assertions for Rotting Oranges passed successfully!" << std::endl;
    return 0;
}
