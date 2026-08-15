#include <iostream>
#include <algorithm>
#include <cassert>

// PROBLEM: AVL Balancing - Choose correct rotation
// Balance Factor (BF) = height(left) - height(right)
//   BF > 1  -> LEFT heavy (LL or LR case)
//   BF < -1 -> RIGHT heavy (RR or RL case)
//
//   LL case: BF > 1  && BF(left) >= 0  -> rotateRight
//   LR case: BF > 1  && BF(left) < 0   -> rotateLeft(left), then rotateRight
//   RR case: BF < -1 && BF(right) <= 0 -> rotateLeft
//   RL case: BF < -1 && BF(right) > 0  -> rotateRight(right), then rotateLeft

struct AVLNode {
    int val, height; AVLNode *left, *right;
    AVLNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

int getH(AVLNode* n) { return n ? n->height : 0; }
int getBF(AVLNode* n) { return n ? getH(n->left) - getH(n->right) : 0; }

class Solution {
private:
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left; AVLNode* T2 = x->right;
        x->right = y; y->left = T2;
        y->height = std::max(getH(y->left), getH(y->right)) + 1;
        x->height = std::max(getH(x->left), getH(x->right)) + 1;
        return x;
    }
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right; AVLNode* T2 = y->left;
        y->left = x; x->right = T2;
        x->height = std::max(getH(x->left), getH(x->right)) + 1;
        y->height = std::max(getH(y->left), getH(y->right)) + 1;
        return y;
    }

public:
    AVLNode* balance(AVLNode* node) {
        // TODO:
        // 1. Update node->height = max(getH(left), getH(right)) + 1
        // 2. Compute bf = getBF(node)
        // 3. Handle LL, LR, RR, RL cases using rotations above
        // 4. Return balanced node

        return node;
    }
};

int main() {
    //   5
    //  /
    // 2
    //  \
    //   3   <- LR case, balance(5) should yield 3 as new root
    AVLNode* r = new AVLNode(5); r->height = 3;
    r->left = new AVLNode(2); r->left->height = 2;
    r->left->right = new AVLNode(3);
    AVLNode* res = Solution().balance(r);
    assert(res->val == 3);
    std::cout << "9_AVL Coding 2 Passed!" << std::endl;
    return 0;
}
