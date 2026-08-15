#include <iostream>
#include <algorithm>
#include <cassert>

// PROBLEM: AVL Right Rotation (LL Case)
// Used when left subtree is too tall (Balance Factor > 1).
//
//     y                x
//    / \              / \
//   x   T3   ->     T1  y
//  / \                 / \
// T1  T2              T2  T3
//
// Steps: x = y->left, y->left = x->right, x->right = y, update heights

struct AVLNode {
    int val, height; AVLNode *left, *right;
    AVLNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(AVLNode* n) { return n ? n->height : 0; }

class Solution {
public:
    AVLNode* rotateRight(AVLNode* y) {
        // TODO:
        // 1. x = y->left
        // 2. T2 = x->right
        // 3. x->right = y
        // 4. y->left = T2
        // 5. Update y->height first, then x->height
        // 6. Return x (new root)

        return y;
    }
};

int main() {
    //     3
    //    /
    //   2
    //  /
    // 1    <- LL imbalance at 3, rotateRight(3) should return 2
    AVLNode* r = new AVLNode(3);
    r->left = new AVLNode(2);
    r->left->left = new AVLNode(1);
    AVLNode* res = Solution().rotateRight(r);
    assert(res->val == 2 && res->left->val == 1 && res->right->val == 3);
    std::cout << "9_AVL Coding 1 Passed!" << std::endl;
    return 0;
}
