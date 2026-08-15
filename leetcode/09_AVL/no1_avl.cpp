/**
 * @brief Custom - AVL Tree Rotations & Insert
 * @difficulty Custom
 *
 * Problem:
 * Self-balancing AVL tree.
 * Implement: getHeight, getBalance, rotateLeft, rotateRight, insert.
 * |balance| must always be <= 1 after each insert.
 * 
 * Example: insert 10,20,30 -> LL rotation, root becomes 20 */

#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

struct AVLNode {
    int val, height;
    AVLNode *left, *right;
    AVLNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(AVLNode* n) { // TODO
}

int getBalance(AVLNode* n) { // TODO
}

AVLNode* rotateRight(AVLNode* y) { // TODO (LL case)
}

AVLNode* rotateLeft(AVLNode* x) { // TODO (RR case)
}

AVLNode* insert(AVLNode* root, int val) {
    // TODO: BST insert then rebalance
    // Cases: LL, LR, RR, RL
}

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    AVLNode* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);  // RR case -> rotateLeft, root becomes 20
    check(root->val == 20,       "insert 10,20,30 -> root is 20 (RR rotation)");
    check(getBalance(root) == 0, "root balanced after RR");

    root = insert(root, 40);
    root = insert(root, 50);  // another RR on right subtree
    check(root->val == 20 || root->val == 30, "root stays balanced");
    check(getBalance(root) >= -1 && getBalance(root) <= 1, "balance in [-1,1]");

    root = insert(root, 25);  // RL case
    check(getBalance(root) >= -1 && getBalance(root) <= 1, "balanced after RL");

    AVLNode* r2 = nullptr;
    r2 = insert(r2, 30);
    r2 = insert(r2, 20);
    r2 = insert(r2, 10);  // LL case -> rotateRight
    check(r2->val == 20, "insert 30,20,10 -> root is 20 (LL rotation)");
    check(getBalance(r2) == 0, "LL rotation balanced");

    AVLNode* r3 = nullptr;
    r3 = insert(r3, 30);
    r3 = insert(r3, 10);
    r3 = insert(r3, 20);  // LR case -> rotateLeft then rotateRight
    check(r3->val == 20, "LR case -> root is 20");


    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
