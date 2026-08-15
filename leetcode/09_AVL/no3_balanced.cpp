/**
 * @brief LeetCode 110 - Balanced Binary Tree
 * @difficulty Easy
 * @link https://leetcode.com/problems/balanced-binary-tree/
 *
 * Problem:
 * True if for every node |height(left) - height(right)| <= 1.
 * 
 * Example: [3,9,20,null,null,15,7] -> true
 * 
 * Constraints: 0 <= nodes <= 5000 */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        // TODO (bottom-up height check, return -1 as sentinel for imbalance)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        TreeNode* r1=new TreeNode(3);
        r1->left=new TreeNode(9); r1->right=new TreeNode(20);
        r1->right->left=new TreeNode(15); r1->right->right=new TreeNode(7);
        check(Solution().isBalanced(r1)==true,"standard balanced -> true");
    }
    {
        TreeNode* r2=new TreeNode(1);
        r2->left=new TreeNode(2); r2->left->left=new TreeNode(3);
        check(Solution().isBalanced(r2)==false,"left-skewed -> false");
    }
    {
        check(Solution().isBalanced(nullptr)==true,"null -> true");
    }
    {
        TreeNode* r3=new TreeNode(1);
        check(Solution().isBalanced(r3)==true,"single node -> true");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
