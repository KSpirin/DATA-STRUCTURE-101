/**
 * @file no7_path_sum.cpp
 * @brief LeetCode 112 - Path Sum
 * 
 * Difficulty: Easy
 * LeetCode Link: https://leetcode.com/problems/path-sum/
 * 
 * Problem Description:
 * Given the root of a binary tree and an integer targetSum, return true if the 
 * tree has a root-to-leaf path such that adding up all the values along the 
 * path equals targetSum.
 * 
 * A leaf is a node with no children.
 */

#include <iostream>

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
    /**
     * @brief Determines if the tree has a root-to-leaf path with the given targetSum.
     * @param root The root of the binary tree.
     * @param targetSum The sum to check for.
     * @return true if such a path exists, false otherwise.
     */
    bool hasPathSum(TreeNode* root, int targetSum) {
        // Base case: If the node is null, no path exists
        if (root == nullptr) {
            return false;
        }

        // Check if the current node is a leaf
        if (root->left == nullptr && root->right == nullptr) {
            return root->val == targetSum;
        }

        // Subtract current node's value from targetSum and search recursively
        int remainingSum = targetSum - root->val;
        return hasPathSum(root->left, remainingSum) || hasPathSum(root->right, remainingSum);
    }
};

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *         5
 *        / \
 *       4   8
 *      /   / \
 *     11  13  4
 *    /  \      \
 *   7    2      1
 * 
 * Target Sum: 22
 * 
 * Step-by-Step execution of hasPathSum(root, 22):
 * 
 * 1. Call hasPathSum(node = 5, targetSum = 22)
 *    - Not null, not a leaf.
 *    - remainingSum = 22 - 5 = 17
 *    - Calls hasPathSum(node = 4, targetSum = 17) (left subtree)
 * 2. Call hasPathSum(node = 4, targetSum = 17)
 *    - Not null, not a leaf.
 *    - remainingSum = 17 - 4 = 13
 *    - Calls hasPathSum(node = 11, targetSum = 13) (left subtree)
 * 3. Call hasPathSum(node = 11, targetSum = 13)
 *    - Not null, not a leaf.
 *    - remainingSum = 13 - 11 = 2
 *    - Calls hasPathSum(node = 7, targetSum = 2) (left subtree)
 * 4. Call hasPathSum(node = 7, targetSum = 2)
 *    - Leaf node!
 *    - Does node->val (7) == targetSum (2)? No. Returns false.
 * 5. Back to node 11, calls hasPathSum(node = 2, targetSum = 2) (right subtree)
 * 6. Call hasPathSum(node = 2, targetSum = 2)
 *    - Leaf node!
 *    - Does node->val (2) == targetSum (2)? Yes. Returns true.
 * 7. Back to node 11, returns false || true -> true.
 * 8. Back to node 4, returns true (left call returned true).
 * 9. Back to node 5, returns true (left call returned true).
 * 
 * Result: true. Path 5 -> 4 -> 11 -> 2 has sum 5 + 4 + 11 + 2 = 22.
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Time Complexity: O(N)
 *   - In the worst case, we must visit every node in the binary tree once
 *     (e.g., if no path equals targetSum, or the matching path is the last one checked).
 *   - Each node visit involves O(1) operations.
 *   - Therefore, time complexity is O(N), where N is the number of nodes.
 * 
 * Space Complexity: O(H)
 *   - Determined by the depth of the recursion stack.
 *   - In the worst case (a completely skewed tree), H = O(N) space.
 *   - In the best/balanced case, H = O(log N) space.
 * =========================================================================
 */
