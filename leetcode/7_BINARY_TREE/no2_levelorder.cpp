/**
 * @file no2_level_order.cpp
 * @brief LeetCode 102: Binary Tree Level Order Traversal
 * 
 * Difficulty: Medium
 * LeetCode Link: https://leetcode.com/problems/binary-tree-level-order-traversal/
 * 
 * Problem Description:
 * Given the root of a binary tree, return the level order traversal of its 
 * nodes' values. (i.e., from left to right, level by level).
 * 
 * Example:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
 */

#include <vector>
#include <queue>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Time Complexity: O(N) - visits each node exactly once
    // Space Complexity: O(N) - to hold the queue and the result vector
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) {
            return result; // Guard clause for empty tree
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            // Number of elements at the current level
            int levelSize = q.size();
            std::vector<int> currentLevel;

            // Process all nodes at the current level
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* curr = q.front();
                q.pop();

                // Add current node value to level representation
                currentLevel.push_back(curr->val);

                // Queue children of current node for the next level
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }
                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }

            // Append the level result
            result.push_back(currentLevel);
        }

        return result;
    }
};

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *        3
 *       / \
 *      9  20
 *        /  \
 *       15   7
 * 
 * Queue state during execution:
 * 1. Initial State: q = [3]
 * 2. Outer Loop Iteration 1:
 *    - levelSize = q.size() = 1
 *    - currentLevel = []
 *    - Process i = 0:
 *      - curr = 3, pop 3. q = []
 *      - currentLevel = [3]
 *      - Push children of 3 (9, 20). q = [9, 20]
 *    - Append currentLevel [3] to result. result = [[3]]
 * 
 * 3. Outer Loop Iteration 2:
 *    - levelSize = q.size() = 2 (nodes 9 and 20)
 *    - currentLevel = []
 *    - Process i = 0 (node 9):
 *      - curr = 9, pop 9. q = [20]
 *      - currentLevel = [9]
 *      - Children of 9 are null, nothing pushed.
 *    - Process i = 1 (node 20):
 *      - curr = 20, pop 20. q = []
 *      - currentLevel = [9, 20]
 *      - Push children of 20 (15, 7). q = [15, 7]
 *    - Append currentLevel to result. result = [[3], [9, 20]]
 * 
 * 4. Outer Loop Iteration 3:
 *    - levelSize = q.size() = 2 (nodes 15 and 7)
 *    - currentLevel = []
 *    - Process i = 0 (node 15):
 *      - curr = 15, pop 15. q = [7]
 *      - currentLevel = [15]
 *      - Children are null.
 *    - Process i = 1 (node 7):
 *      - curr = 7, pop 7. q = []
 *      - currentLevel = [15, 7]
 *      - Children are null.
 *    - Append currentLevel to result. result = [[3], [9, 20], [15, 7]]
 * 
 * 5. Outer Loop exits because q is empty.
 * Return result = [[3], [9, 20], [15, 7]]. Correct.
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Time Complexity: O(N)
 *   We process each node in the tree exactly once. Insertion and removal from 
 *   the queue are O(1) operations. Thus, runtime scale linearly with nodes.
 * 
 * Space Complexity: O(N)
 *   In the worst case (perfect binary tree), the queue will hold all leaf nodes 
 *   at the bottom level. The bottom level of a perfect binary tree has 
 *   ceil(N / 2) nodes. Therefore, space complexity is O(N).
 * =========================================================================
 */
