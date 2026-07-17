/**
 * @file no6_diameter_of_tree.cpp
 * @brief LeetCode 543 - Diameter of Binary Tree
 * 
 * Difficulty: Easy
 * LeetCode Link: https://leetcode.com/problems/diameter-of-binary-tree/
 * 
 * Problem Description:
 * Given the root of a binary tree, return the length of the diameter of the tree.
 * The diameter of a binary tree is the length of the longest path between any two 
 * nodes in a tree. This path may or may not pass through the root.
 * The length of a path between two nodes is represented by the number of edges 
 * between them.
 */

#include <algorithm>
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
private:
    int max_diameter = 0;

    /**
     * @brief Helper function to compute the height of the tree and update diameter.
     * @param node The current node under examination.
     * @return The height of the tree rooted at node (number of nodes in the longest path to a leaf).
     */
    int calculateHeightAndDiameter(TreeNode* node) {
        if (node == nullptr) {
            return 0; // Height of an empty subtree is 0
        }

        // Recursively find the height of left and right subtrees
        int leftHeight = calculateHeightAndDiameter(node->left);
        int rightHeight = calculateHeightAndDiameter(node->right);

        // The diameter passing through the current node is the sum of left and right heights
        // (number of edges on the path connecting the deepest nodes in left and right subtrees)
        max_diameter = std::max(max_diameter, leftHeight + rightHeight);

        // Return height of the current node
        return 1 + std::max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        max_diameter = 0;
        calculateHeightAndDiameter(root);
        return max_diameter;
    }
};

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 * 
 * Step-by-Step execution of calculateHeightAndDiameter():
 * 
 * 1. Call calculateHeightAndDiameter(node = 1)
 *    - Calls calculateHeightAndDiameter(node = 2)
 * 2. Call calculateHeightAndDiameter(node = 2)
 *    - Calls calculateHeightAndDiameter(node = 4)
 * 3. Call calculateHeightAndDiameter(node = 4)
 *    - Calls calculateHeightAndDiameter(node = nullptr) -> returns 0 (left)
 *    - Calls calculateHeightAndDiameter(node = nullptr) -> returns 0 (right)
 *    - Update max_diameter = max(0, 0 + 0) = 0
 *    - Returns 1 + max(0, 0) = 1 (height of node 4)
 * 4. Back to node 2, leftHeight = 1.
 *    - Calls calculateHeightAndDiameter(node = 5)
 * 5. Call calculateHeightAndDiameter(node = 5)
 *    - Calls calculateHeightAndDiameter(node = nullptr) -> returns 0 (left)
 *    - Calls calculateHeightAndDiameter(node = nullptr) -> returns 0 (right)
 *    - Update max_diameter = max(0, 0 + 0) = 0
 *    - Returns 1 + max(0, 0) = 1 (height of node 5)
 * 6. Back to node 2, rightHeight = 1.
 *    - Update max_diameter = max(0, 1 + 1) = 2 (path: 4 -> 2 -> 5)
 *    - Returns 1 + max(1, 1) = 2 (height of node 2)
 * 7. Back to node 1, leftHeight = 2.
 *    - Calls calculateHeightAndDiameter(node = 3)
 * 8. Call calculateHeightAndDiameter(node = 3)
 *    - Calls calculateHeightAndDiameter(node = nullptr) -> returns 0
 *    - Calls calculateHeightAndDiameter(node = nullptr) -> returns 0
 *    - Update max_diameter = max(2, 0 + 0) = 2
 *    - Returns 1 + max(0, 0) = 1 (height of node 3)
 * 9. Back to node 1, rightHeight = 1.
 *    - Update max_diameter = max(2, 2 + 1) = 3 (path: 4 -> 2 -> 1 -> 3 or 5 -> 2 -> 1 -> 3)
 *    - Returns 1 + max(2, 1) = 3 (height of node 1)
 * 
 * Result: max_diameter = 3. Correct.
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Time Complexity: O(N)
 *   - We visit every node in the binary tree exactly once.
 *   - At each node, the work done (computing sum and max, updating diameter) is O(1).
 *   - Thus, total time complexity is linear, O(N), where N is the number of nodes.
 * 
 * Space Complexity: O(H)
 *   - The space complexity is determined by the recursion stack.
 *   - In the worst case (a highly skewed tree), the height of the tree is H = O(N),
 *     requiring O(N) space.
 *   - In the best case (a balanced binary tree), the height is H = O(log N),
 *     requiring O(log N) space.
 * =========================================================================
 */
