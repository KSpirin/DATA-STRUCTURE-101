/**
 * @file no3_delete_bst.cpp
 * @brief LeetCode 450: Delete Node in a BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/delete-node-in-a-bst/
 *
 * @details
 * Problem Description:
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST.
 * Return the root node reference (possibly updated) of the BST.
 *
 * Basically, the deletion can be divided into two stages:
 * 1. Search for a node to remove.
 * 2. If the node is found, delete the node.
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
private:
    /**
     * @brief Helper function to find the minimum value node in a subtree.
     *        This is used to find the Inorder Successor (smallest node in right subtree).
     */
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    /**
     * @brief Helper function to find the maximum value node in a subtree.
     *        This is used to find the Inorder Predecessor (largest node in left subtree).
     */
    TreeNode* findMax(TreeNode* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

public:
    /**
     * @brief Deletes a node with the key from the BST recursively using the INORDER SUCCESSOR strategy.
     * @param root The root of the BST.
     * @param key The key to delete.
     * @return TreeNode* The root of the updated BST.
     */
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        
        // --- STAGE 1: Search for the node ---
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // --- STAGE 2: Node found, delete it ---
            
            // Case 1: Leaf Node (No child)
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            
            // Case 2: One child
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp; // Connect parent to child
            } else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp; // Connect parent to child
            }
            
            // Case 3: Two children
            // Choice A: Replace with Inorder Successor (minimum in right subtree)
            TreeNode* successor = findMin(root->right);
            root->val = successor->val; // Copy successor's value to current node
            root->right = deleteNode(root->right, successor->val); // Recursively delete successor
        }
        return root;
    }

    /**
     * @brief Alternative solution: Deletes a node using the INORDER PREDECESSOR strategy.
     * @param root The root of the BST.
     * @param key The key to delete.
     * @return TreeNode* The root of the updated BST.
     */
    TreeNode* deleteNodePredecessor(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        
        if (key < root->val) {
            root->left = deleteNodePredecessor(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNodePredecessor(root->right, key);
        } else {
            // Found node
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            
            // Choice B: Replace with Inorder Predecessor (maximum in left subtree)
            TreeNode* predecessor = findMax(root->left);
            root->val = predecessor->val; // Copy predecessor's value to current node
            root->left = deleteNodePredecessor(root->left, predecessor->val); // Recursively delete predecessor
        }
        return root;
    }
};

/*
=========================================
      MANUAL DRY-RUN / TRACE
=========================================
Input Tree:
       5
      / \
     3   6
    / \   \
   2   4   7
Target key = 3

Trace using deleteNode(root = [5], key = 3) (Successor Strategy):
1. Call deleteNode(root=[5], key=3):
   - key (3) < root->val (5) -> Left branch.
   - Set root->left = deleteNode(root->left=[3], key=3).

2. Call deleteNode(root=[3], key=3):
   - root->val == key (3) -> Node found!
   - Node has two children: root->left=[2] and root->right=[4].
   - Find Inorder Successor in right subtree [4]:
     * findMin(root->right=[4]) -> returns [4] (minimum node in right subtree).
   - Copy successor value: root->val = 4. (Node [3] becomes node [4]).
   - Recursively delete the successor node:
     * root->right = deleteNode(root->right=[4], key=4).

3. Call deleteNode(root=[4], key=4):
   - root->val == key (4) -> Node found!
   - Node is a Leaf Node (no children).
   - Delete root([4]) and return nullptr.

4. Back to call on node [4] (which replaced [3]):
   - root->right = nullptr.
   - Return node [4].

5. Back to call on root [5]:
   - root->left is set to [4].
   - Return node [5].

Final updated tree structure:
       5
      / \
     4   6
    /     \
   2       7

=========================================
      COMPLEXITY ANALYSIS
=========================================
Time Complexity:
- Average Case: O(log N) - since finding the node and finding the successor/predecessor takes O(h) steps, where h is the height of the tree.
- Worst Case: O(N) - occurs in skewed BSTs where height h = N.

Space Complexity:
- O(h) auxiliary space due to recursive stack calls.
  * Average Case: O(log N)
  * Worst Case: O(N)
*/

int main() {
    Solution sol;
    
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);
    
    TreeNode* result = sol.deleteNode(root, 3);
    
    // Inorder traversal check (should be sorted: 2 4 5 6 7)
    // Root should still be 5, left child should be 4 with left child 2.
    if (result != nullptr && result->left != nullptr && result->left->val == 4 && result->left->left->val == 2) {
        std::cout << "Test passed! Node with value 3 successfully deleted and replaced by 4." << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }
    
    // Clean up memory
    delete root->left->left; // node 2
    delete root->left;       // node 4
    delete root->right->right;// node 7
    delete root->right;      // node 6
    delete root;             // node 5
    
    return 0;
}
