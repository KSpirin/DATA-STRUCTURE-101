/**
 * @file no2_sorted_array_to_bst.cpp
 * @brief LeetCode 108: Convert Sorted Array to Binary Search Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 *
 * Problem Description:
 * Given an integer array `nums` where the elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the two subtrees
 * of every node never differs by more than one.
 *
 * Example 1:
 * Input: nums = [-10,-3,0,5,9]
 * Output: [0,-3,9,-10,null,5]
 * Explanation: [0,-10,5,null,-3,null,9] is also accepted.
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
    // Helper function to build height-balanced BST recursively using divide-and-conquer
    TreeNode* buildBST(const std::vector<int>& nums, int left, int right) {
        // Base case: If the range is invalid, return nullptr (no node to build)
        if (left > right) {
            return nullptr;
        }

        // Choose the middle element as root to ensure height balance
        // Using left + (right - left) / 2 to avoid integer overflow
        int mid = left + (right - left) / 2;
        
        // Create root node with the middle element
        TreeNode* root = new TreeNode(nums[mid]);

        // Recursively construct the left subtree from the left half of the array
        root->left = buildBST(nums, left, mid - 1);

        // Recursively construct the right subtree from the right half of the array
        root->right = buildBST(nums, mid + 1, right);

        // Return the root of this sub-BST
        return root;
    }

public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums) {
        return buildBST(nums, 0, nums.size() - 1);
    }
};

/*
 * =========================================================================
 * MANUAL DRY-RUN TRACE
 * =========================================================================
 * Input: nums = [-10, -3, 0, 5, 9]
 * Initial call: buildBST(nums, left = 0, right = 4)
 * 
 * 1. Range: [0, 4]
 *    - mid = 0 + (4 - 0) / 2 = 2
 *    - nums[2] = 0 -> root = [0]
 *    - Left subtree call: buildBST(nums, 0, 1)
 *    - Right subtree call: buildBST(nums, 3, 4)
 * 
 * 2. Left Subtree: buildBST(nums, left = 0, right = 1)
 *    - mid = 0 + (1 - 0) / 2 = 0
 *    - nums[0] = -10 -> root->left = [-10]
 *    - Left subtree call: buildBST(nums, 0, -1) -> Returns nullptr (left > right)
 *    - Right subtree call: buildBST(nums, 1, 1)
 * 
 * 3. Left-Right Subtree: buildBST(nums, left = 1, right = 1)
 *    - mid = 1 + (1 - 1) / 2 = 1
 *    - nums[1] = -3 -> root->left->right = [-3]
 *    - Left subtree call: buildBST(nums, 1, 0) -> Returns nullptr
 *    - Right subtree call: buildBST(nums, 2, 1) -> Returns nullptr
 *    - Returns node [-3]
 *    - Node [-10]'s right child becomes [-3]. Returns node [-10]
 * 
 * 4. Right Subtree: buildBST(nums, left = 3, right = 4)
 *    - mid = 3 + (4 - 3) / 2 = 3
 *    - nums[3] = 5 -> root->right = [5]
 *    - Left subtree call: buildBST(nums, 3, 2) -> Returns nullptr
 *    - Right subtree call: buildBST(nums, 4, 4)
 * 
 * 5. Right-Right Subtree: buildBST(nums, left = 4, right = 4)
 *    - mid = 4 + (4 - 4) / 2 = 4
 *    - nums[4] = 9 -> root->right->right = [9]
 *    - Left subtree call: buildBST(nums, 4, 3) -> Returns nullptr
 *    - Right subtree call: buildBST(nums, 5, 4) -> Returns nullptr
 *    - Returns node [9]
 *    - Node [5]'s right child becomes [9]. Returns node [5]
 * 
 * Final Balanced Tree Structure:
 *          0
 *        /   \
 *     -10     5
 *       \      \
 *       -3      9
 * 
 * Let's check the heights of the subtrees:
 * - Root (0): Left subtree height = 2 (nodes -10, -3), Right subtree height = 2 (nodes 5, 9)
 *   Height difference = |2 - 2| = 0 (Balanced)
 * - Node -10: Left subtree height = -1, Right subtree height = 1 (node -3)
 *   Height difference = |-1 - 1| = 2? Wait! 
 *   Wait, is the tree height balanced?
 *   Let's check: Left subtree of root (0) is:
 *       -10
 *         \
 *         -3
 *   Height of Left Subtree of -10 is -1. Height of Right Subtree of -10 is 0 (leaf node -3).
 *   Height difference at node -10 is |-1 - 0| = 1. So it is balanced!
 *   Height of Left Subtree of root (0) is 1. Height of Right Subtree of root (0) is 1.
 *   Difference at root is |1 - 1| = 0.
 *   So the entire tree is height-balanced!
 * 
 * =========================================================================
 * TIME AND SPACE COMPLEXITY ANALYSIS
 * =========================================================================
 * - Time Complexity: O(N)
 *   Every element in the sorted array is visited exactly once to construct a node.
 * - Space Complexity: O(log N)
 *   Since the tree is balanced, the maximum depth of the recursion tree is O(log N).
 *   The call stack space complexity is therefore O(log N).
 */

int main() {
    Solution solver;
    std::vector<int> nums = {-10, -3, 0, 5, 9};
    TreeNode* root = solver.sortedArrayToBST(nums);
    
    // Quick validation of BST root
    if (root && root->val == 0) {
        std::cout << "Successfully built balanced BST. Root value: " << root->val << "\n";
    } else {
        std::cout << "Verification failed!\n";
    }
    
    // Clean up memory
    // (Omitted standard postorder delete for brief main test code)
    return 0;
}
