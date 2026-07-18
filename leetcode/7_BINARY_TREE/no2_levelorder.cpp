/**
 * @brief LeetCode 102 - Binary Tree Level Order Traversal
 * @difficulty Medium
 * @link https://leetcode.com/problems/binary-tree-level-order-traversal/
 *
 * Problem:
 * BFS traversal, grouped by level.
 * 
 * Example: [3,9,20,null,null,15,7] -> [[3],[9,20],[15,7]]
 * 
 * Constraints: 0 <= nodes <= 2000 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        // TODO (BFS)
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
        r->left=new TreeNode(9); r->right=new TreeNode(20);
        r->right->left=new TreeNode(15); r->right->right=new TreeNode(7);
        auto res=Solution().levelOrder(r);
        check(res.size()==3,"3 levels");
        check(res[0][0]==3,"level 0: [3]");
        check(res[1][0]==9&&res[1][1]==20,"level 1: [9,20]");
        check(res[2][0]==15&&res[2][1]==7,"level 2: [15,7]");
    }
    {
        auto res=Solution().levelOrder(nullptr);
        check(res.empty(),"null -> empty");
    }
    {
        TreeNode* r2=new TreeNode(1);
        auto res=Solution().levelOrder(r2);
        check(res.size()==1&&res[0][0]==1,"single node");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
