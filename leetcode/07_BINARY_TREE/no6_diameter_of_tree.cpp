/**
 * @brief LeetCode 543 - Diameter of Binary Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/diameter-of-binary-tree/
 *
 * Problem:
 * Longest path between any two nodes (doesn't need to pass through root).
 * 
 * Example: [1,2,3,4,5] -> 3
 * 
 * Constraints: 1 <= nodes <= 10^4 */

#include <iostream>
#include <algorithm>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
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
        TreeNode* r=new TreeNode(1);
        r->left=new TreeNode(2); r->right=new TreeNode(3);
        r->left->left=new TreeNode(4); r->left->right=new TreeNode(5);
        check(Solution().diameterOfBinaryTree(r)==3,"standard tree -> 3");
    }
    {
        TreeNode* r2=new TreeNode(1);
        r2->left=new TreeNode(2);
        check(Solution().diameterOfBinaryTree(r2)==1,"two nodes -> 1");
    }
    {
        TreeNode* r3=new TreeNode(1);
        check(Solution().diameterOfBinaryTree(r3)==0,"single node -> 0");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
