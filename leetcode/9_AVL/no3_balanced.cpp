/**
 * @file no3_is_balanced.cpp
 * @brief LeetCode 110: Balanced Binary Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/balanced-binary-tree/
 *
 * Problem Description:
 * Given a binary tree, determine if it is height-balanced.
 *
 * A height-balanced binary tree is defined as:
 * A binary tree in which the left and right subtrees of every node differ in height by no more than 1.
 *
 * Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: true
 *
 * Example 2:
 * Input: root = [1,2,2,3,3,null,null,4,4]
 * Output: false
 */

#include <iostream>
#include <algorithm>
#include <cmath>

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
    /*
     * Helper function to check if the tree is balanced and return its height.
     * If the tree is unbalanced, it returns -1.
     *
     * Note: Here we use the standard LeetCode height convention where height(nullptr) = 0
     * and height(leaf) = 1. This matches the logic of AVL Tree's height(nullptr) = -1
     * and height(leaf) = 0, because the difference (left_height - right_height) remains identical.
     */
    int checkHeight(TreeNode* node) {
        // Base case: An empty node has a height of 0 (which is balanced)
        if (!node) {
            return 0;
        }

        // Recursively find the height of the left subtree
        int leftHeight = checkHeight(node->left);
        // If the left subtree is already unbalanced, propagate the failure up
        if (leftHeight == -1) {
            return -1;
        }

        // Recursively find the height of the right subtree
        int rightHeight = checkHeight(node->right);
        // If the right subtree is already unbalanced, propagate the failure up
        if (rightHeight == -1) {
            return -1;
        }

        // Check if the current node violates the balance condition:
        // Height of left and right subtrees cannot differ by more than 1
        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1; // Unbalanced
        }

        // If balanced, return the height of the current node
        return 1 + std::max(leftHeight, rightHeight);
    }

public:
    bool isBalanced(TreeNode* root) {
        // The tree is balanced if checkHeight does not return -1
        return checkHeight(root) != -1;
    }
};

/*
 * =========================================================================
 * MANUAL DRY-RUN TRACE
 * =========================================================================
 * Input Tree (Example 2): [1, 2, 2, 3, 3, null, null, 4, 4]
 * 
 *          1
 *        /   \
 *       2     2
 *      / \
 *     3   3
 *    / \
 *   4   4
 * 
 * 1. checkHeight(node 4):
 *    - Left and right are null -> returns 1.
 * 
 * 2. checkHeight(node 3 [left child of 2]):
 *    - leftHeight = 1 (from node 4)
 *    - rightHeight = 1 (from node 4)
 *    - abs(1 - 1) = 0 <= 1. Node 3 is balanced.
 *    - Returns 1 + max(1, 1) = 2.
 * 
 * 3. checkHeight(node 3 [right child of 2]):
 *    - Left and right are null -> returns 1.
 * 
 * 4. checkHeight(node 2 [left child of 1]):
 *    - leftHeight = 2 (from node 3 [left])
 *    - rightHeight = 1 (from node 3 [right])
 *    - abs(2 - 1) = 1 <= 1. Node 2 is balanced.
 *    - Returns 1 + max(2, 1) = 3.
 * 
 * 5. checkHeight(node 2 [right child of 1]):
 *    - Left and right are null -> returns 1.
 * 
 * 6. checkHeight(node 1 [root]):
 *    - leftHeight = 3 (from node 2 [left])
 *    - rightHeight = 1 (from node 2 [right])
 *    - abs(3 - 1) = 2 > 1. Height difference is 2!
 *    - Returns -1 (indicating unbalanced).
 * 
 * 7. isBalanced(root):
 *    - checkHeight(root) returned -1.
 *    - Returns false.
 * 
 * =========================================================================
 * TIME AND SPACE COMPLEXITY ANALYSIS
 * =========================================================================
 * - Time Complexity: O(N)
 *   We perform a post-order traversal where each node is visited exactly once. 
 *   The height of subtrees is computed bottom-up, preventing the O(N^2) complexity 
 *   of the naive approach where height is computed repeatedly for each node.
 * - Space Complexity: O(H)
 *   In the worst case (skewed tree), the space complexity is O(N) due to recursion stack.
 *   In the best/average case (balanced tree), the space complexity is O(log N).
 */

int main() {
    Solution solver;

    // Build the tree for Example 1: [3, 9, 20, null, null, 15, 7]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    if (solver.isBalanced(root)) {
        std::cout << "Tree 1 is balanced.\n";
    } else {
        std::cout << "Tree 1 is NOT balanced.\n";
    }

    // Build the tree for Example 2: [1, 2, 2, 3, 3, null, null, 4, 4]
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(3);
    root2->left->left->left = new TreeNode(4);
    root2->left->left->right = new TreeNode(4);

    if (solver.isBalanced(root2)) {
        std::cout << "Tree 2 is balanced.\n";
    } else {
        std::cout << "Tree 2 is NOT balanced.\n";
    }

    // Clean up memory
    delete root2->left->left->right;
    delete root2->left->left->left;
    delete root2->left->right;
    delete root2->left->left;
    delete root2->left;
    delete root2->right;
    delete root2;

    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
