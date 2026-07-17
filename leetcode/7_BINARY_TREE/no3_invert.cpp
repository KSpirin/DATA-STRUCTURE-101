/**
 * @file no3_invert_tree.cpp
 * @brief LeetCode 226: Invert Binary Tree
 * 
 * Difficulty: Easy
 * LeetCode Link: https://leetcode.com/problems/invert-binary-tree/
 * 
 * Problem Description:
 * Given the root of a binary tree, invert the tree, and return its root.
 * 
 * Example:
 * Input: root = [4,2,7,1,3,6,9]
 * Output: [4,7,2,9,6,3,1]
 */

#include <algorithm>
#include <queue>
#include <stack>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class SolutionRecursive {
public:
    // Time Complexity: O(N) - visits each node exactly once
    // Space Complexity: O(H) - recursion stack depth (H = tree height)
    TreeNode* invertTree(TreeNode* root) {
        // Base case: If root is null, return null
        if (root == nullptr) {
            return nullptr;
        }

        // Recursively invert left and right subtrees
        TreeNode* leftInverted = invertTree(root->left);
        TreeNode* rightInverted = invertTree(root->right);

        // Swap the left and right children
        root->left = rightInverted;
        root->right = leftInverted;

        // Return the root of the inverted tree
        return root;
    }
};

class SolutionIterative {
public:
    // Time Complexity: O(N) - visits each node exactly once
    // Space Complexity: O(W) - where W is the maximum width of the tree (BFS queue size)
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }

        // Standard BFS queue to visit level by level and swap children
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            // Swap children of current node
            std::swap(curr->left, curr->right);

            // If children exist, push them to queue to swap their sub-children later
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }

        return root;
    }
};

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *        4
 *       / \
 *      2   7
 *     / \ / \
 *    1  3 6  9
 * 
 * Recursive Dry Run:
 * Step 1: Call invertTree(4).
 *   - Call invertTree(2).
 *     - Call invertTree(1).
 *       - Call invertTree(nullptr) -> returns nullptr.
 *       - Call invertTree(nullptr) -> returns nullptr.
 *       - Swap: 1->left = nullptr, 1->right = nullptr. Return 1.
 *     - Call invertTree(3).
 *       - Call invertTree(nullptr) -> returns nullptr.
 *       - Call invertTree(nullptr) -> returns nullptr.
 *       - Swap: 3->left = nullptr, 3->right = nullptr. Return 3.
 *     - Swap: 2->left = 3, 2->right = 1. Return 2.
 *   - Call invertTree(7).
 *     - Call invertTree(6).
 *       - Return 6.
 *     - Call invertTree(9).
 *       - Return 9.
 *     - Swap: 7->left = 9, 7->right = 6. Return 7.
 *   - Swap: 4->left = 7, 4->right = 2. Return 4.
 * 
 * Final Inverted Structure:
 *        4
 *       / \
 *      7   2
 *     / \ / \
 *    9  6 3  1
 * Correct.
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Recursive Approach:
 *   - Time Complexity: O(N)
 *     Since each node in the tree is visited exactly once, the time complexity
 *     scales linearly with the number of nodes.
 *   - Space Complexity: O(H)
 *     Where H is the height of the tree. The recursion stack uses space proportional
 *     to the height of the tree. In the worst case (skewed tree), H = O(N).
 *     In the average/best case (balanced tree), H = O(log N).
 * 
 * Iterative Approach:
 *   - Time Complexity: O(N)
 *     Each node is queued and dequeued once, performing O(1) swaps.
 *   - Space Complexity: O(W)
 *     Where W is the maximum width of the tree (number of nodes in the widest level).
 *     In a perfect binary tree, this is O(N).
 * =========================================================================
 */
