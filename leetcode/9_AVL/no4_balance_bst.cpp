/**
 * @brief LeetCode 1382 - Balance a BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/balance-a-binary-search-tree/
 *
 * Problem:
 * Return balanced BST with same values.
 * 
 * Steps: inorder traversal -> sorted array -> build balanced BST.
 * 
 * Constraints: 1 <= nodes <= 10^4 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        // TODO: inorder -> sorted array -> build balanced BST
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        // Skewed: 1->2->3->4
        TreeNode* r=new TreeNode(1); r->right=new TreeNode(2);
        r->right->right=new TreeNode(3); r->right->right->right=new TreeNode(4);
        TreeNode* b=Solution().balanceBST(r);
        check(b!=nullptr,"result not null");
        // Height should be at most 3 for 4 nodes
        int lh=0,rh=0; TreeNode* t=b;
        while(t->left){lh++;t=t->left;}  t=b;
        while(t->right){rh++;t=t->right;}
        check(std::abs(lh-rh)<=1,"balanced result");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
