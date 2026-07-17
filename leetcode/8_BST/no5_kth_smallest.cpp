/**
 * @file no5_kth_smallest_bst.cpp
 * @brief LeetCode 230: Kth Smallest Element in a BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 *
 * @details
 * Problem Description:
 * Given the root of a binary search tree (BST), and an integer k, 
 * return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
 */

#include <iostream>
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
     * @brief Finds the kth smallest element in a BST iteratively using a stack.
     *        This approach allows early termination once the kth element is reached,
     *        making it highly efficient.
     * @param root The root of the BST.
     * @param k The 1-indexed target position.
     * @return int The kth smallest value.
     */
    int kthSmallest(TreeNode* root, int k) {
        std::stack<TreeNode*> s;
        TreeNode* curr = root;
        
        while (curr != nullptr || !s.empty()) {
            // Reach the left-most node of the current node
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            
            // Current must be nullptr at this point, pop from stack
            curr = s.top();
            s.pop();
            
            // Decrement k since we visited the node
            k--;
            if (k == 0) {
                return curr->val;
            }
            
            // We have visited the node and its left subtree. Now, it's the right subtree's turn.
            curr = curr->right;
        }
        
        return -1; // Should not be reached if k is valid
    }
};

/*
=========================================
      MANUAL DRY-RUN / TRACE
=========================================
Input Tree:
       3
      / \
     1   4
      \
       2
k = 1

Trace using kthSmallest(root = [3], k = 1):
1. Initialize: stack s = [], curr = [3]
2. Outer loop starts: (curr != nullptr || !s.empty()) is true.
3. Inner loop: push [3] to s, curr becomes [3]->left ([1]).
   Inner loop: push [1] to s, curr becomes [1]->left (nullptr).
   Inner loop ends. Stack s = [[3], [1]], curr = nullptr.
4. Pop from stack: curr = [1], s = [[3]].
5. Decrement k: k = 1 - 1 = 0.
6. Since k == 0, return curr->val (which is 1).
Final output: 1

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- O(H + K) - where H is the height of the BST, and K is the target rank.
  We must traverse down to the leftmost leaf (takes O(H) time), and then visit K nodes.
  In the worst case (skewed tree and K = N), this is O(N).
  In the best case (balanced tree and K = 1), this is O(log N).

Space Complexity:
- O(H) - where H is the height of the BST. This represents the maximum size of the stack.
  H is log N for a balanced tree, and N for a skewed tree.
*/

int main() {
    Solution sol;

    // Test case:
    //       3
    //      / \
    //     1   4
    //      \
    //       2
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);

    int k1 = 1;
    int ans1 = sol.kthSmallest(root, k1);
    if (ans1 == 1) {
        std::cout << "Test 1 Passed: 1st smallest is " << ans1 << std::endl;
    } else {
        std::cout << "Test 1 Failed! Got " << ans1 << std::endl;
    }

    int k2 = 3;
    int ans2 = sol.kthSmallest(root, k2);
    if (ans2 == 3) {
        std::cout << "Test 2 Passed: 3rd smallest is " << ans2 << std::endl;
    } else {
        std::cout << "Test 2 Failed! Got " << ans2 << std::endl;
    }

    // Clean up memory
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
