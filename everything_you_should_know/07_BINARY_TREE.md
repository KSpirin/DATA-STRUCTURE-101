# Module 7: Binary Trees — Study Guide

Welcome to the definitive study guide for the **Binary Tree** module. This guide covers all definitions, properties, recursive and iterative traversals, expression tree evaluations, and C++ class implementations, highlighting potential bugs in lecture slides to prepare you perfectly for your exams and interviews.

---

## 1. Trees: Core Definitions and Concepts

A **rooted tree** data structure stores information in nodes.
* **Root**: The unique first node in the tree.
* **References**: Each node has a variable number of references to successors (children).
* **Unique Parent**: Each node other than the root has **exactly one parent** pointing to it.

### Node Properties
* **Degree**: The degree of a node is defined as the number of its children.
  * $\text{deg}(A) = 3$ if node $A$ has 3 children.
* **Siblings**: Nodes that share the same parent node.
* **Leaf Node (External Node)**: A node with a degree of zero (no children).
* **Internal Node**: Any node with a degree greater than zero (nodes internal to the tree).
* **Ancestors**: For a node $X$, the set of nodes on the path from the root to $X$, including $X$ itself.
* **Descendants**: For a node $X$, the set of all nodes in subtrees rooted at $X$, including $X$ itself.

### Structural Concepts
* **Path**: A sequence of nodes $(a_0, a_1, \dots, a_n)$ where $a_{k+1}$ is a child of $a_k$.
  * **Path Length**: Defined as $n$ (the number of edges, which is the number of nodes minus 1).
  * *Example*: The path $(B, E, G)$ has length 2.
* **Depth of a Node**: The length of the unique path from the root node to that node.
  * The root node has depth 0.
* **Height of a Tree**: The maximum depth of any node within the tree.
  * A tree with only the root node has height $0$.
  * For convenience and mathematical consistency, an **empty tree** has a height of $-1$.
* **Subtree**: Given any node $a$ in a tree with root $r$, the collection of $a$ and all of its descendants is a subtree rooted at $a$.
* **Ordered vs. Unordered Trees**:
  * **Unordered Trees**: The order of children does not matter.
  * **Ordered Trees**: The order of children is relevant (most computer science applications use ordered trees).

---

## 2. Binary Trees and Classifications

A **Binary Tree** is a rooted tree where each node is restricted to having **at most two children**.
* Children are labeled as the **left subtree** and the **right subtree**.

### Types of Binary Trees

| Type | Definition | Key Formula / Property |
| :--- | :--- | :--- |
| **Perfect** | All levels are completely filled with no gaps. | A perfect binary tree of height $h$ contains exactly $2^{h+1} - 1$ nodes. |
| **Full** | Every node has either $0$ or $2$ children. No node has exactly $1$ child. | Used in expression trees and Huffman encoding. |
| **Complete** | All levels are completely filled except possibly the last, which is filled from left to right with no gaps. | Can be efficiently mapped to an array representation. |
| **Height-Balanced** | For every node, the height difference between its left and right subtrees is at most 1. | Guarantees $\Theta(\log n)$ search, insertion, and deletion times. |

### Full vs. Empty Nodes
* **Full Node**: A node whose left and right subtrees are both non-empty.
* **Empty Node (Null Subtree)**: Any location where a new leaf node could be appended (represented by `nullptr`).

---

## 3. C++ Class Implementation

Here is the C++ class template implementation matching the slide design.

### Binary Node Declaration (`Binary_node.h`)
```cpp
#pragma once
#include <algorithm>
#include <iostream>

template <typename Type>
class Binary_node {
protected:
    Type node_value;
    Binary_node *p_left_tree;
    Binary_node *p_right_tree;

public:
    // Constructor
    Binary_node(Type const &obj);

    // Accessors
    Type value() const;
    Binary_node *left() const;
    Binary_node *right() const;
    bool is_leaf() const;
    int size() const;
    int height() const;

    // Mutators (Helpers for building trees)
    void set_left(Binary_node *new_left);
    void set_right(Binary_node *new_right);

    // Memory clean up
    void clear(Binary_node *&p_to_this);
};
```

