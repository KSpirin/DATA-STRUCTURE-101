#include <iostream>
#include <cassert>

// PROBLEM: LeetCode 450 - Delete Node in BST
// Three cases for deletion:
//   Case 1: Node has NO children -> just remove it
//   Case 2: Node has ONE child -> replace with that child
//   Case 3: Node has TWO children -> replace value with INORDER SUCCESSOR
//           (smallest node in RIGHT subtree), then delete the successor

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        // TODO:
        // - If root is null: return null
        // - If key < root->val: recurse left
        // - If key > root->val: recurse right
        // - Else (found it!):
        //   Case 1 & 2: if no left child, return right child (and vice versa)
        //   Case 3: find min in right subtree, copy its val here, delete it from right

        return root;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root = Solution().deleteNode(root, 3);
    assert(root->left == nullptr);
    std::cout << "8_BST Coding 1 Passed!" << std::endl;
    return 0;
}
