/**
 * @brief LeetCode 700 - Search in a BST
 * @difficulty Easy
 * @link https://leetcode.com/problems/search-in-a-binary-search-tree/
 *
 * Problem:
 * Find node with given value in BST, return its subtree. Null if not found.
 * 
 * Example: BST=[4,2,7,1,3], val=2 -> [2,1,3]
 * 
 * Constraints: 1 <= nodes <= 5000 */

#include <iostream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    TreeNode* r=new TreeNode(4);
    r->left=new TreeNode(2); r->right=new TreeNode(7);
    r->left->left=new TreeNode(1); r->left->right=new TreeNode(3);
    check(Solution().searchBST(r,2)->val==2,   "found 2");
    check(Solution().searchBST(r,1)->val==1,   "found 1");
    check(Solution().searchBST(r,7)->val==7,   "found 7");
    check(Solution().searchBST(r,5)==nullptr,  "5 not found -> null");
    check(Solution().searchBST(nullptr,1)==nullptr,"null tree -> null");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
