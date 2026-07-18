/**
 * @brief LeetCode 98 - Validate BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/validate-binary-search-tree/
 *
 * Problem:
 * Check if every node satisfies BST property (all left < node < all right).
 * 
 * Example: [2,1,3] -> true, [5,1,4,null,null,3,6] -> false
 * 
 * Constraints: 1 <= nodes <= 10^4 */

#include <iostream>
#include <climits>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // TODO (pass min/max bounds down recursion)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        TreeNode* r1=new TreeNode(2);
        r1->left=new TreeNode(1); r1->right=new TreeNode(3);
        check(Solution().isValidBST(r1)==true,"[2,1,3] valid");
    }
    {
        TreeNode* r2=new TreeNode(5);
        r2->left=new TreeNode(1); r2->right=new TreeNode(4);
        r2->right->left=new TreeNode(3); r2->right->right=new TreeNode(6);
        check(Solution().isValidBST(r2)==false,"[5,1,4,3,6] invalid");
    }
    {
        check(Solution().isValidBST(nullptr)==true,"null -> valid");
    }
    {
        TreeNode* r3=new TreeNode(1);
        check(Solution().isValidBST(r3)==true,"single node valid");
    }
    {
        TreeNode* r4=new TreeNode(10);
        r4->left=new TreeNode(5); r4->left->right=new TreeNode(15);
        check(Solution().isValidBST(r4)==false,"5->15 violates BST (15>10)");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
