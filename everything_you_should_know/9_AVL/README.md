# AVL Trees - The Complete Guide

An **AVL Tree** (named after its inventors **Adelson-Velskii and Landis**) is a self-balancing Binary Search Tree (BST). It is the first dynamically balanced data structure ever proposed. 

---

## 1. Theoretical Foundations & Height Balance Property

In a standard Binary Search Tree (BST), the efficiency of operations such as search, insertion, and deletion is highly dependent on the tree's height. In the worst-case scenario (e.g., inserting sorted keys), a BST degrades into a linear linked list with a height of $O(N)$, resulting in $O(N)$ operation times.

To prevent this, AVL trees introduce a **height balance condition**:
> For every node in the tree, the height of its left and right subtrees can differ by at most **1**.

### Definitions and Conventions
- **Height of a Node ($H$)**: The length of the longest path from that node to a leaf.
  - The height of a leaf node is defined as **$0$**.
  - The height of an empty tree (null pointer) is defined as **$-1$**.
  - The height of a node with children is calculated as:
    $$\text{Height}(t) = 1 + \max(\text{Height}(t.left), \text{Height}(t.right))$$
- **Balance Factor ($BF$)**: 
  Based on the lecture slides:
  $$\text{Balance Factor (BF)} = \text{Height}(t.left) - \text{Height}(t.right)$$
  - For an AVL tree, the value of the balance factor for every node must belong to the set:
    $$\text{BF} \in \{-1, 0, +1\}$$
  - If at any point the balance factor becomes $\ge 2$ or $\le -2$, the node is **unbalanced** and requires **rebalancing** (rotation).

---

## 2. The Four Imbalance Cases & Rotations

When we insert or delete a node in an AVL tree, the heights of the subtrees change. If this causes a node $\alpha$ to have $|BF| = 2$, we must restore the balance. There are exactly four cases of imbalance, classified by the path from the unbalanced ancestor $\alpha$ to the newly inserted node.

| Imbalance Case | Location of Insertion | Type of Rotation to Fix | Balance Factor of $\alpha$ | Balance Factor of Child |
| :--- | :--- | :--- | :---: | :---: |
| **Case 1: Left-Left (LL)** | Left subtree of the left child of $\alpha$ | **Single Right Rotation** | $+2$ | $\ge 0$ (typically $+1$) |
| **Case 2: Left-Right (LR)** | Right subtree of the left child of $\alpha$ | **Double Left-Right Rotation** | $+2$ | $< 0$ (typically $-1$) |
| **Case 3: Right-Left (RL)** | Left subtree of the right child of $\alpha$ | **Double Right-Left Rotation** | $-2$ | $> 0$ (typically $+1$) |
| **Case 4: Right-Right (RR)** | Right subtree of the right child of $\alpha$ | **Single Left Rotation** | $-2$ | $\le 0$ (typically $-1$) |

> [!NOTE]
> - **"Outside" cases** (LL and RR) are resolved with a **single rotation**.
> - **"Inside" cases** (LR and RL) are resolved with a **double rotation**.

---

### Case 1: Single Right Rotation (LL Imbalance)

An insertion into the left subtree of the left child of $\alpha$ causes $\alpha$ to become unbalanced. We rotate the tree to the right around $\alpha$ (which is $k_2$ in the diagram).

#### Visual Representation:
```text
       k2 (+2)                    k1 (0)
      /   \                      /  \
    k1     Z                    X    k2 (0)
   /  \         =======>       /    /  \
  X    Y                      W    Y    Z
 /
W
```
- **Process**:
  1. Let $k_1$ be the left child of $k_2$.
  2. Make $k_1$'s right child ($Y$) the new left child of $k_2$.
  3. Make $k_2$ the right child of $k_1$.
  4. Update the heights of $k_2$ and $k_1$.

---

### Case 4: Single Left Rotation (RR Imbalance)

An insertion into the right subtree of the right child of $\alpha$ (which is $k_1$ in the diagram) causes it to become unbalanced. We rotate the tree to the left around $k_1$.

