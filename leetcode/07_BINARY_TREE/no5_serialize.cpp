/**
 * @brief LeetCode 297 - Serialize/Deserialize Binary Tree
 * @difficulty Hard
 * @link https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 *
 * Problem:
 * Convert tree to string and back.
 * 
 * Example: serialize/deserialize must produce identical tree.
 * 
 * Constraints: 0 <= nodes <= 10^4 */

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    std::string serialize(TreeNode* root) {
        // TODO (preorder, '#' for null)
    }
    TreeNode* deserialize(std::string data) {
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
        TreeNode* r=new TreeNode(1);
        r->left=new TreeNode(2); r->right=new TreeNode(3);
        Codec c;
        TreeNode* out=c.deserialize(c.serialize(r));
        check(out->val==1&&out->left->val==2&&out->right->val==3,"serialize/deserialize 1-2-3");
    }
    {
        Codec c;
        TreeNode* out=c.deserialize(c.serialize(nullptr));
        check(out==nullptr,"null roundtrip -> null");
    }
    {
        TreeNode* r2=new TreeNode(42);
        Codec c;
        check(c.deserialize(c.serialize(r2))->val==42,"single node roundtrip");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