### Binary Node Implementation
```cpp
// Constructor
template <typename Type>
Binary_node<Type>::Binary_node(Type const &obj)
    : node_value(obj), p_left_tree(nullptr), p_right_tree(nullptr) {
    // Constructing a leaf node
}

// Accessors
template <typename Type>
Type Binary_node<Type>::value() const {
    return node_value;
}

template <typename Type>
Binary_node<Type> *Binary_node<Type>::left() const {
    return p_left_tree;
}

template <typename Type>
Binary_node<Type> *Binary_node<Type>::right() const {
    return p_right_tree;
}

template <typename Type>
bool Binary_node<Type>::is_leaf() const {
    return (p_left_tree == nullptr) && (p_right_tree == nullptr);
}

// Mutators
template <typename Type>
void Binary_node<Type>::set_left(Binary_node *new_left) {
    p_left_tree = new_left;
}

template <typename Type>
void Binary_node<Type>::set_right(Binary_node *new_right) {
    p_right_tree = new_right;
}

// Size function - Time: Theta(n), Space: Theta(h) recursion stack
template <typename Type>
int Binary_node<Type>::size() const {
    if (left() == nullptr) {
        return (right() == nullptr) ? 1 : 1 + right()->size();
    } else {
        return (right() == nullptr) ? 1 + left()->size() 
                                    : 1 + left()->size() + right()->size();
    }
}
```

> [!WARNING]
> ### ⚠️ Critical Bug in Lecture Slide height() Implementation
> The lecture slides contain a logical bug in the `height()` function for the case where both children are non-empty:
> ```cpp
> // BUGGED VERSION FROM SLIDES
> template <typename Type>
> int Binary_node<Type>::height() const {
>     if ( left() == nullptr ) {
>         return ( right() == nullptr ) ? 0 : 1 + right()->height();
>     } else {
>         return ( right() == nullptr ) ? 1 + left()->height() 
>                                       : 1 + left()->height() + right()->height(); // BUG! Adds left and right heights
>     }
> }
> ```
> Adding the heights of subtrees is mathematically incorrect. The correct height of a node with two children is $1 + \max(\text{height}(\text{left}), \text{height}(\text{right}))$.

#### Correct Height Implementation
```cpp
// Corrected Height - Time: Theta(n), Space: Theta(h)
template <typename Type>
int Binary_node<Type>::height() const {
    if (left() == nullptr) {
        return (right() == nullptr) ? 0 : 1 + right()->height();
    } else {
        return (right() == nullptr) ? 1 + left()->height() 
                                    : 1 + std::max(left()->height(), right()->height());
    }
}

// Clear function (recursive postorder deletion)
template <typename Type>
void Binary_node<Type>::clear(Binary_node *&p_to_this) {
    if (left() != nullptr) {
        left()->clear(p_left_tree);
    }
    if (right() != nullptr) {
        right()->clear(p_right_tree);
    }
    delete this;
    p_to_this = nullptr;
}
```

---

## 4. Tree Traversals

Traversing a tree means visiting every node exactly once. There are two primary types:

### A. Breadth-First Traversal (Level-Order)
* **Strategy**: Visit all nodes at depth $k$ before moving to depth $k+1$.
* **Data Structure**: Standard FIFO Queue (`std::queue`).
* **Complexities**:
  * **Time**: $\Theta(n)$ since each node is queued and dequeued once.
  * **Space**: $\Theta(w)$ where $w$ is the maximum width of the tree (max nodes at any depth). In the worst case (perfect tree), the queue holds up to $\lceil n/2 \rceil$ nodes at the leaf level.

```cpp
#include <queue>
#include <vector>

template <typename Type>
std::vector<Type> breadth_first_traversal(Binary_node<Type> *root) {
    std::vector<Type> result;
    if (root == nullptr) return result;

    std::queue<Binary_node<Type>*> q;
    q.push(root);

    while (!q.empty()) {
        Binary_node<Type> *current = q.front();
        q.pop();
        result.push_back(current->value());

        if (current->left() != nullptr) {
            q.push(current->left());
        }
        if (current->right() != nullptr) {
            q.push(current->right());
        }
    }
    return result;
}
```

