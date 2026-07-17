/**
 * @file no7_greater_tree.cpp
 * @brief LeetCode 538: Convert BST to Greater Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/convert-bst-to-greater-tree/
 *
 * @details
 * Problem Description:
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key
 * of the original BST is changed to the original key plus the sum of all keys greater than the
 * original key in BST.
 *
 * Recall that a Binary Search Tree is a tree that satisfies these constraints:
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^4].
 * - -10^4 <= Node.val <= 10^4
 * - All the values in the tree are unique.
 * - root is guaranteed to be a valid binary search tree.
 */

#include <iostream>
#include <vector>

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
    int sum = 0; // Running sum of all nodes visited so far in reverse inorder traversal

public:
    /**
     * @brief Converts the BST to a Greater Tree in-place.
     *        Performs a reverse inorder traversal (Right -> Root -> Left).
     *        Since nodes are visited in descending order, we can accumulate the sum of all
     *        greater nodes and update each node's value.
     * @param root The root node of the BST.
     * @return TreeNode* The root of the modified Greater Tree.
     */
    TreeNode* convertBST(TreeNode* root) {
        if (root != nullptr) {
            // 1. Visit the right subtree first (greater values)
            convertBST(root->right);
            
            // 2. Process current node: update sum and the node's value
            sum += root->val;
            root->val = sum;
            
            // 3. Visit the left subtree (smaller values)
            convertBST(root->left);
        }
        return root;
    }
};

/*
=========================================
      MANUAL DRY-RUN / TRACE
=========================================
Input Tree:
      2
     / \
    1   3

Running convertBST(root = [2]):
1. Initial: sum = 0
2. Outer call convertBST(node 2):
   - Calls convertBST(node 2 -> right which is node 3):
     - Calls convertBST(node 3 -> right which is nullptr):
       - returns (base case)
     - Process node 3:
       - sum += 3  => sum = 3
       - node 3 -> val = sum = 3
     - Calls convertBST(node 3 -> left which is nullptr):
       - returns (base case)
     - returns node 3
   - Process node 2:
     - sum += 2  => sum = 5
     - node 2 -> val = sum = 5
   - Calls convertBST(node 2 -> left which is node 1):
     - Calls convertBST(node 1 -> right which is nullptr):
       - returns (base case)
     - Process node 1:
       - sum += 1  => sum = 6
       - node 1 -> val = sum = 6
     - Calls convertBST(node 1 -> left which is nullptr):
       - returns (base case)
     - returns node 1
   - returns node 2

Final Modified Tree:
      5
     / \
    6   3

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- O(N) - where N is the number of nodes in the BST. We visit every node exactly once.

Space Complexity:
- O(H) - where H is the height of the BST. This is due to the recursion call stack.
  In the worst case (completely skewed tree), the recursion stack takes O(N) space.
  In the average case (balanced tree), the stack space is O(log N).
*/

// Helper function to print inorder traversal to verify structure
void printInorder(TreeNode* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    std::cout << node->val << " ";
    printInorder(node->right);
}

int main() {
    Solution sol;

    // Test case BST:
    //      2
    //     / \
    //    1   3
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    std::cout << "Original tree (inorder): ";
    printInorder(root);
    std::cout << "\n";

    // Convert BST
    TreeNode* result = sol.convertBST(root);

    std::cout << "Greater Tree (inorder): ";
    printInorder(result);
    std::cout << "\n";

    // Verify values: Inorder should be 6 5 3
    if (root->left->val == 6 && root->val == 5 && root->right->val == 3) {
        std::cout << "Test Passed: Tree successfully converted to Greater Tree!\n";
    } else {
        std::cout << "Test Failed! Values do not match expected.\n";
    }

    // Clean up memory
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
