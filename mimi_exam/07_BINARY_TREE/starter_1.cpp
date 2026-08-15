#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

// PROBLEM: LeetCode 106 - Build Tree from Inorder + Postorder
// Postorder: [left | right | ROOT] -> last element is always the root
// Inorder:   [left | ROOT | right] -> split by root position

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    // TODO 1: Implement recursive helper
    // - p_idx starts at postorder.size()-1 (the root)
    // - For each call: read root = post[p_idx--]
    // - Find root in inorder using map
    // - Recurse RIGHT first (postorder traversal order), then LEFT
    TreeNode* helper(int is, int ie, const std::vector<int>& post,
                     int& p_idx, std::unordered_map<int,int>& map) {

    }

public:
    TreeNode* buildTree(const std::vector<int>& inorder, const std::vector<int>& postorder) {
        // TODO 2: Build map of inorder value -> index
        // TODO 3: Call helper(0, inorder.size()-1, ...)
        return nullptr;
    }
};

int main() {
    // inorder=[9,3,15], postorder=[9,15,3] -> root is 3, left=9, right=15
    TreeNode* root = Solution().buildTree({9, 3, 15}, {9, 15, 3});
    assert(root->val == 3 && root->left->val == 9 && root->right->val == 15);
    std::cout << "7_BINARY_TREE Coding 1 Passed!" << std::endl;
    return 0;
}
