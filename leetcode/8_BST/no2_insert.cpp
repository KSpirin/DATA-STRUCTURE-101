/**
 * @file no2_insert_bst.cpp
 * @brief LeetCode 701: Insert into a Binary Search Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/insert-into-a-binary-search-tree/
 *
 * @details
 * Problem Description:
 * You are given the root node of a binary search tree (BST) and a value to insert into the tree.
 * Return the root node of the BST after the insertion. It is guaranteed that the new value does
 * not exist in the original BST.
 *
 * Notice that there may exist multiple valid ways for the insertion, as long as the tree remains
 * a BST after insertion. You can return any of them.
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
     * @brief Inserts a value into the BST recursively.
     * @param root The root of the BST.
     * @param val The value to insert.
     * @return TreeNode* The root of the updated BST.
     */
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // Base case: If we reach an empty position, create and return the new node.
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        // If the value is less than the current node's value, insert into the left subtree.
        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        }
        // Otherwise, insert into the right subtree.
        else {
            root->right = insertIntoBST(root->right, val);
        }
        
        return root;
    }

    /**
     * @brief Inserts a value into the BST iteratively.
     *        This optimization uses O(1) auxiliary space.
     * @param root The root of the BST.
     * @param val The value to insert.
     * @return TreeNode* The root of the updated BST.
     */
    TreeNode* insertIntoBSTIterative(TreeNode* root, int val) {
        // If tree is empty, return a new node.
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        TreeNode* curr = root;
        while (true) {
            if (val < curr->val) {
                // If left child is null, insert here and break.
                if (curr->left == nullptr) {
                    curr->left = new TreeNode(val);
                    break;
                }
                curr = curr->left;
            } else {
                // If right child is null, insert here and break.
                if (curr->right == nullptr) {
                    curr->right = new TreeNode(val);
                    break;
                }
                curr = curr->right;
            }
        }
        return root;
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
Target val = 5

Trace using Recursive insertIntoBST(root = [4], val = 5):
1. Call insertIntoBST(root=[4], val=5):
   - root is not null.
   - val (5) > root->val (4).
   - Set root->right = insertIntoBST(root->right=[7], val=5).

2. Call insertIntoBST(root=[7], val=5):
   - root is not null.
   - val (5) < root->val (7).
   - Set root->left = insertIntoBST(root->left=nullptr, val=5).

3. Call insertIntoBST(root=nullptr, val=5):
   - root is null.
   - Create new TreeNode(5) and return it.

4. Back to call on node [7]:
   - root->left is set to the newly created node [5].
   - Return node [7].

5. Back to call on node [4]:
   - root->right remains [7] (which now has left child [5]).
   - Return node [4].

Final updated tree structure:
       4
      / \
     2   7
    / \  /
   1   3 5

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- Average Case: O(log N) - where N is the number of nodes. We traverse a single path from root to leaf.
- Worst Case: O(N) - occurs when the tree is skewed (like a single line) and we must insert at the end of the chain.

Space Complexity:
- Recursive Approach:
  * Average Case: O(log N) - call stack height for balanced tree.
  * Worst Case: O(N) - call stack height for skewed tree.
- Iterative Approach:
  * O(1) - auxiliary space since it only uses a few pointers.
*/

int main() {
    Solution sol;
    
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    
    TreeNode* result = sol.insertIntoBST(root, 5);
    
    // Check if 5 is inserted correctly as left child of 7
    if (result != nullptr && result->right != nullptr && result->right->left != nullptr && result->right->left->val == 5) {
        std::cout << "Test passed! Node with value 5 correctly inserted." << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }
    
    // Clean up memory
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right->left; // delete node 5
    delete root->right;
    delete root;
    
    return 0;
}
