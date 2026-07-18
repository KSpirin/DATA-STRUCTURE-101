/**
 * @brief LeetCode 235 - LCA of BST
 * @difficulty Easy
 * @link https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 *
 * Problem:
 * LCA in BST: if both p,q < root -> go left; if both > root -> go right; else root is LCA.
 * 
 * Example: BST=[6,2,8], p=2, q=8 -> 6
 * 
 * Constraints: 2 <= nodes <= 10^5 */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // TODO (use BST property to navigate)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        TreeNode* r=new TreeNode(6);
        r->left=new TreeNode(2); r->right=new TreeNode(8);
        r->left->left=new TreeNode(0); r->left->right=new TreeNode(4);
        check(Solution().lowestCommonAncestor(r,r->left,r->right)->val==6,"LCA(2,8)==6");
        check(Solution().lowestCommonAncestor(r,r->left,r->left->right)->val==2,"LCA(2,4)==2");
    }
    {
        TreeNode* r2=new TreeNode(2);
        r2->left=new TreeNode(1);
        check(Solution().lowestCommonAncestor(r2,r2,r2->left)->val==2,"LCA includes self");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