### B. Depth-First Traversals (DFS)
Depth-First traversals go as deep as possible before backtracking.
* **Memory**: $\Theta(h)$ stack frames or stack elements.
* There are three orderings based on when the root node is visited relative to its subtrees:

| Traversal Type | Visit Order | Recursive Form | Typical Use Case |
| :--- | :--- | :--- | :--- |
| **Preorder** | Root $\rightarrow$ Left $\rightarrow$ Right | `visit(root); preorder(left); preorder(right);` | Copying a tree, serialization. |
| **Inorder** | Left $\rightarrow$ Root $\rightarrow$ Right | `inorder(left); visit(root); inorder(right);` | Sorted output on Binary Search Trees (BSTs). |
| **Postorder** | Left $\rightarrow$ Right $\rightarrow$ Root | `postorder(left); postorder(right); visit(root);` | Deletion (`clear`), Expression tree evaluation. |

#### Iterative DFS Implementations (Using `std::stack`)

To implement DFS iteratively, we use an explicit stack to mimic recursion:

##### 1. Iterative Preorder Traversal
```cpp
#include <stack>
#include <vector>

template <typename Type>
std::vector<Type> iterative_preorder(Binary_node<Type> *root) {
    std::vector<Type> result;
    if (root == nullptr) return result;

    std::stack<Binary_node<Type>*> s;
    s.push(root);

    while (!s.empty()) {
        Binary_node<Type> *curr = s.top();
        s.pop();
        result.push_back(curr->value());

        // Push right first so left is processed first (LIFO order)
        if (curr->right() != nullptr) s.push(curr->right());
        if (curr->left() != nullptr) s.push(curr->left());
    }
    return result;
}
```

##### 2. Iterative Inorder Traversal
```cpp
template <typename Type>
std::vector<Type> iterative_inorder(Binary_node<Type> *root) {
    std::vector<Type> result;
    std::stack<Binary_node<Type>*> s;
    Binary_node<Type> *curr = root;

    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left();
        }
        curr = s.top();
        s.pop();
        result.push_back(curr->value());
        curr = curr->right();
    }
    return result;
}
```

##### 3. Iterative Postorder Traversal (Two-Stack Method)
```cpp
template <typename Type>
std::vector<Type> iterative_postorder(Binary_node<Type> *root) {
    std::vector<Type> result;
    if (root == nullptr) return result;

    std::stack<Binary_node<Type>*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Binary_node<Type> *curr = s1.top();
        s1.pop();
        s2.push(curr);

        if (curr->left() != nullptr) s1.push(curr->left());
        if (curr->right() != nullptr) s1.push(curr->right());
    }

    while (!s2.empty()) {
        result.push_back(s2.top()->value());
        s2.pop();
    }
    return result;
}
```

---

## 5. Application: Expression Tree

An **Expression Tree** represents mathematical expressions containing binary operators.
* **Internal Nodes**: Store operators (e.g., `+`, `-`, `*`, `/`).
* **Leaf Nodes**: Store operands/literals or variables (e.g., `3`, `a`, `b`).
* **Property**: It is always a full binary tree (no node has exactly one child).
* **Non-Commutative Operators**: For operators like `-` and `/`, left/right child order determines the dividend/divisor or minuend/subtrahend.
  * Can also be represented using unary operations: $a - b = a + (-b)$ or $a / b = a \cdot b^{-1}$.

### Evaluation using Postorder Traversal
Evaluating an expression tree is a classic postorder depth-first traversal because we must evaluate both children (operands) before evaluating the root operator.

```cpp
#include <string>
#include <stdexcept>

struct ExpNode {
    std::string value; // Stores either operator "+", "-", "*", "/" or an integer like "5"
    ExpNode *left;
    ExpNode *right;

    ExpNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
    bool is_leaf() const { return left == nullptr && right == nullptr; }
};

int evaluate_expression_tree(ExpNode *root) {
    if (root == nullptr) return 0;

    // Base case: Leaf node stores a value
    if (root->is_leaf()) {
        return std::stoi(root->value);
    }

    // Postorder traversal: Evaluate subtrees first
    int left_val = evaluate_expression_tree(root->left);
    int right_val = evaluate_expression_tree(root->right);

    // Apply the operator at root
    if (root->value == "+") return left_val + right_val;
    if (root->value == "-") return left_val - right_val;
    if (root->value == "*") return left_val * right_val;
    if (root->value == "/") {
        if (right_val == 0) throw std::runtime_error("Division by zero!");
        return left_val / right_val;
    }
    throw std::invalid_argument("Unknown operator: " + root->value);
}
```

