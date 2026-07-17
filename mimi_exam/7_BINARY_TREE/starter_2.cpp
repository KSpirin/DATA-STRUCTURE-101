#include <iostream>
#include <cassert>

// PROBLEM: LeetCode 236 - Lowest Common Ancestor
// Find the deepest node that is an ancestor of BOTH p and q.

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // TODO:
        // - Base case: if (!root || root == p || root == q) return root
        // - left = LCA(root->left, p, q)
        // - right = LCA(root->right, p, q)
        // - if both left and right are non-null -> return root (root is LCA)
        // - return left ? left : right

        return nullptr;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    assert(Solution().lowestCommonAncestor(root, root->left, root->right) == root);
    std::cout << "7_BINARY_TREE Coding 2 Passed!" << std::endl;
    return 0;
}