#### Visual Representation:
```text
    k1 (-2)                       k2 (0)
   /   \                         /  \
  X     k2                      k1   Z
       /  \      =======>      /  \   \
      Y    Z                  X    Y   W
            \
             W
```
- **Process**:
  1. Let $k_2$ be the right child of $k_1$.
  2. Make $k_2$'s left child ($Y$) the new right child of $k_1$.
  3. Make $k_1$ the left child of $k_2$.
  4. Update the heights of $k_1$ and $k_2$.

---

### Case 2: Double Left-Right Rotation (LR Imbalance)

An insertion into the right subtree of the left child of $k_3$ causes it to become unbalanced. A single rotation is not sufficient because the middle element needs to become the new root. We perform a left rotation on the left child ($k_1$), converting the problem into a Left-Left (LL) case, and then perform a right rotation on $k_3$.

#### Visual Representation:
```text
       k3 (+2)                  k3 (+2)                  k2 (0)
      /   \                    /   \                    /  \
    k1     D   Rotate Left   k2     D   Rotate Right  k1    k3
   /  \        =========>   /  \        =========>   / \   / \
  A    k2                  k1   C                   A   B C   D
      /  \                /  \
     B    C              A    B
```
- **Process**:
  1. Left-rotate around the left child ($k_1$).
  2. Right-rotate around the root ($k_3$).

---

### Case 3: Double Right-Left Rotation (RL Imbalance)

An insertion into the left subtree of the right child of $k_1$ causes it to become unbalanced. We perform a right rotation on the right child ($k_3$), converting the problem into a Right-Right (RR) case, and then perform a left rotation on $k_1$.

#### Visual Representation:
```text
    k1 (-2)                  k1 (-2)                  k2 (0)
   /   \                    /   \                    /  \
  A     k3   Rotate Right  A     k2    Rotate Left  k1    k3
       /  \  ===========>       /  \   =========>  / \   / \
      k2   D                   B    k3            A   B C   D
     /  \                            \
    B    C                            C
```
- **Process**:
  1. Right-rotate around the right child ($k_3$).
  2. Left-rotate around the root ($k_1$).

---

## 3. Rebalancing Algorithm (Insert & Delete)

Rebalancing is applied bottom-up as the recursion unwinds. After modifying a node's subtree:
1. Update the height of the current node.
2. Check the balance factor.
3. If $BF > 1$ (Left-heavy):
   - If $BF(\text{left child}) \ge 0$, perform **Right Rotation** (LL Case).
   - If $BF(\text{left child}) < 0$, perform **Left-Right Double Rotation** (LR Case).
4. If $BF < -1$ (Right-heavy):
   - If $BF(\text{right child}) \le 0$, perform **Left Rotation** (RR Case).
   - If $BF(\text{right child}) > 0$, perform **Right-Left Double Rotation** (RL Case).

### Deletion vs. Insertion
- **Insertion**: At most **one** single or double rotation is needed to restore balance to the entire tree. Once a sub-tree is rebalanced, its height matches what it was before insertion, meaning no further ancestors require rebalancing.
- **Deletion**: Restoring balance at a node can decrease its height, which might propagate the imbalance upward. Thus, we may need to perform rotations at multiple ancestors up to the root, resulting in a worst-case of $O(\log N)$ rotations.

---

## 4. Complexity Analysis

| Operation | Average Case | Worst Case | Space Complexity |
| :--- | :---: | :---: | :---: |
| **Search** | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ (call stack) |
| **Insertion** | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ (call stack) |
| **Deletion** | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ (call stack) |

- **Height Limit**: An AVL tree with $N$ nodes has a maximum height of approximately $1.44 \log_2(N + 2) - 1.328$. This is strictly bounded compared to red-black trees, which can have heights up to $2 \log_2(N + 1)$. Consequently, AVL trees provide faster lookups but slightly slower modifications due to more frequent rotations.

