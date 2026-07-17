/**
 * @file no5_serialize_deserialize_binary_tree.cpp
 * @brief LeetCode 297 - Serialize and Deserialize Binary Tree
 * 
 * Difficulty: Hard
 * LeetCode Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 * 
 * Problem Description:
 * Serialization is the process of converting a data structure or object into a sequence of bits 
 * so that it can be stored in a file or memory buffer, or transmitted across a network connection 
 * link to be reconstructed later in the same or another computer environment.
 * 
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how 
 * your serialization/deserialization algorithm should work. You just need to ensure that a binary 
 * tree can be serialized to a string and this string can be deserialized to the original tree structure.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^4].
 * - -1000 <= Node.val <= 1000
 */

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
private:
    // Helper function for preorder serialization
    void serializeHelper(TreeNode* root, std::string& out) {
        if (root == nullptr) {
            out += "#,"; // Use '#' to represent null nodes, separated by commas
            return;
        }
        out += std::to_string(root->val) + ",";
        serializeHelper(root->left, out);
        serializeHelper(root->right, out);
    }

    // Helper function for preorder deserialization
    TreeNode* deserializeHelper(std::queue<std::string>& q) {
        if (q.empty()) return nullptr;

        std::string val = q.front();
        q.pop();

        if (val == "#") {
            return nullptr;
        }

        TreeNode* node = new TreeNode(std::stoi(val));
        node->left = deserializeHelper(q);
        node->right = deserializeHelper(q);
        return node;
    }

public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string result = "";
        serializeHelper(root, result);
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        std::queue<std::string> q;
        std::stringstream ss(data);
        std::string token;
        
        // Split string by commas and push to queue
        while (std::getline(ss, token, ',')) {
            if (!token.empty()) {
                q.push(token);
            }
        }
        
        return deserializeHelper(q);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

/*
 * =========================================================================
 * MANUAL DRY RUN TRACE
 * Test Tree Structure:
 *        1
 *       / \
 *      2   3
 *         / \
 *        4   5
 * 
 * -------------------------------------------------------------------------
 * Serialization Process (Preorder traversal: Root -> Left -> Right):
 * 1. Start at root (1): Append "1," -> result = "1,"
 * 2. Move left (2): Append "2," -> result = "1,2,"
 *    - Move left of 2 (null): Append "#," -> result = "1,2,#,"
 *    - Move right of 2 (null): Append "#," -> result = "1,2,#,#,"
 * 3. Move right of 1 (3): Append "3," -> result = "1,2,#,#,3,"
 *    - Move left of 3 (4): Append "4," -> result = "1,2,#,#,3,4,"
 *      - Move left of 4 (null): Append "#," -> result = "1,2,#,#,3,4,#,"
 *      - Move right of 4 (null): Append "#," -> result = "1,2,#,#,3,4,#,#,"
 *    - Move right of 3 (5): Append "5," -> result = "1,2,#,#,3,4,#,#,5,"
 *      - Move left of 5 (null): Append "#," -> result = "1,2,#,#,3,4,#,#,5,#,"
 *      - Move right of 5 (null): Append "#," -> result = "1,2,#,#,3,4,#,#,5,#,#,"
 * Final Serialized String: "1,2,#,#,3,4,#,#,5,#,#,"
 * 
 * -------------------------------------------------------------------------
 * Deserialization Process:
 * 1. Parse string "1,2,#,#,3,4,#,#,5,#,#," by ',' and populate queue:
 *    q = ["1", "2", "#", "#", "3", "4", "#", "#", "5", "#", "#"]
 * 
 * 2. Call deserializeHelper(q):
 *    - Pop "1". Create Node(1).
 *    - Set Node(1)->left = deserializeHelper(q):
 *      - Pop "2". Create Node(2).
 *      - Set Node(2)->left = deserializeHelper(q):
 *        - Pop "#". Return nullptr. Node(2)->left = nullptr.
 *      - Set Node(2)->right = deserializeHelper(q):
 *        - Pop "#". Return nullptr. Node(2)->right = nullptr.
 *      - Return Node(2). Node(1)->left = Node(2).
 *    - Set Node(1)->right = deserializeHelper(q):
 *      - Pop "3". Create Node(3).
 *      - Set Node(3)->left = deserializeHelper(q):
 *        - Pop "4". Create Node(4).
 *        - Set Node(4)->left = deserializeHelper(q):
 *          - Pop "#". Return nullptr. Node(4)->left = nullptr.
 *        - Set Node(4)->right = deserializeHelper(q):
 *          - Pop "#". Return nullptr. Node(4)->right = nullptr.
 *        - Return Node(4). Node(3)->left = Node(4).
 *      - Set Node(3)->right = deserializeHelper(q):
 *        - Pop "5". Create Node(5).
 *        - Set Node(5)->left = deserializeHelper(q):
 *          - Pop "#". Return nullptr. Node(5)->left = nullptr.
 *        - Set Node(5)->right = deserializeHelper(q):
 *          - Pop "#". Return nullptr. Node(5)->right = nullptr.
 *        - Return Node(5). Node(3)->right = Node(5).
 *      - Return Node(3). Node(1)->right = Node(3).
 *    - Return Node(1) (reconstructed root).
 * 
 * =========================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS
 * Serialization:
 *   - Time Complexity: O(N) where N is the number of nodes. We visit each node exactly once.
 *   - Space Complexity: O(N) since we produce a string representing all nodes and null pointers,
 *     and the recursion stack uses O(H) space.
 * Deserialization:
 *   - Time Complexity: O(N). We process each value in the queue/string exactly once.
 *   - Space Complexity: O(N) to store the queue of tokens and the recursion stack of height H.
 * =========================================================================
 */
