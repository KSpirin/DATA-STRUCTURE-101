/**
 * @brief LeetCode 230 - Kth Smallest in BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 *
 * Problem:
 * Return the kth smallest value in BST.
 * 
 * Example: BST=[3,1,4,null,2], k=1 -> 1
 * 
 * Constraints: 1 <= k <= nodes <= 10^4 */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        // TODO (inorder = sorted order)
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
        r->left=new TreeNode(1); r->right=new TreeNode(4);
        r->left->right=new TreeNode(2);
        check(Solution().kthSmallest(r,1)==1,"k=1 -> 1");
        check(Solution().kthSmallest(r,2)==2,"k=2 -> 2");
        check(Solution().kthSmallest(r,3)==3,"k=3 -> 3");
        check(Solution().kthSmallest(r,4)==4,"k=4 -> 4");
    }
    {
        TreeNode* r2=new TreeNode(5);
        r2->left=new TreeNode(3); r2->right=new TreeNode(6);
        r2->left->left=new TreeNode(2); r2->left->right=new TreeNode(4);
        r2->left->left->left=new TreeNode(1);
        check(Solution().kthSmallest(r2,3)==3,"k=3 in bigger tree");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
