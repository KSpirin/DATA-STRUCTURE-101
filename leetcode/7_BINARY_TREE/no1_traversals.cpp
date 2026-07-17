/**
 * @file no1_traversals.cpp
 * @brief LeetCode 144 (Preorder), 94 (Inorder), and 145 (Postorder) Traversals
 * 
 * Difficulty: Easy
 * LeetCode Links:
 * - Preorder:  https://leetcode.com/problems/binary-tree-preorder-traversal/
 * - Inorder:   https://leetcode.com/problems/binary-tree-inorder-traversal/
 * - Postorder: https://leetcode.com/problems/binary-tree-postorder-traversal/
 * 
 * Problem Descriptions:
 * Given the root of a binary tree, return the preorder, inorder, and postorder 
 * traversals of its nodes' values.
 */

#include <vector>
#include <stack>
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

// ==========================================
// 1. PREORDER TRAVERSAL (LeetCode 144)
// Visit Order: Root -> Left -> Right
// ==========================================
class PreorderTraversal {
public:
    // Recursive Approach
    // Time Complexity: O(N) - visits each node once
    // Space Complexity: O(H) - recursion stack depth (H = tree height)
    void preorderRecursiveHelper(TreeNode* root, std::vector<int>& result) {
        if (root == nullptr) return;
        result.push_back(root->val);                  // Visit root
        preorderRecursiveHelper(root->left, result);   // Traverse left subtree
        preorderRecursiveHelper(root->right, result);  // Traverse right subtree
    }

    std::vector<int> preorderTraversalRecursive(TreeNode* root) {
        std::vector<int> result;
        preorderRecursiveHelper(root, result);
        return result;
    }

    // Iterative Approach (Using Stack)
    // Time Complexity: O(N)
    // Space Complexity: O(H) - where H is the height of the tree (maximum nodes in stack)
    std::vector<int> preorderTraversalIterative(TreeNode* root) {
        std::vector<int> result;
        if (root == nullptr) return result;

        std::stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* curr = s.top();
            s.pop();
            result.push_back(curr->val); // Visit node

            // Push right child first, so left child is processed first (LIFO)
            if (curr->right != nullptr) {
                s.push(curr->right);
            }
            if (curr->left != nullptr) {
                s.push(curr->left);
            }
        }
        return result;
    }
};

// ==========================================
// 2. INORDER TRAVERSAL (LeetCode 94)
// Visit Order: Left -> Root -> Right
// ==========================================
class InorderTraversal {
public:
    // Recursive Approach
    // Time Complexity: O(N)
    // Space Complexity: O(H)
    void inorderRecursiveHelper(TreeNode* root, std::vector<int>& result) {
        if (root == nullptr) return;
        inorderRecursiveHelper(root->left, result);  // Traverse left subtree
        result.push_back(root->val);                 // Visit root
        inorderRecursiveHelper(root->right, result); // Traverse right subtree
    }

    std::vector<int> inorderTraversalRecursive(TreeNode* root) {
        std::vector<int> result;
        inorderRecursiveHelper(root, result);
        return result;
    }

    // Iterative Approach (Using Stack)
    // Time Complexity: O(N)
    // Space Complexity: O(H)
    std::vector<int> inorderTraversalIterative(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> s;
        TreeNode* curr = root;

        while (curr != nullptr || !s.empty()) {
            // Keep traversing left until we hit nullptr
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left; // Move to left child
            }

            // Node to visit is at the top of the stack
            curr = s.top();
            s.pop();
            result.push_back(curr->val); // Visit root

            // Move to the right child
            curr = curr->right;
        }
        return result;
    }
};

// ==========================================
// 3. POSTORDER TRAVERSAL (LeetCode 145)
// Visit Order: Left -> Right -> Root
// ==========================================
class PostorderTraversal {
public:
    // Recursive Approach
    // Time Complexity: O(N)
    // Space Complexity: O(H)
    void postorderRecursiveHelper(TreeNode* root, std::vector<int>& result) {
        if (root == nullptr) return;
        postorderRecursiveHelper(root->left, result);   // Traverse left subtree
        postorderRecursiveHelper(root->right, result);  // Traverse right subtree
        result.push_back(root->val);                   // Visit root
    }