---

## 5. LeetCode Practice & Verification

The following code exercises verify the theoretical concepts and AVL balancing mechanisms through hands-on coding challenges:

### 1. [no1_avl.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp)
* **Goal**: Build a fully featured, self-balancing AVL Tree from scratch in C++.
* **Key Components**:
  - [AVLNode](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp#L29-L38): Struct representing a node containing value, left/right pointers, and height.
  - [AVLTree](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp#L41-L45): Templated class encapsulating balancing operations.
  - [rotateRight](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp#L76-L98) / [rotateLeft](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp#L100-L115): Implements single rotations to resolve LL/RR outside imbalances.
  - [doubleRotateLeftRight](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp#L124-L128) / [doubleRotateRightLeft](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no1_avl.cpp#L141-L145): Implements double rotations to resolve LR/RL inside imbalances.
* **Complexities**:
  - Time: $O(\log N)$ for `insert`, `remove`, and `search`.
  - Space: $O(N)$ total space, $O(\log N)$ stack frame depth.

### 2. [no2_array_to_bst.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no2_array_to_bst.cpp) (LeetCode 108 - Easy)
* **Goal**: Convert a sorted array into a height-balanced BST.
* **Core Idea**: Since the input is sorted, selecting the middle element of the array (or subarray) as the root recursively partitions the remaining elements into two equal (or almost equal) halves. This guarantees that the height difference between the left and right subtrees is at most $1$.
* **Complexities**:
  - Time: $O(N)$ since each element is processed exactly once to construct a node.
  - Space: $O(N)$ to build the tree, $O(\log N)$ recursive stack depth.

### 3. [no3_balanced.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no3_balanced.cpp) (LeetCode 110 - Easy)
* **Goal**: Validate whether a given binary tree matches the height-balanced definition (the same balance condition required by AVL trees).
* **Core Idea**: Performs a post-order traversal to calculate tree heights bottom-up. If any subtree is found to be unbalanced, it returns `-1` immediately, short-circuiting the recursion and avoiding unnecessary node visits.
* **Complexities**:
  - Time: $O(N)$ since every node is visited at most once.
  - Space: $O(H)$ where $H$ is the height of the tree (down to $O(\log N)$ if balanced, $O(N)$ if skewed).

### 4. [no4_balance_bst.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no4_balance_bst.cpp) (LeetCode 1382 - Medium)
* **Goal**: Transform any arbitrary (potentially highly unbalanced) BST into a height-balanced BST.
* **Core Idea**: This problem bridges the sorted property of BSTs and the balance properties of AVL trees. We perform an in-order traversal to flatten the tree into a sorted array of node pointers using [getInorderNodes](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no4_balance_bst.cpp#L40-L52). Then, we build a balanced tree structure from this array in-place using [buildBalancedBST](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no4_balance_bst.cpp#L62-L79). This avoids allocating new nodes or deleting old ones, achieving maximum efficiency.
* **Complexities**:
  - Time: $O(N)$ for both the in-order flattening and the divide-and-conquer tree reconstruction.
  - Space: $O(N)$ auxiliary space to store the node pointers, and $O(\log N)$ recursive stack depth.

### 5. [no5_sorted_list_to_bst.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/9_AVL/no5_sorted_list_to_bst.cpp) (LeetCode 109 - Medium)
* **Goal**: Convert a sorted singly linked list into a height-balanced BST.
* **Core Idea**: Instead of finding the middle element repeatedly using slow/fast pointers (which takes $O(N \log N)$ time), we simulate an in-order tree construction. Since the linked list is sorted, we can build the left subtree first, construct the root using the current list node's value, advance the list head pointer to the next element, and then construct the right subtree. This builds the balanced BST in a single linear pass.
* **Complexities**:
  - Time: $O(N)$ because each node in the list is visited exactly once.
  - Space: $O(\log N)$ auxiliary space for the recursive call stack (no extra array allocation required, unlike the $O(N)$ space array conversion approach).

