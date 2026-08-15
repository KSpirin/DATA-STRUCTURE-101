#include <iostream>
#include <cassert>

// PROBLEM: LeetCode 98 - Validate BST
// Every node must satisfy: minBound < node->val < maxBound
// Pass the bounds down the recursion tree.

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    bool validate(TreeNode* r, TreeNode* minNode, TreeNode* maxNode) {
        // TODO:
        // - If r is null: return true
        // - If minNode && r->val <= minNode->val: return false
        // - If maxNode && r->val >= maxNode->val: return false
        // - Recurse: validate(left, minNode, r) && validate(right, r, maxNode)
        return false;
    }

public:
    bool isValidBST(TreeNode* root) {
        // TODO: Call validate(root, nullptr, nullptr)
        return false;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(7);
    assert(Solution().isValidBST(root) == true);
    root->left->right = new TreeNode(10); // 10 > 5, violates BST!
    assert(Solution().isValidBST(root) == false);
    std::cout << "8_BST Coding 2 Passed!" << std::endl;
    return 0;
}
