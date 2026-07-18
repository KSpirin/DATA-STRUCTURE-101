/**
 * @brief LeetCode 450 - Delete Node in a BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/delete-node-in-a-bst/
 *
 * Problem:
 * Delete node with given key. Three cases:
 * 1. No children -> remove
 * 2. One child -> replace
 * 3. Two children -> replace with inorder successor
 * 
 * Constraints: 0 <= nodes <= 10^4 */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        // TODO (3 cases: no child, one child, two children)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        TreeNode* r=new TreeNode(5);
        r->left=new TreeNode(3); r->right=new TreeNode(6);
        r->left->left=new TreeNode(2); r->left->right=new TreeNode(4);
        TreeNode* res=Solution().deleteNode(r,3);
        check(res->left==nullptr||res->left->val!=3,"node 3 deleted");
    }
    {
        TreeNode* r2=new TreeNode(5);
        r2->left=new TreeNode(3); r2->right=new TreeNode(6);
        TreeNode* res=Solution().deleteNode(r2,0);
        check(res->val==5,"delete non-existent -> unchanged");
    }
    {
        TreeNode* r3=new TreeNode(1);
        TreeNode* res=Solution().deleteNode(r3,1);
        check(res==nullptr,"delete only node -> null");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
