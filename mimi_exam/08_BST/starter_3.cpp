#include <iostream>
#include <vector>
#include <cassert>

// PROBLEM: LeetCode 108 - Sorted Array to Height-Balanced BST
// Always pick the MIDDLE element as root (ensures balance).
// Recurse on left half -> left subtree, right half -> right subtree.

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* helper(const std::vector<int>& nums, int l, int r) {
        // TODO:
        // - Base case: if l > r return nullptr
        // - mid = l + (r - l) / 2
        // - Create node with nums[mid]
        // - node->left = helper(nums, l, mid-1)
        // - node->right = helper(nums, mid+1, r)
        // - Return node
        return nullptr;
    }

public:
    TreeNode* sortedArrayToBST(const std::vector<int>& nums) {
        // TODO: Call helper(nums, 0, nums.size()-1)
        return nullptr;
    }
};

int main() {
    std::vector<int> nums = {-10, 0, 5};
    // Middle = 0, so root should be 0
    TreeNode* r = Solution().sortedArrayToBST(nums);
    assert(r->val == 0);
    std::cout << "8_BST Coding 3 Passed!" << std::endl;
    return 0;
}
