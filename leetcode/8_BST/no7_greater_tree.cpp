/**
 * @brief LeetCode 538 - Convert BST to Greater Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/convert-bst-to-greater-tree/
 *
 * Problem:
 * Replace each node's value with sum of all values >= it.
 * 
 * Example: BST=[4,1,6,0,2,5,7] -> [22,12,26,11,13,21,26]
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
    TreeNode* convertBST(TreeNode* root) {
        // TODO (reverse inorder: right -> root -> left)
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
        r->left=new TreeNode(1); r->right=new TreeNode(6);
        r->right->left=new TreeNode(5); r->right->right=new TreeNode(7);
        Solution().convertBST(r);
        // 4 -> 4+5+6+7=22; 6 -> 6+7=13; etc.
        check(r->val==22,"root 4 becomes 22 (4+5+6+7)");
        check(r->right->val==13,"node 6 becomes 13 (6+7)");
        check(r->right->right->val==7,"node 7 stays 7 (largest)");
    }
    {
        TreeNode* r2=new TreeNode(0);
        r2->right=new TreeNode(1);
        Solution().convertBST(r2);
        check(r2->val==1,"0 becomes 0+1=1");
        check(r2->right->val==1,"1 stays 1");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
