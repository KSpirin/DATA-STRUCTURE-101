/**
 * @file no4_balance_bst.cpp
 * @brief LeetCode 1382: Balance a Binary Search Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/balance-a-binary-search-tree/
 *
 * Problem Description:
 * Given the root of a binary search tree, return a balanced binary search tree with the same node values. 
 * If there is more than one answer, return any of them.
 *
 * A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.
 *
 * Example 1:
 * Input: root = [1,null,2,null,3,null,4,null,null]
 * Output: [2,1,3,null,null,null,4] or [3,1,4,null,2]
 *
 * Example 2:
 * Input: root = [2,1,3]
 * Output: [2,1,3]
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
    /**
     * @brief Performs an in-order traversal to extract the tree nodes in sorted order.
     * We collect the node pointers themselves so we can reuse them without extra dynamic allocations.
     * 
     * @param node The current subtree root.
     * @param sortedNodes Reference to a vector storing the collected TreeNode pointers.
     */
    void getInorderNodes(TreeNode* node, std::vector<TreeNode*>& sortedNodes) {
        if (!node) {
            return;
        }
        // Traverse left subtree
        getInorderNodes(node->left, sortedNodes);
        
        // Visit current node
        sortedNodes.push_back(node);
        
        // Traverse right subtree
        getInorderNodes(node->right, sortedNodes);
    }

    /**
     * @brief Recursively builds a balanced BST from a sorted vector of TreeNode pointers.
     * This uses a divide-and-conquer strategy similar to binary search.
     * 
     * @param sortedNodes The sorted list of TreeNode pointers.
     * @param start The starting index of the current partition.
     * @param end The ending index of the current partition.
     * @return TreeNode* The root of the balanced subtree.
     */
    TreeNode* buildBalancedBST(const std::vector<TreeNode*>& sortedNodes, int start, int end) {
        // Base case: If the range is invalid, return nullptr
        if (start > end) {
            return nullptr;
        }

        // Select the middle element to be the root of the current subtree
        int mid = start + (end - start) / 2;
        TreeNode* root = sortedNodes[mid];

        // Recursively build the left subtree using elements before the middle
        root->left = buildBalancedBST(sortedNodes, start, mid - 1);

        // Recursively build the right subtree using elements after the middle
        root->right = buildBalancedBST(sortedNodes, mid + 1, end);

        return root;
    }

public:
    /**
     * @brief Balances a given BST by flattening it into a sorted array and rebuilding it.
     * 
     * @param root The root of the unbalanced BST.
     * @return TreeNode* The root of the newly balanced BST.
     */
    TreeNode* balanceBST(TreeNode* root) {
        std::vector<TreeNode*> sortedNodes;
        // Step 1: Flatten the BST into a sorted list of node pointers
        getInorderNodes(root, sortedNodes);
        
        // Step 2: Build and return the balanced BST
        return buildBalancedBST(sortedNodes, 0, sortedNodes.size() - 1);
    }
};

/**
 * @brief Helper function to print tree levels (Breadth-First Search) for verification.
 * 
 * @param root The root of the tree to print.
 */
void printLevelOrder(TreeNode* root) {
    if (!root) {
        std::cout << "Empty\n";
        return;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr) {
                std::cout << curr->val << " ";
                q.push(curr->left);
                q.push(curr->right);
            } else {
                std::cout << "null ";
            }
        }
    }
    std::cout << "\n";
}

/*
 * =========================================================================
 * MANUAL DRY-RUN TRACE
 * =========================================================================
 * Input Tree (Example 1): [1, null, 2, null, 3, null, 4]
 * 
 *   1
 *    \
 *     2
 *      \
 *       3
 *        \
 *         4
 * 
 * Step 1: getInorderNodes(root, sortedNodes)
 *   - Visits 1 -> visits 2 -> visits 3 -> visits 4.
 *   - sortedNodes array has pointers to nodes with values: [1, 2, 3, 4].
 * 
 * Step 2: buildBalancedBST(sortedNodes, 0, 3)
 *   - start = 0, end = 3
 *   - mid = 0 + (3 - 0) / 2 = 1 (Node with value 2)
 *   - root = Node(2)
 * 
 *   - root->left = buildBalancedBST(sortedNodes, 0, 0)
 *     - start = 0, end = 0
 *     - mid = 0 + (0 - 0) / 2 = 0 (Node with value 1)
 *     - root = Node(1)
 *     - root->left = buildBalancedBST(sortedNodes, 0, -1) -> returns nullptr
 *     - root->right = buildBalancedBST(sortedNodes, 1, 0) -> returns nullptr
 *     - Returns Node(1)
 * 
 *   - root->right = buildBalancedBST(sortedNodes, 2, 3)
 *     - start = 2, end = 3
 *     - mid = 2 + (3 - 2) / 2 = 2 (Node with value 3)
 *     - root = Node(3)
 *     - root->left = buildBalancedBST(sortedNodes, 2, 1) -> returns nullptr
 *     - root->right = buildBalancedBST(sortedNodes, 3, 3)
 *       - start = 3, end = 3
 *       - mid = 3 (Node with value 4)
 *       - root = Node(4)
 *       - root->left = nullptr, root->right = nullptr
 *       - Returns Node(4)
 *     - Node(3)'s left = nullptr, right = Node(4). Returns Node(3).
 * 
 *   - Node(2)'s left = Node(1), right = Node(3). Returns Node(2).
 * 
 * Final Balanced Tree Structure:
 *       2
 *     /   \
 *    1     3
 *           \
 *            4
 * Heights of subtrees:
 *   - Node(2): Left height = 0, Right height = 1. Balance factor = 0 - 1 = -1 (Balanced)
 *   - Node(1): Left height = -1, Right height = -1. Balance factor = 0 (Balanced)
 *   - Node(3): Left height = -1, Right height = 0. Balance factor = -1 (Balanced)
 *   - Node(4): Left height = -1, Right height = -1. Balance factor = 0 (Balanced)
 * 
 * =========================================================================
 * TIME AND SPACE COMPLEXITY ANALYSIS
 * =========================================================================
 * - Time Complexity: O(N)
 *   - getInorderNodes visits every node in the BST exactly once, which takes O(N) time.
 *   - buildBalancedBST uses a divide-and-conquer method. Each node is processed as mid
 *     exactly once and has its left and right child pointers reassigned. This takes O(N) time.
 *   - Total Time Complexity: O(N).
 *
 * - Space Complexity: O(N)
 *   - An auxiliary vector of size N is used to store the node pointers.
 *   - The call stack for recursive in-order traversal takes O(H) space, where H is the height
 *     of the original tree (O(N) in the worst-case of a skewed tree, O(log N) in the best-case).
 *   - The call stack for buildBalancedBST takes O(log N) space since the tree is divided in half.
 *   - Total Space Complexity: O(N) auxiliary space.
 */

int main() {
    // Construct the unbalanced BST from Example 1:
    // 1
    //  \
    //   2
    //    \
    //     3
    //      \
    //       4
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);

    std::cout << "Original tree (level order): ";
    printLevelOrder(root);

    Solution solver;
    TreeNode* balancedRoot = solver.balanceBST(root);

    std::cout << "Balanced tree (level order): ";
    printLevelOrder(balancedRoot);

    // Clean up memory (using the balanced tree structure to delete nodes)
    // Note: Since all original nodes were reused, we delete them once.
    delete balancedRoot->left; // Deletes Node(1)
    delete balancedRoot->right->right; // Deletes Node(4)
    delete balancedRoot->right; // Deletes Node(3)
    delete balancedRoot; // Deletes Node(2)

    return 0;
}