### Reverse Polish Notation (RPN / Postfix)
A postorder traversal on an expression tree yields its **Postfix** (Reverse-Polish) notation.
* For the expression tree representing: $3 \times (4 \times a + b + c) + d / 5 + (6 - e)$
* Postorder traversal yields the sequence:
  `3 4 a * b + c + * d 5 / + 6 e - +`

---

## 6. Time and Space Complexity Summary

| Operation | Best Case | Average Case | Worst Case (Skewed Tree) | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Size** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(h)$ recursion stack |
| **Height** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(h)$ recursion stack |
| **Clear** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(h)$ recursion stack |
| **Preorder DFS** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(h)$ stack |
| **Inorder DFS** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(h)$ stack |
| **Postorder DFS** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(h)$ stack |
| **Level Order BFS** | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(w)$ queue ($w = \text{width}$) |

---

## 7. LeetCode Practice Problems

This section details the solutions and conceptual rationales for advanced binary tree practice problems.

### Problem 1: Lowest Common Ancestor of a Binary Tree (LeetCode 236 - Medium)
* **File Link**: [no4_lca.cpp](../../leetcode/7_BINARY_TREE/no4_lca.cpp)
* **LeetCode Link**: [Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)
* **Core Concept**:
  The Lowest Common Ancestor (LCA) is the deepest node in the tree that has both target nodes $p$ and $q$ as descendants.
* **Algorithm Rationale**:
  Using a bottom-up postorder-like depth-first search (DFS):
  1. **Base Case**: If the current node is `nullptr`, or matches $p$, or matches $q$, return the current node.
  2. **Recurse**: Search the left and right subtrees.
  3. **Evaluate Results**:
     - If both left and right subtree searches return non-null, the current node is the LCA because $p$ and $q$ are split on different subtrees of the current node.
     - If only one child search returns non-null, return that non-null result (propagating the target node or the LCA up).
     - If both return `nullptr`, return `nullptr`.

#### C++ Solution Snippet
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;

    TreeNode* leftLCA = lowestCommonAncestor(root->left, p, q);
    TreeNode* rightLCA = lowestCommonAncestor(root->right, p, q);

    if (leftLCA != nullptr && rightLCA != nullptr) return root;
    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}
```

* **Complexities**:
  * **Time Complexity**: $\Theta(n)$ as every node may be visited in the worst case.
  * **Space Complexity**: $\Theta(h)$ stack frames for recursion stack where $h$ is the height of the tree.

---

### Problem 2: Serialize and Deserialize Binary Tree (LeetCode 297 - Hard)
* **File Link**: [no5_serialize.cpp](../../leetcode/7_BINARY_TREE/no5_serialize.cpp)
* **LeetCode Link**: [Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)
* **Core Concept**:
  Converting a binary tree structure into a flat string representation (serialization) and reconstructing the identical tree back from the string (deserialization).
* **Algorithm Rationale**:
  Preorder DFS traversal provides a highly deterministic ordering that encodes both parent-child relationships and null children:
  1. **Serialization**:
     - Perform a preorder traversal (Root $\rightarrow$ Left $\rightarrow$ Right).
     - If a node is `nullptr`, append a special sentinel character (e.g. `"#"`) followed by a delimiter (e.g. `","`).
     - Otherwise, append the node's integer value followed by the delimiter, and recurse on left and right children.
  2. **Deserialization**:
     - Split the serialized string by the delimiter and load all tokens into a queue.
     - Reconstruct the tree recursively using a preorder helper:
       - Pop a token from the queue.
       - If the token is the sentinel `"#"`, return `nullptr`.
       - Otherwise, create a new node with the value, and recursively assign its left and right children from subsequent queue states.

#### C++ Solution Snippet
```cpp
class Codec {
private:
    void serializeHelper(TreeNode* root, std::string& out) {
        if (root == nullptr) {
            out += "#,";
            return;
        }
        out += std::to_string(root->val) + ",";
        serializeHelper(root->left, out);
        serializeHelper(root->right, out);
    }

