/**
 * @brief LeetCode 236 - LCA of Binary Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * Problem:
 * Find deepest common ancestor of nodes p and q.
 * 
 * Example: tree=[3,5,1], p=5, q=1 -> 3
 * 
 * Constraints: 2 <= nodes <= 10^5, all values unique */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
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
        TreeNode* r=new TreeNode(3);
        r->left=new TreeNode(5); r->right=new TreeNode(1);
        r->left->left=new TreeNode(6); r->left->right=new TreeNode(2);
        r->right->left=new TreeNode(0); r->right->right=new TreeNode(8);
        check(Solution().lowestCommonAncestor(r,r->left,r->right)==r,"LCA(5,1)==3");
        check(Solution().lowestCommonAncestor(r,r->left,r->left->right)==r->left,"LCA(5,2)==5");
    }
    {
        TreeNode* r2=new TreeNode(1);
        r2->left=new TreeNode(2);
        check(Solution().lowestCommonAncestor(r2,r2,r2->left)==r2,"LCA includes ancestor itself");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
