#include <iostream>
#include <algorithm>
#include <cassert>

// PROBLEM: LeetCode 110 - Balanced Binary Tree
// A tree is balanced if for EVERY node: |height(left) - height(right)| <= 1

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int checkHeight(TreeNode* root) {
        // TODO:
        // - If null: return 0
        // - lh = checkHeight(root->left),  if lh == -1 return -1
        // - rh = checkHeight(root->right), if rh == -1 return -1
        // - If abs(lh - rh) > 1: return -1  (imbalanced!)
        // - Else return max(lh, rh) + 1

        return 0;
    }

public:
    bool isBalanced(TreeNode* root) {
        // TODO: return checkHeight(root) != -1
        return false;
    }
};

int main() {
    //   1
    //  /
    // 2
    // /
    // 3   <- height diff at root = 2 -> NOT balanced
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->left->left = new TreeNode(3);
    assert(Solution().isBalanced(r) == false);
    std::cout << "9_AVL Coding 3 Passed!" << std::endl;
    return 0;
}
