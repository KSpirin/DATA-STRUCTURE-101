/**
 * @brief LeetCode 701 - Insert into a BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/insert-into-a-binary-search-tree/
 *
 * Problem:
 * Insert value into BST. Guaranteed val does not exist.
 * 
 * Example: BST=[4,2,7,1,3], val=5 -> [4,2,7,1,3,5]
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
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
        TreeNode* r=new TreeNode(4);
        r->left=new TreeNode(2); r->right=new TreeNode(7);
        TreeNode* res=Solution().insertIntoBST(r,5);
        check(res->right->left!=nullptr&&res->right->left->val==5,"insert 5 -> left of 7");
    }
    {
        TreeNode* r2=nullptr;
        TreeNode* res=Solution().insertIntoBST(r2,1);
        check(res!=nullptr&&res->val==1,"insert into empty tree");
    }
    {
        TreeNode* r3=new TreeNode(5);
        Solution().insertIntoBST(r3,3);
        check(r3->left!=nullptr&&r3->left->val==3,"insert 3 left of 5");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
