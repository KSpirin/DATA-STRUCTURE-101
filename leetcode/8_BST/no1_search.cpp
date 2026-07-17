/**
 * @file no1_search_bst.cpp
 * @brief LeetCode 700: Search in a Binary Search Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/search-in-a-binary-search-tree/
 *
 * @details
 * Problem Description:
 * You are given the root of a binary search tree (BST) and an integer val.
 * Find the node in the BST that the node's value equals val and return the subtree rooted with that node.
 * If such a node does not exist, return null.
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
     * @brief Searches for a node with value `val` in the BST recursively.
     * @param root The root of the BST.
     * @param val The value to search for.
     * @return TreeNode* The node matching the value, or nullptr if not found.
     */
    TreeNode* searchBST(TreeNode* root, int val) {
        // Base Cases: root is null (not found) or root's key is the target
        if (root == nullptr || root->val == val) {
            return root;
        }
        
        // If the target value is less than the current node's value, search the left subtree.
        if (val < root->val) {
            return searchBST(root->left, val);
        }
        
        // Otherwise, search the right subtree.
        return searchBST(root->right, val);
    }

    /**
     * @brief Searches for a node with value `val` in the BST iteratively.
     *        This optimization runs in O(1) auxiliary space.
     * @param root The root of the BST.
     * @param val The value to search for.
     * @return TreeNode* The node matching the value, or nullptr if not found.
     */
    TreeNode* searchBSTIterative(TreeNode* root, int val) {
        TreeNode* curr = root;
        while (curr != nullptr && curr->val != val) {
            if (val < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return curr;
    }
};

/*
=========================================
      MANUAL DRY-RUN / TRACE
=========================================
Input Tree:
       4
      / \
     2   7
    / \
   1   3
Target val = 2

Trace using Recursive searchBST(root = [4], val = 2):
1. Call searchBST(root=[4], val=2):
   - root is not null and root->val (4) != val (2).
   - Check condition: val (2) < root->val (4).
   - Since 2 < 4, recursively call searchBST(root->left=[2], val=2).
   
2. Call searchBST(root=[2], val=2):
   - root is not null.
   - Check condition: root->val (2) == val (2).
   - Match found! Return the subtree rooted at [2] (i.e., node 2 with children 1 and 3).

3. Call returns [2] up the stack to the caller.
Final output: Node [2] (Subtree: [2, 1, 3])

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- Average Case: O(log N) - where N is the number of nodes. At each step, we discard half of the tree.
- Worst Case: O(N) - occurs when the tree is a skewed binary tree (like a linked list) and we search for a leaf or non-existent value.

Space Complexity:
- Recursive Approach:
  * Average Case: O(log N) - for the recursion call stack.
  * Worst Case: O(N) - call stack height for a skewed tree.
- Iterative Approach:
  * O(1) - auxiliary space since no call stack is used.
*/

int main() {
    // Simple verification check
    Solution sol;
    
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    
    TreeNode* result = sol.searchBST(root, 2);
    if (result != nullptr && result->val == 2) {
        std::cout << "Test passed! Found node with value 2." << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }
    
    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}
