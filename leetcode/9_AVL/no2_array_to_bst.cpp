/**
 * @brief LeetCode 108 - Sorted Array to Height-Balanced BST
 * @difficulty Easy
 * @link https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 *
 * Problem:
 * Build height-balanced BST from sorted array.
 * 
 * Example: [-10,-3,0,5,9] -> [0,-3,9,-10,null,5]
 * 
 * Constraints: 1 <= nums.length <= 10^4 */

#include <iostream>
#include <vector>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums) {
        // TODO: always pick mid as root
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        std::vector<int> n1={-10,-3,0,5,9};
        TreeNode* r=Solution().sortedArrayToBST(n1);
        check(r->val==0,"mid element is root");
        check(r->left!=nullptr&&r->right!=nullptr,"has both children");
    }
    {
        std::vector<int> n2={1,3};
        TreeNode* r=Solution().sortedArrayToBST(n2);
        check(r!=nullptr,"non-null result");
    }
    {
        std::vector<int> n3={1};
        TreeNode* r=Solution().sortedArrayToBST(n3);
        check(r->val==1&&r->left==nullptr&&r->right==nullptr,"single -> leaf");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