    TreeNode* deserializeHelper(std::queue<std::string>& q) {
        if (q.empty()) return nullptr;
        std::string val = q.front();
        q.pop();
        if (val == "#") return nullptr;

        TreeNode* node = new TreeNode(std::stoi(val));
        node->left = deserializeHelper(q);
        node->right = deserializeHelper(q);
        return node;
    }

public:
    std::string serialize(TreeNode* root) {
        std::string result = "";
        serializeHelper(root, result);
        return result;
    }

    TreeNode* deserialize(std::string data) {
        std::queue<std::string> q;
        std::stringstream ss(data);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (!token.empty()) q.push(token);
        }
        return deserializeHelper(q);
    }
};
```

* **Complexities**:
  * **Time Complexity**: $\Theta(n)$ for both processes, visiting each node or token exactly once.
  * **Space Complexity**: $\Theta(n)$ to store the serialized string/queue elements, and $\Theta(h)$ for recursion stack depth.

---

### Problem 3: Diameter of Binary Tree (LeetCode 543 - Easy)
* **File Link**: [no6_diameter_of_tree.cpp](../../leetcode/7_BINARY_TREE/no6_diameter_of_tree.cpp)
* **LeetCode Link**: [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)
* **Core Concept**:
  The diameter of a binary tree is the length of the longest path between any two nodes. This path does not necessarily need to pass through the root. The length of a path is measured by the number of edges.
* **Algorithm Rationale**:
  For any node in the tree, the longest path that has this node as its highest point (the turning point of the path) is the sum of the heights of its left and right subtrees.
  1. We perform a postorder-like DFS traversal where the helper function returns the height of the current node's subtree (defined as `1 + max(left_height, right_height)` where the height of `nullptr` is `0`).
  2. At each node, we calculate the path length passing through it: `left_height + right_height`.
  3. We maintain a global/member variable `max_diameter` and update it if the path length through the current node is greater than the current maximum.
  4. The function returns the height of the subtree to its parent node.

#### C++ Solution Snippet
```cpp
class Solution {
private:
    int max_diameter = 0;

    int calculateHeightAndDiameter(TreeNode* root) {
        if (root == nullptr) return 0;
        int leftHeight = calculateHeightAndDiameter(root->left);
        int rightHeight = calculateHeightAndDiameter(root->right);
        max_diameter = std::max(max_diameter, leftHeight + rightHeight);
        return 1 + std::max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        max_diameter = 0;
        calculateHeightAndDiameter(root);
        return max_diameter;
    }
};
```

* **Complexities**:
  * **Time Complexity**: $\Theta(n)$ since every node is visited exactly once.
  * **Space Complexity**: $\Theta(h)$ recursion stack space, where $h$ is the tree height.

---

### Problem 4: Path Sum (LeetCode 112 - Easy)
* **File Link**: [no7_path_sum.cpp](../../leetcode/7_BINARY_TREE/no7_path_sum.cpp)
* **LeetCode Link**: [Path Sum](https://leetcode.com/problems/path-sum/)
* **Core Concept**:
  Checking if there exists a root-to-leaf path in the binary tree where the sum of the values equals `targetSum`.
* **Algorithm Rationale**:
  We can solve this using recursion (preorder DFS):
  1. **Base Case**: If the current node is `nullptr`, return `false` because a null node cannot form a path.
  2. **Leaf Node Case**: If the current node has no children (is a leaf), check if its value matches the remaining `targetSum`.
  3. **Recursive Step**: For an internal node, recursively check if a path exists in the left or right subtree with the remaining sum: `targetSum - root->val`.

#### C++ Solution Snippet
```cpp
bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr) {
        return root->val == targetSum;
    }
    int remainingSum = targetSum - root->val;
    return hasPathSum(root->left, remainingSum) || hasPathSum(root->right, remainingSum);
}
```

* **Complexities**:
  * **Time Complexity**: $\Theta(n)$ as we may need to visit all nodes in the worst case.
  * **Space Complexity**: $\Theta(h)$ recursion stack space, where $h$ is the height of the tree.

