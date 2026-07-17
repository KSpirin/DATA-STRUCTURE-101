/**
 * @file no6_lca_bst.cpp
 * @brief LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 *
 * @details
 * Problem Description:
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
 * 
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor is defined between two nodes
 * p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself)."
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [2, 10^5].
 * - -10^9 <= Node.val <= 10^9
 * - All Node.val are Unique.
 * - p and q will exist in the BST.
 * - p != q
 */

#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /**
     * @brief Finds the lowest common ancestor of two nodes in a BST.
     *        Leverages the BST property: if both values are smaller than current, LCA is in left subtree;
     *        if both are larger, LCA is in right subtree; otherwise, current is the LCA.
     * @param root The root node of the BST.
     * @param p Pointer to the first target node.
     * @param q Pointer to the second target node.
     * @return TreeNode* Pointer to the LCA node.
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        
        while (curr != nullptr) {
            // If both p and q are smaller than the current node's value, LCA must be in the left subtree.
            if (p->val < curr->val && q->val < curr->val) {
                curr = curr->left;
            }
            // If both p and q are larger than the current node's value, LCA must be in the right subtree.
            else if (p->val > curr->val && q->val > curr->val) {
                curr = curr->right;
            }
            // If they split (one is smaller/equal and the other is larger/equal), the current node is the LCA.
            else {
                return curr;
            }
        }
        
        return nullptr;
    }
};

/*
=========================================
      MANUAL DRY-RUN / TRACE
=========================================
Input Tree:
        6
      /   \
     2     8
    / \   / \
   0   4 7   9
      / \
     3   5

Test Case 1: p = 2, q = 8
Trace using lowestCommonAncestor(root = [6], p = [2], q = [8]):
1. Initialize: curr = [6]
2. Loop step 1: 
   - curr->val = 6
   - p->val = 2, q->val = 8
   - p->val < 6 is true, but q->val < 6 is false.
   - p->val > 6 is false.
   - We fall into the else block. Return curr [6].
Result: Node with value 6.

Test Case 2: p = 2, q = 4
Trace using lowestCommonAncestor(root = [6], p = [2], q = [4]):
1. Initialize: curr = [6]
2. Loop step 1:
   - curr->val = 6
   - p->val = 2, q->val = 4
   - Both p->val (2) and q->val (4) are less than curr->val (6).
   - Update curr = curr->left ([2]).
3. Loop step 2:
   - curr->val = 2
   - p->val = 2, q->val = 4
   - p->val < 2 is false.
   - p->val > 2 is false.
   - We fall into the else block. Return curr [2].
Result: Node with value 2.

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- O(H) - where H is the height of the BST.
  In the worst case (skewed tree), we might traverse from root to leaf, taking O(N) time.
  In the best case (balanced tree), the height H is O(log N).

Space Complexity:
- O(1) - because we use an iterative approach with a single pointer `curr` and no extra memory.
  (If implemented recursively, space complexity would be O(H) due to the call stack).
*/

int main() {
    Solution sol;

    // Construct the BST:
    //        6
    //      /   \
    //     2     8
    //    / \   / \
    //   0   4 7   9
    //      / \
    //     3   5
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4, new TreeNode(3), new TreeNode(5));
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    // Test Case 1: p = 2, q = 8 -> LCA = 6
    TreeNode* p1 = root->left; // 2
    TreeNode* q1 = root->right; // 8
    TreeNode* ans1 = sol.lowestCommonAncestor(root, p1, q1);
    if (ans1 != nullptr && ans1->val == 6) {
        std::cout << "Test 1 Passed: LCA(2, 8) = " << ans1->val << std::endl;
    } else {
        std::cout << "Test 1 Failed!" << std::endl;
    }

    // Test Case 2: p = 2, q = 4 -> LCA = 2
    TreeNode* p2 = root->left; // 2
    TreeNode* q2 = root->left->right; // 4
    TreeNode* ans2 = sol.lowestCommonAncestor(root, p2, q2);
    if (ans2 != nullptr && ans2->val == 2) {
        std::cout << "Test 2 Passed: LCA(2, 4) = " << ans2->val << std::endl;
    } else {
        std::cout << "Test 2 Failed!" << std::endl;
    }

    // Clean up memory
    delete root->left->right->left; // 3
    delete root->left->right->right; // 5
    delete root->left->right; // 4
    delete root->left->left; // 0
    delete root->left; // 2
    delete root->right->left; // 7
    delete root->right->right; // 9
    delete root->right; // 8
    delete root; // 6

    return 0;
}
