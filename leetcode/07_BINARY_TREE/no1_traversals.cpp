/**
 * @brief LeetCode 94/144/145 - Binary Tree Traversals
 * @difficulty Easy
 * @link https://leetcode.com/problems/binary-tree-inorder-traversal/
 *
 * Problem:
 * Implement inorder (L-Root-R), preorder (Root-L-R), postorder (L-R-Root).
 * Iterative preferred.
 * 
 * Example: [1,null,2,3] inorder -> [1,3,2] */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) { // TODO
    }
    std::vector<int> preorderTraversal(TreeNode* root) { // TODO
    }
    std::vector<int> postorderTraversal(TreeNode* root) { // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    TreeNode* r = new TreeNode(1);
    r->left=new TreeNode(2); r->right=new TreeNode(3);
    r->left->left=new TreeNode(4); r->left->right=new TreeNode(5);
    {
        auto in=Solution().inorderTraversal(r);
        check(in[0]==4&&in[1]==2&&in[2]==5&&in[3]==1&&in[4]==3,"inorder: 4-2-5-1-3");
    }
    {
        auto pre=Solution().preorderTraversal(r);
        check(pre[0]==1&&pre[1]==2&&pre[2]==4,"preorder starts 1-2-4");
    }
    {
        auto post=Solution().postorderTraversal(r);
        check(post[4]==1&&post[3]==3,"postorder root is last");
    }
    {
        auto in2=Solution().inorderTraversal(nullptr);
        check(in2.empty(),"null tree -> empty");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
