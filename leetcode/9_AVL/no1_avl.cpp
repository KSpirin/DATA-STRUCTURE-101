/**
 * @file no1_avl_implementation.cpp
 * @brief Custom AVL Tree Implementation (Insertion, Deletion, and Rebalancing)
 * @difficulty Hard (Data Structure Design)
 * @link Custom Implementation Reference
 *
 * Problem Description:
 * Design and implement a self-balancing Binary Search Tree (AVL Tree) from scratch.
 * The class must support:
 * 1. Templated keys.
 * 2. Proper encapsulation (private helpers, public interfaces).
 * 3. Dynamic height calculation and Balance Factor verification (BF = left_height - right_height).
 * 4. Rebalancing operations:
 *    - Single Right Rotation (LL case)
 *    - Single Left Rotation (RR case)
 *    - Double Left-Right Rotation (LR case)
 *    - Double Right-Left Rotation (RL case)
 * 5. Insertion and Deletion while maintaining the AVL balance property at every node.
 * 6. Helper traversal methods to print or check the tree structure.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iomanip>

// AVLNode structure for the templated AVL Tree
template <typename T>
struct AVLNode {
    T val;
    AVLNode* left;
    AVLNode* right;
    int height; // Height of the node: leaf is 0, nullptr is -1

    AVLNode(const T& x) 
        : val(x), left(nullptr), right(nullptr), height(0) {}
};

// Templated AVLTree Class
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Helper: returns the height of a node, or -1 if null
    int height(AVLNode<T>* node) const {
        return node ? node->height : -1;
    }

    // Helper: calculates the balance factor of a node (left_height - right_height)
    int getBalanceFactor(AVLNode<T>* node) const {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    // Update the height of a node based on its children
    void updateHeight(AVLNode<T>* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    /*
     * Single Right Rotation (LL Imbalance)
     * Rebalances a left-heavy subtree where left child is also left-heavy or balanced.
     *
     *        k2 (+2)                k1 (0)
     *       /   \                  /  \
     *     k1     Z      ===>      X    k2 (0)
     *    /  \                    /    /  \
     *   X    Y                  W    Y    Z
     *  /
     * W
     */
    AVLNode<T>* rotateRight(AVLNode<T>* k2) {
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        // Recalculate heights for the affected nodes
        updateHeight(k2);
        updateHeight(k1);

        return k1; // New root of this subtree
    }

    /*
     * Single Left Rotation (RR Imbalance)
     * Rebalances a right-heavy subtree where right child is also right-heavy or balanced.
     *
     *      k1 (-2)                  k2 (0)
     *     /   \                    /  \
     *    X     k2       ===>      k1   Z
     *         /  \               /  \   \
     *        Y    Z             X    Y   W
     *              \
     *               W
     */
    AVLNode<T>* rotateLeft(AVLNode<T>* k1) {
        AVLNode<T>* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        // Recalculate heights for the affected nodes
        updateHeight(k1);
        updateHeight(k2);

        return k2; // New root of this subtree
    }

    /*
     * Double Left-Right Rotation (LR Imbalance)
     * Rebalances a left-heavy subtree where left child is right-heavy.
     *
     *       k3 (+2)                 k3 (+2)                  k2 (0)
     *      /   \                   /   \                    /  \
     *    k1     D  Rotate Left   k2     D  Rotate Right   k1    k3
     *   /  \       =========>   /  \       =========>    / \   / \
     *  A    k2                 k1   C                   A   B C   D
     *      /  \               /  \
     *     B    C             A    B
     */
    AVLNode<T>* doubleRotateLeftRight(AVLNode<T>* k3) {
        k3->left = rotateLeft(k3->left);
        return rotateRight(k3);
    }

    /*
     * Double Right-Left Rotation (RL Imbalance)
     * Rebalances a right-heavy subtree where right child is left-heavy.
     *
     *      k1 (-2)                 k1 (-2)                  k2 (0)
     *     /   \                   /   \                    /  \
     *    A     k3  Rotate Right  A     k2   Rotate Left  k1    k3
     *         /  \ ============>      /  \  =========>  / \   / \
     *        k2   D                  B    k3           A   B C   D
     *       /  \                           \
     *      B    C                           C
     */
    AVLNode<T>* doubleRotateRightLeft(AVLNode<T>* k1) {
        k1->right = rotateRight(k1->right);
        return rotateLeft(k1);
    }

    // Rebalance a node if it violates the AVL property
    AVLNode<T>* balance(AVLNode<T>* node) {
        if (!node) return nullptr;

        updateHeight(node);
        int bf = getBalanceFactor(node);

        // Case 1: Left-heavy (BF > 1)
        if (bf > 1) {
            // Check left child's balance factor to differentiate LL and LR
            if (getBalanceFactor(node->left) >= 0) {
                // LL Case -> Single Right Rotation
                return rotateRight(node);
            } else {
                // LR Case -> Double Left-Right Rotation
                return doubleRotateLeftRight(node);
            }
        }
        // Case 2: Right-heavy (BF < -1)
        else if (bf < -1) {
            // Check right child's balance factor to differentiate RR and RL
            if (getBalanceFactor(node->right) <= 0) {
                // RR Case -> Single Left Rotation
                return rotateLeft(node);
            } else {
                // RL Case -> Double Right-Left Rotation
                return doubleRotateRightLeft(node);
            }
        }

        return node; // Balanced
    }

    // Recursive insertion helper
    AVLNode<T>* insertHelper(AVLNode<T>* node, const T& val) {
        if (!node) {
            return new AVLNode<T>(val);
        }

        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        } else {
            return node; // Duplicate keys are not allowed in this implementation
        }

        return balance(node); // Perform path rebalancing on the way up
    }

    // Find the node with the minimum value in a subtree
    AVLNode<T>* findMin(AVLNode<T>* node) const {
        if (!node) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // Recursive deletion helper
    AVLNode<T>* removeHelper(AVLNode<T>* node, const T& val) {
        if (!node) return nullptr;

        if (val < node->val) {
            node->left = removeHelper(node->left, val);
        } else if (val > node->val) {
            node->right = removeHelper(node->right, val);
        } else {
            // Found node to delete
            if (!node->left && !node->right) {
                // Case 1: Leaf node
                delete node;
                node = nullptr;
            } else if (!node->left || !node->right) {
                // Case 2: Single child
                AVLNode<T>* temp = node->left ? node->left : node->right;
                delete node;
                node = temp;
            } else {
                // Case 3: Two children
                // Find successor (minimum key in right subtree)
                AVLNode<T>* successor = findMin(node->right);
                node->val = successor->val;
                node->right = removeHelper(node->right, successor->val);
            }
        }

        if (!node) return nullptr;

        return balance(node); // Rebalance current node after deletion
    }

    // In-order traversal print helper
    void inorderHelper(AVLNode<T>* node) const {
        if (node) {
            inorderHelper(node->left);
            std::cout << node->val << " (H: " << node->height 
                      << ", BF: " << getBalanceFactor(node) << ") ";
            inorderHelper(node->right);
        }
    }

    // Visual tree display helper
    void printTreeHelper(AVLNode<T>* node, int indent = 0) const {
        if (node != nullptr) {
            if (node->right) {
                printTreeHelper(node->right, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (node->right) std::cout << " /\n" << std::setw(indent) << ' ';
            std::cout << node->val << "\n";
            if (node->left) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                printTreeHelper(node->left, indent + 4);
            }
        }
    }

    // Destructor helper to release memory recursively
    void clear(AVLNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    // Constructor
    AVLTree() : root(nullptr) {}

    // Destructor
    ~AVLTree() {
        clear(root);
    }

    // Public Insert
    void insert(const T& val) {
        root = insertHelper(root, val);
    }

    // Public Remove
    void remove(const T& val) {
        root = removeHelper(root, val);
    }

    // Public In-order Traversal
    void inorder() const {
        inorderHelper(root);
        std::cout << "\n";
    }

    // Public Print Tree (Structured Visualization)
    void printTree() const {
        std::cout << "--- Tree Structure (rotated 90 deg counter-clockwise) ---\n";
        printTreeHelper(root);
        std::cout << "---------------------------------------------------------\n";
    }

    // Accessor for the root height
    int getRootHeight() const {
        return height(root);
    }
};

/*
 * =========================================================================
 * MANUAL DRY-RUN TRACE
 * =========================================================================
 * Test Sequence: Insert 3, 2, 1, 4, 5, 6, 7 in an empty AVL Tree.
 *
 * 1. Insert 3:
 *    [3] (H=0, BF=0)
 *
 * 2. Insert 2:
 *      3 (H=1, BF=1)
 *     /
 *    2 (H=0, BF=0)
 *
 * 3. Insert 1:
 *      3 (H=2, BF=2) -> Unbalanced at 3!
 *     /
 *    2 (H=1, BF=1)
 *   /
 *  1 (H=0, BF=0)
 *  - This is LL Case (Left-heavy node 3, left-heavy child 2).
 *  - Apply single Right Rotation on node 3:
 *    `rotateRight(3)` makes 2 the root, 3 becomes 2's right child.
 *    Resulting Tree:
 *      2 (H=1, BF=0)
 *     / \
 *    1   3 (Both H=0)
 *
 * 4. Insert 4:
 *      2 (H=2, BF=-1)
 *     / \
 *    1   3 (H=1, BF=-1)
 *         \
 *          4 (H=0)
 *
 * 5. Insert 5:
 *      2 (H=3, BF=-2) -> Node 2 has BF=-1, but parent of 4 (node 3) has BF=-2!
 *     / \
 *    1   3 (H=2, BF=-2) -> Unbalanced at 3!
 *         \
 *          4 (H=1, BF=-1)
 *           \
 *            5 (H=0)
 *  - This is RR Case (Right-heavy node 3, right-heavy child 4).
 *  - Apply single Left Rotation on node 3:
 *    `rotateLeft(3)` makes 4 the parent of 3.
 *    Resulting Tree:
 *        2 (H=2, BF=-1)
 *       / \
 *      1   4 (H=1, BF=0)
 *         / \
 *        3   5 (Both H=0)
 *
 * 6. Insert 6:
 *        2 (H=3, BF=-2) -> Unbalanced at root node 2!
 *       / \
 *      1   4 (H=2, BF=-1)
 *         / \
 *        3   5 (H=1, BF=-1)
 *             \
 *              6 (H=0)
 *  - This is RR Case on root node 2 (Right-heavy node 2, right-heavy child 4).
 *  - Apply single Left Rotation on node 2:
 *    `rotateLeft(2)` makes 4 the root of the tree.
 *    Resulting Tree:
 *          4 (H=2, BF=0)
 *        /   \
 *       2     5 (H=1, BF=-1)
 *      / \     \
 *     1   3     6 (H=0)
 *
 * 7. Insert 7:
 *          4 (H=3, BF=-1)
 *        /   \
 *       2     5 (H=2, BF=-2) -> Unbalanced at 5!
 *      / \     \
 *     1   3     6 (H=1, BF=-1)
 *                \
 *                 7 (H=0)
 *  - This is RR Case on node 5 (Right-heavy node 5, right-heavy child 6).
 *  - Apply single Left Rotation on node 5:
 *    Resulting Tree:
 *          4 (H=2, BF=0)
 *        /   \
 *       2     6 (H=1, BF=0)
 *      / \   / \
 *     1   3 5   7 (All leaves H=0)
 *
 * =========================================================================
 * TIME AND SPACE COMPLEXITY ANALYSIS
 * =========================================================================
 * - Time Complexity:
 *   - Insertion: O(log N) as it traverses down the tree height to insert, 
 *     then climbs up doing constant time rotation checks O(1) at each level.
 *   - Deletion: O(log N) as it locates the node, performs constant-time swaps, 
 *     and bubbles back up to rebalance.
 *   - Traversal: O(N) to visit every node once.
 * - Space Complexity:
 *   - O(N) memory allocation for N nodes.
 *   - Auxiliary Space: O(log N) for the recursion call stack during operations.
 */

int main() {
    AVLTree<int> tree;

    std::cout << "Step 1: Inserting values 3, 2, 1 (Triggers LL balance, right rotation)\n";
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.printTree();
    tree.inorder();

    std::cout << "\nStep 2: Inserting values 4, 5 (Triggers RR balance at node 3, left rotation)\n";
    tree.insert(4);
    tree.insert(5);
    tree.printTree();
    tree.inorder();

    std::cout << "\nStep 3: Inserting value 6 (Triggers RR balance at root 2, left rotation)\n";
    tree.insert(6);
    tree.printTree();
    tree.inorder();

    std::cout << "\nStep 4: Inserting value 7 (Triggers RR balance at node 5, left rotation)\n";
    tree.insert(7);
    tree.printTree();
    tree.inorder();

    std::cout << "\nStep 5: Deleting root node 4 (Two children, successor swap)\n";
    tree.remove(4);
    tree.printTree();
    tree.inorder();

    std::cout << "\nStep 6: Deleting nodes 1 and 2 to check rebalancing upon deletion\n";
    tree.remove(1);
    tree.remove(2);
    tree.printTree();
    tree.inorder();

    return 0;
}
