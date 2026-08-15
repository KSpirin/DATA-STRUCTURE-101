# Binary Search Tree (BST) Study Guide

A **Binary Search Tree (BST)** is a node-based binary tree data structure which has the following properties:
- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree of a node contains only nodes with keys **greater than** the node's key.
- The left and right subtrees must each also be a binary search tree.
- There must be no duplicate nodes (typically, although variations allow them).

---

## Table of Contents
1. [Core Properties](#1-core-properties)
2. [Implementations](#2-implementations)
   - [Linked List Representation](#linked-list-representation)
   - [Array Representation](#array-representation)
3. [Operations & Complexities](#3-operations--complexities)
   - [Search](#search)
   - [Insertion](#insertion)
   - [Deletion (3 Cases)](#deletion-3-cases)
4. [Complete C++ Templated Implementation](#4-complete-c-templated-implementation)
5. [Inorder Traversal Property](#5-inorder-traversal-property)
6. [LeetCode Practice & Solutions](#6-leetcode-practice--solutions)

---

## 1. Core Properties

* **Binary Search Property:** For every node $X$ in the tree:
  $$\text{Key}(Y) < \text{Key}(X), \quad \forall Y \in \text{LeftSubtree}(X)$$
  $$\text{Key}(Z) > \text{Key}(X), \quad \forall Z \in \text{RightSubtree}(X)$$
* **Inorder Traversal:** Performing an inorder traversal (Left $\rightarrow$ Root $\rightarrow$ Right) of a BST visits the nodes in **strictly ascending (sorted)** order. E.g., if a BST contains $\{6, 3, 10, 1, 4, 8\}$, the inorder traversal output is:
  $$1 \rightarrow 3 \rightarrow 4 \rightarrow 6 \rightarrow 8 \rightarrow 10$$

---

## 2. Implementations

### Linked List Representation
Each node is dynamically allocated and contains:
- `value`/`key`: The stored data.
- `left`: Pointer to the left child node (or `nullptr`).
- `right`: Pointer to the right child node (or `nullptr`).

```cpp
template <typename T>
struct Node {
    T value;
    Node* left;
    Node* right;
    
    Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
};
```

### Array Representation
BSTs can be mapped to a flat array where for a node at index $i$ (0-indexed):
- **Left Child Index:** $2i + 1$
- **Right Child Index:** $2i + 2$
- **Parent Index:** $\lfloor \frac{i - 1}{2} \rfloor$

> [!WARNING]
> While array representation is efficient for **complete** or **nearly complete** binary trees (like Binary Heaps), it can be highly wasteful in space for skewed BSTs. For example, a skewed tree of height $h$ can require an array of size $2^h - 1$, resulting in $O(2^h)$ space complexity with many unused (`nullptr`/empty) slots.

---

## 3. Operations & Complexities

| Operation | Average Case | Worst Case (Skewed Tree) | Space Complexity (Call Stack) |
| :--- | :--- | :--- | :--- |
| **Search** | $O(\log n)$ | $O(n)$ | $O(h)$ recursive / $O(1)$ iterative |
| **Insert** | $O(\log n)$ | $O(n)$ | $O(h)$ recursive / $O(1)$ iterative |
| **Delete** | $O(\log n)$ | $O(n)$ | $O(h)$ recursive / $O(1)$ iterative |

---

### Search
Compare the target value with the current node's value:
- If equal, search is successful.
- If target is smaller, search recursively in the left subtree.
- If target is larger, search recursively in the right subtree.
- If the node is `nullptr`, the key does not exist.

### Insertion
Find the appropriate leaf position where the new key should reside to maintain the BST property, and insert the new node there.
- Do not insert if the key already exists (to prevent duplicates).

---

### Deletion (3 Cases)

Deletion is the most complex operation because the BST property must be maintained after the node is removed.

#### Case 1: The node to be deleted is a Leaf Node (No children)
- **Action:** Simply delete the node and set the parent's pointer to `nullptr`.
- **Visual:**
  ```text
        5                   5
       / \      Delete 3   / \
      3   8    -------->  nullptr 8
  ```

#### Case 2: The node to be deleted has a Single Child Node (1 child)
- **Action:** Bypass the node by linking its parent directly to its only child, then delete the node.
- **Visual:**
  ```text
        5                   5
       / \      Delete 3   /
      3   8    -------->  1
     /
    1
  ```

#### Case 3: The node to be deleted has Two Children (2 children)
- **Action:** Replace the value of the node with either:
  1. Its **Inorder Successor** (the minimum value in its right subtree).
  2. Its **Inorder Predecessor** (the maximum value in its left subtree).
- Then, recursively delete the inorder successor/predecessor node (which is guaranteed to fall under Case 1 or Case 2).

- **Inorder Successor Approach:**
  1. Find the smallest node in the right subtree: `findMin(node->right)`.
  2. Copy its value to the node to be deleted.
  3. Delete the successor node from the right subtree.

- **Inorder Predecessor Approach:**
  1. Find the largest node in the left subtree: `findMax(node->left)`.
  2. Copy its value to the node to be deleted.
  3. Delete the predecessor node from the left subtree.

---

## 4. Complete C++ Templated Implementation

Here is a fully verified, exception-safe, templated Binary Search Tree class implementation in C++. It includes both inorder successor and inorder predecessor deletion strategies, along with standard accessors and memory cleanup.

```cpp
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node* clone(Node* node) const {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);
        return newNode;
    }

    Node* insert(Node* node, const T& val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        // Duplicate values are ignored
        return node;
    }

    bool search(Node* node, const T& val) const {
        if (node == nullptr) return false;
        if (val == node->data) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    Node* findMin(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // Deletion using inorder successor (default choice)
    Node* removeSuccessor(Node* node, const T& val) {
        if (node == nullptr) return nullptr;

        if (val < node->data) {
            node->left = removeSuccessor(node->left, val);
        } else if (val > node->data) {
            node->right = removeSuccessor(node->right, val);
        } else {
            // Found node to delete
            // Case 1 & 2: No child or 1 child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: 2 children - replace with Inorder Successor (min of right subtree)
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeSuccessor(node->right, temp->data);
        }
        return node;
    }

    // Deletion using inorder predecessor (alternative choice)
    Node* removePredecessor(Node* node, const T& val) {
        if (node == nullptr) return nullptr;

        if (val < node->data) {
            node->left = removePredecessor(node->left, val);
        } else if (val > node->data) {
            node->right = removePredecessor(node->right, val);
        } else {
            // Found node to delete
            // Case 1 & 2: No child or 1 child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: 2 children - replace with Inorder Predecessor (max of left subtree)
            Node* temp = findMax(node->left);
            node->data = temp->data;
            node->left = removePredecessor(node->left, temp->data);
        }
        return node;
    }

    void inorder(Node* node) const {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Destructor
    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Copy Constructor
    BinarySearchTree(const BinarySearchTree& other) {
        root = clone(other.root);
    }

    // Copy Assignment Operator
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            destroyTree(root);
            root = clone(other.root);
        }
        return *this;
    }

    // Public API
    void insert(const T& val) {
        root = insert(root, val);
    }

    bool contains(const T& val) const {
        return search(root, val);
    }

    // Deletion wrapper using successor strategy
    void remove(const T& val) {
        root = removeSuccessor(root, val);
    }

    // Deletion wrapper using predecessor strategy
    void removeUsingPredecessor(const T& val) {
        root = removePredecessor(root, val);
    }

    T getMin() const {
        Node* minNode = findMin(root);
        if (minNode == nullptr) throw std::underflow_error("Tree is empty");
        return minNode->data;
    }

    T getMax() const {
        Node* maxNode = findMax(root);
        if (maxNode == nullptr) throw std::underflow_error("Tree is empty");
        return maxNode->data;
    }

    void printInorder() const {
        inorder(root);
        std::cout << "\n";
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

#endif // BINARY_SEARCH_TREE_H

---

## 5. Inorder Traversal Property

One of the most important characteristics of a Binary Search Tree is that its **inorder traversal** (Left $\rightarrow$ Root $\rightarrow$ Right) visits the nodes in **strictly sorted ascending order**.

### Mathematical Proof Outline
For any node $X$:
1. All nodes in the left subtree of $X$ have keys strictly less than $\text{Key}(X)$.
2. All nodes in the right subtree of $X$ have keys strictly greater than $\text{Key}(X)$.
3. Inorder traversal recursively visits the left subtree, then node $X$, then the right subtree.
4. By induction, the resulting sequence is sorted in ascending order.

This property is extremely useful:
- We can validate if a binary tree is a BST by checking if its inorder traversal is sorted.
- We can find the $k$-th smallest/largest element in a BST easily by performing a partial inorder traversal.
- We can construct a balanced BST from a sorted array by recursively finding the middle element (which would be the root) and building left and right subtrees.

---

## 6. LeetCode Practice & Solutions

Below is the curated list of LeetCode problems covering BST concepts from basic operations to advanced validation and properties.

| # | Problem Name | Difficulty | Core Concept / Technique | Source Code Link |
| :--- | :--- | :--- | :--- | :--- |
| 1 | **Search in a BST** (LeetCode 700) | Easy | Binary search property recursion & iteration | [no1_search.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no1_search.cpp) |
| 2 | **Insert into a BST** (LeetCode 701) | Medium | Tree mutation, leaf node identification | [no2_insert.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no2_insert.cpp) |
| 3 | **Delete Node in a BST** (LeetCode 450) | Medium | Node deletion with 3 cases (successor/predecessor) | [no3_delete.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no3_delete.cpp) |
| 4 | **Validate BST** (LeetCode 98) | Medium | Boundary range validation via pointers | [no4_validate.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no4_validate.cpp) |
| 5 | **Kth Smallest in a BST** (LeetCode 230) | Medium | Inorder traversal with stack early termination | [no5_kth_smallest.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no5_kth_smallest.cpp) |
| 6 | **Lowest Common Ancestor of a BST** (LeetCode 235) | Easy | BST property (left/right split) | [no6_lca_bst.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no6_lca_bst.cpp) |
| 7 | **Convert BST to Greater Tree** (LeetCode 538) | Medium | Reverse inorder traversal (Right -> Root -> Left) | [no7_greater_tree.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/8_BST/no7_greater_tree.cpp) |

---

### Detailed Walkthroughs

#### LeetCode 98: Validate Binary Search Tree
- **Problem Statement:** Determine if a binary tree is a valid BST.
- **Approach:**
  We cannot just check if a node's left child is smaller and right child is larger (a classic trap!). The condition must hold for the *entire* subtrees.
  We recursively validate the tree by passing down low and high boundary pointers:
  - When we go left, the upper bound (`high`) becomes the current node.
  - When we go right, the lower bound (`low`) becomes the current node.
  This avoids integer overflow since we compare nodes directly using pointers (`TreeNode*`) rather than `INT_MIN`/`INT_MAX`.
- **Complexity:**
  - **Time:** $O(N)$ - each node is visited once.
  - **Space:** $O(H)$ - recursion stack depth where $H$ is the height of the tree.

#### LeetCode 230: Kth Smallest Element in a BST
- **Problem Statement:** Find the $k$-th smallest value (1-indexed) in a BST.
- **Approach:**
  Since the inorder traversal of a BST produces sorted values, we can simulate an inorder traversal iteratively using a `std::stack`.
  We keep visiting left children and pushing them to the stack.
  Then, we pop from the stack, decrement $k$, and if $k$ becomes 0, we return the node's value.
  Otherwise, we move to the right child and continue.
  This iterative approach is optimal because we terminate immediately when the $k$-th element is found, saving unnecessary node traversals.
- **Complexity:**
  - **Time:** $O(H + K)$ - we traverse down to the leftmost leaf ($O(H)$) and then visit $K$ nodes.
  - **Space:** $O(H)$ - size of the stack representing the height of the tree.

#### LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
- **Problem Statement:** Find the lowest common ancestor (LCA) node of two given nodes $p$ and $q$ in the BST.
- **Approach:**
  Leveraging the Binary Search Tree property, we can find the split point where $p$ and $q$ diverge:
  - If both $p$ and $q$ have values less than the current node's value, we move to the left child.
  - If both $p$ and $q$ have values greater than the current node's value, we move to the right child.
  - If they split (one is smaller/equal and the other is larger/equal), the current node is their lowest common ancestor.
  This can be done iteratively in $O(1)$ auxiliary space.
- **Complexity:**
  - **Time:** $O(H)$ - where $H$ is the height of the BST. We traverse one path from the root.
  - **Space:** $O(1)$ - iterative approach using constant memory.

#### LeetCode 538: Convert BST to Greater Tree
- **Problem Statement:** Convert a BST into a "Greater Tree" where every node's value is updated to the sum of its original value and all values greater than it in the tree.
- **Approach:**
  Perform a reverse inorder traversal (Right $\rightarrow$ Root $\rightarrow$ Left). Since a standard inorder traversal visits nodes in ascending order, a reverse inorder traversal visits nodes in descending order.
  By keeping a running sum of all visited nodes, we can update each node's value in-place:
  - Recursively visit the right subtree.
  - Add the current node's value to the running sum.
  - Update the current node's value to the running sum.
  - Recursively visit the left subtree.
- **Complexity:**
  - **Time:** $O(N)$ - we visit each node exactly once.
  - **Space:** $O(H)$ - recursion stack space matching the tree's height.

