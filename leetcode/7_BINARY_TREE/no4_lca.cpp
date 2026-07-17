/**
 * @file no4_lowest_common_ancestor.cpp
 * @brief LeetCode 236 - Lowest Common Ancestor of a Binary Tree
 * 
 * Difficulty: Medium
 * LeetCode Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
 * 
 * Problem Description:
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined 
 * between two nodes p and q as the lowest node in T that has both p and q as descendants 
 * (where we allow a node to be a descendant of itself).”
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [2, 10^5].
 * - -10^9 <= Node.val <= 10^9
 * - All Node.val are unique.
 * - p and q will exist in the tree.
 * - p != q
 */

#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * @brief Finds the lowest common ancestor (LCA) of two nodes p and q.
     * 
     * Rationale:
     * We perform a bottom-up postorder-like traversal. At each node:
     * 1. If the current node is null, we return nullptr.
     * 2. If the current node matches p or q, we return the current node.
     * 3. Recursively search the left and right subtrees.
     * 4. If both left and right subtree searches return non-null results, it means
     *    one target node is in the left subtree and the other is in the right subtree.
     *    Thus, the current node is the lowest common ancestor.
     * 5. If only one of the subtrees returns a non-null result, it means both target 
     *    nodes are located in that subtree (or only one was found so far). We propagate
     *    the non-null result up.
     * 
     * Time Complexity: O(N) where N is the number of nodes in the tree. In the worst case, 
     *                  we visit all nodes.
     * Space Complexity: O(H) where H is the height of the tree. This is determined by the
     *                   maximum depth of the recursion stack. (O(log N) for balanced trees,
     *                   O(N) for skewed trees).
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Base case: if we reach a null node, or find either target node, return root.
        if (root == nullptr || root == p || root == q) {
            return root;
        }

        // Recurse into left and right subtrees
        TreeNode* leftLCA = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightLCA = lowestCommonAncestor(root->right, p, q);

        // If leftLCA and rightLCA are both non-null, the current root is the LCA.
        if (leftLCA != nullptr && rightLCA != nullptr) {
            return root;
        }

        // Otherwise, return the non-null result (propagating the found node or LCA up)
        return (leftLCA != nullptr) ? leftLCA : rightLCA;
    }
};

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *        3
 *       / \
 *      5   1
 *     / \  / \
 *    6   2 0   8
 *       / \
 *      7   4
 * 
 * Target Nodes: p = 5, q = 1
 * -------------------------------------------------------------------------
 * Recursion calls on root = 3:
 * 1. call lowestCommonAncestor(3, 5, 1)
 *    - root (3) != nullptr, != 5, != 1.
 *    - call lowestCommonAncestor(5, 5, 1) [left child]
 *      - root (5) == p (5). Returns 5.
 *      - leftLCA for 3 becomes 5.
 *    - call lowestCommonAncestor(1, 5, 1) [right child]
 *      - root (1) == q (1). Returns 1.
 *      - rightLCA for 3 becomes 1.
 *    - both leftLCA (5) and rightLCA (1) are non-null.
 *    - returns root (3).
 * Output: LCA is node 3.
 * 
 * -------------------------------------------------------------------------
 * Target Nodes: p = 5, q = 4
 * -------------------------------------------------------------------------
 * Recursion calls on root = 3:
 * 1. call lowestCommonAncestor(3, 5, 4)
 *    - root (3) != nullptr, != p, != q.
 *    - call lowestCommonAncestor(5, 5, 4) [left child]
 *      - root (5) == p (5). Returns 5.
 *      - leftLCA for 3 becomes 5.
 *    - call lowestCommonAncestor(1, 5, 4) [right child]
 *      - root (1) != nullptr, != p, != q.
 *      - call lowestCommonAncestor(0, 5, 4) [left child of 1]
 *        - root (0) == nullptr base case? No, 0 has no children.
 *          - call lowestCommonAncestor(null, 5, 4) -> returns null.
 *          - call lowestCommonAncestor(null, 5, 4) -> returns null.
 *          - returns null.
 *      - call lowestCommonAncestor(8, 5, 4) [right child of 1]
 *        - returns null.
 *      - both left and right of 1 returned null, so lowestCommonAncestor(1, 5, 4) returns null.
 *      - rightLCA for 3 becomes null.
 *    - leftLCA (5) is non-null, rightLCA (null) is null.
 *    - returns leftLCA (5).
 * Output: LCA is node 5. (Indeed, node 5 is the ancestor of both 5 and 4).
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Time Complexity: O(N)
 *   - In the worst case, we must visit every node in the binary tree to find p and q.
 *   - Each node is visited at most twice (one pre-order/post-order pass).
 * Space Complexity: O(H)
 *   - The maximum depth of the recursion stack is equal to the height of the tree H.
 *   - In the worst-case (completely skewed tree), space is O(N).
 *   - In the best-case (completely balanced tree), space is O(log N).
 * =========================================================================
 */