    std::vector<int> postorderTraversalRecursive(TreeNode* root) {
        std::vector<int> result;
        postorderRecursiveHelper(root, result);
        return result;
    }

    // Iterative Approach (Using Two Stacks)
    // Time Complexity: O(N)
    // Space Complexity: O(N) - to hold elements in the second stack
    std::vector<int> postorderTraversalIterativeTwoStacks(TreeNode* root) {
        std::vector<int> result;
        if (root == nullptr) return result;

        std::stack<TreeNode*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            TreeNode* curr = s1.top();
            s1.pop();
            s2.push(curr); // This stack reverse the order to postorder (Left, Right, Root)

            // Push left first, then right so they are processed in correct order
            if (curr->left != nullptr) {
                s1.push(curr->left);
            }
            if (curr->right != nullptr) {
                s1.push(curr->right);
            }
        }

        // Transfer everything from s2 to result
        while (!s2.empty()) {
            result.push_back(s2.top()->val);
            s2.pop();
        }
        return result;
    }
};

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 * 
 * Expected Traversals:
 * 1. Preorder (Root-Left-Right):  [1, 2, 4, 5, 3]
 * 2. Inorder (Left-Root-Right):   [4, 2, 5, 1, 3]
 * 3. Postorder (Left-Right-Root):  [4, 5, 2, 3, 1]
 * 
 * -------------------------------------------------------------------------
 * Preorder Iterative Dry Run (using Stack s):
 * Step 1: s = [1]
 * Step 2: pop 1, result = [1]. Push right child (3), then left child (2). s = [3, 2]
 * Step 3: pop 2, result = [1, 2]. Push right (5), then left (4). s = [3, 5, 4]
 * Step 4: pop 4, result = [1, 2, 4]. No children. s = [3, 5]
 * Step 5: pop 5, result = [1, 2, 4, 5]. No children. s = [3]
 * Step 6: pop 3, result = [1, 2, 4, 5, 3]. No children. s = []
 * End loop. Return [1, 2, 4, 5, 3]. Correct.
 * 
 * -------------------------------------------------------------------------
 * Inorder Iterative Dry Run (using Stack s, Pointer curr):
 * Step 1: curr = 1. Inner loop pushes 1, then curr = 2. Inner loop pushes 2, then curr = 4.
 *         Inner loop pushes 4, then curr = nullptr. s = [1, 2, 4]
 * Step 2: pop 4, result = [4], curr = curr->right = nullptr (from node 4)
 * Step 3: pop 2, result = [4, 2], curr = curr->right = 5.
 * Step 4: curr = 5. Inner loop pushes 5, then curr = nullptr. s = [1, 5]
 * Step 5: pop 5, result = [4, 2, 5], curr = curr->right = nullptr (from node 5)
 * Step 6: pop 1, result = [4, 2, 5, 1], curr = curr->right = 3.
 * Step 7: curr = 3. Inner loop pushes 3, then curr = nullptr. s = [3]
 * Step 8: pop 3, result = [4, 2, 5, 1, 3], curr = curr->right = nullptr.
 * Loop terminates (curr == nullptr && s is empty). Return [4, 2, 5, 1, 3]. Correct.
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Preorder DFS:
 *   - Time: O(N), every node is visited exactly once.
 *   - Space: O(H) recursive stack frames / stack elements, where H is the tree height.
 * Inorder DFS:
 *   - Time: O(N), every node is visited exactly once.
 *   - Space: O(H) recursive stack frames / stack elements.
 * Postorder DFS:
 *   - Time: O(N), every node is visited exactly once.
 *   - Space: O(H) for recursive, O(N) for iterative using two stacks.
 * =========================================================================
 */
