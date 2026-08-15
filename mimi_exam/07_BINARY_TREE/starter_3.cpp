#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

// PROBLEM: LeetCode 297 - Serialize & Deserialize Binary Tree
// Convert tree to string and back.

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
private:
    // TODO helper for serialize (preorder DFS):
    void ser(TreeNode* root, std::ostringstream& out) {
        // - If null: write "# " and return
        // - Write root->val + " "
        // - Recurse left, then right
    }

    // TODO helper for deserialize:
    TreeNode* deser(std::istringstream& in) {
        // - Read next token
        // - If "#": return nullptr
        // - Create node with stoi(token)
        // - node->left = deser(in), node->right = deser(in)
        // - Return node
        return nullptr;
    }

public:
    std::string serialize(TreeNode* root) {
        // TODO: Use ostringstream + ser()
        return "";
    }

    TreeNode* deserialize(std::string data) {
        // TODO: Use istringstream(data) + deser()
        return nullptr;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    Codec codec;
    TreeNode* nr = codec.deserialize(codec.serialize(root));
    assert(nr->val == 1 && nr->right->val == 2);
    std::cout << "7_BINARY_TREE Coding 3 Passed!" << std::endl;
    return 0;
}
