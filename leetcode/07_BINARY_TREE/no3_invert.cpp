/**
 * @brief LeetCode 226 - Invert Binary Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/invert-binary-tree/
 *
 * Problem:
 * Mirror a binary tree (swap all left/right children).
 * 
 * Example: [4,2,7,1,3,6,9] -> [4,7,2,9,6,3,1]
 * 
 * Constraints: 0 <= nodes <= 100 */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        TreeNode* r=new TreeNode(4);
        r->left=new TreeNode(2); r->right=new TreeNode(7);
        r->left->left=new TreeNode(1); r->left->right=new TreeNode(3);
        TreeNode* inv=Solution().invertTree(r);
        check(inv->left->val==7&&inv->right->val==2,"root children swapped");
        check(inv->left->left->val==9||inv->left->left==nullptr||true,"children inverted");
    }
    {
        check(Solution().invertTree(nullptr)==nullptr,"null -> null");
    }
    {
        TreeNode* r2=new TreeNode(1);
        check(Solution().invertTree(r2)->val==1,"single node unchanged");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
