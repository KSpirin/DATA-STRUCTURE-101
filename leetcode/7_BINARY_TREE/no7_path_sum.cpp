/**
 * @brief LeetCode 112 - Path Sum
 * @difficulty Easy
 * @link https://leetcode.com/problems/path-sum/
 *
 * Problem:
 * Return true if any root-to-leaf path sums to targetSum.
 * 
 * Example: tree=[5,4,8...], targetSum=22 -> true
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
    bool hasPathSum(TreeNode* root, int targetSum) {
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
        TreeNode* r=new TreeNode(5);
        r->left=new TreeNode(4); r->right=new TreeNode(8);
        r->left->left=new TreeNode(11);
        r->left->left->left=new TreeNode(7); r->left->left->right=new TreeNode(2);
        check(Solution().hasPathSum(r,22)==true,"sum=22 -> true");
        check(Solution().hasPathSum(r,99)==false,"sum=99 -> false");
    }
    {
        check(Solution().hasPathSum(nullptr,0)==false,"null -> false");
    }
    {
        TreeNode* r2=new TreeNode(1);
        r2->left=new TreeNode(2);
        check(Solution().hasPathSum(r2,1)==false,"1->2 sum=1 -> false (not leaf)");
        check(Solution().hasPathSum(r2,3)==true, "1->2 sum=3 -> true");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
