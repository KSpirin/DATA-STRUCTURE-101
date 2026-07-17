/**
 * @file no4_validate_bst.cpp
 * @brief LeetCode 98: Validate Binary Search Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/validate-binary-search-tree/
 *
 * @details
 * Problem Description:
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * 
 * A valid BST is defined as follows:
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 */

#include <iostream>
#include <climits>
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

class Solution {
public:
    /**
     * @brief Validates if a binary tree is a BST using recursive range validation.
     *        This approach ensures every node's value falls within a dynamically updated
     *        [low, high] pointer boundary, avoiding integer overflow.
     * @param root The root node of the binary tree.
     * @return true if the tree is a valid BST, false otherwise.
     */
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }

private:
    bool validate(TreeNode* node, TreeNode* low, TreeNode* high) {
        // Base Case: An empty tree is a valid BST
        if (node == nullptr) {
            return true;
        }

        // The current node's value must be strictly greater than low (if it exists)
        if (low != nullptr && node->val <= low->val) {
            return false;
        }

        // The current node's value must be strictly less than high (if it exists)
        if (high != nullptr && node->val >= high->val) {
            return false;
        }

        // Recursively validate:
        // - Left subtree: high boundary becomes the current node
        // - Right subtree: low boundary becomes the current node
        return validate(node->left, low, node) && 
               validate(node->right, node, high);
    }
};

/*
=========================================
      MANUAL DRY-RUN / TRACE
=========================================
Example 1: Invalid BST
       5
      / \
     1   4
        / \
       3   6

Trace using isValidBST(root = [5]):
1. Call validate(node=[5], low=nullptr, high=nullptr):
   - node is not null. low/high are null (no bounds checking yet).
   - Recursively call:
     a) validate(node->left=[1], low=nullptr, high=[5])
     b) validate(node->right=[4], low=[5], high=nullptr)

2. Process left child: validate(node=[1], low=nullptr, high=[5]):
   - node is not null. low is null. high=[5], node->val (1) < high->val (5) is true.
   - Recursively call:
     - validate(node->left=nullptr, low=nullptr, high=[1]) -> returns true (base case)
     - validate(node->right=nullptr, low=[1], high=[5]) -> returns true (base case)
   - Left child returns true.

3. Process right child: validate(node=[4], low=[5], high=nullptr):
   - node is not null. low=[5], high is null.
   - Check condition: low != nullptr && node->val <= low->val.
     - 4 <= 5 is true!
   - This violates the BST property because the right child of node 5 contains a node with value 4 (which is not > 5).
   - Returns false.

4. Call stack returns: true && false -> false.
Final output: false (Invalid BST)

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- O(N) - where N is the number of nodes in the binary tree. We visit each node exactly once.

Space Complexity:
- Average Case: O(log N) - call stack height for a balanced tree of size N.
- Worst Case: O(N) - call stack height for a skewed tree (e.g., a linked list).
*/

int main() {
    Solution sol;

    // Test case 1: Valid BST
    //      2
    //     / \
    //    1   3
    TreeNode* validRoot = new TreeNode(2);
    validRoot->left = new TreeNode(1);
    validRoot->right = new TreeNode(3);

    if (sol.isValidBST(validRoot)) {
        std::cout << "Test 1 Passed: Tree is a valid BST." << std::endl;
    } else {
        std::cout << "Test 1 Failed!" << std::endl;
    }

    // Test case 2: Invalid BST
    //      5
    //     / \
    //    1   4
    //       / \
    //      3   6
    TreeNode* invalidRoot = new TreeNode(5);
    invalidRoot->left = new TreeNode(1);
    invalidRoot->right = new TreeNode(4);
    invalidRoot->right->left = new TreeNode(3);
    invalidRoot->right->right = new TreeNode(6);

    if (!sol.isValidBST(invalidRoot)) {
        std::cout << "Test 2 Passed: Correctly identified invalid BST." << std::endl;
    } else {
        std::cout << "Test 2 Failed!" << std::endl;
    }

    // Clean up memory
    delete validRoot->left;
    delete validRoot->right;
    delete validRoot;

    delete invalidRoot->right->left;
    delete invalidRoot->right->right;
    delete invalidRoot->right;
    delete invalidRoot->left;
    delete invalidRoot;

    return 0;
}
