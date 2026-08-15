# Study Guide: Linked Lists

## 1. Theoretical Concepts & Memory Analysis

### What is a Linked List?
A **Linked List** is a linear data structure where elements are not stored in contiguous memory locations. Instead, each element (called a **Node**) is a separate object that contains:
1. **Data**: The value stored in the node.
2. **Next Pointer**: A reference/pointer to the next node in the sequence.

Unlike arrays, which have fixed sizes (or require expensive reallocations in dynamic arrays), linked lists are dynamically allocated. This makes inserting or deleting elements highly efficient because we only need to adjust pointers rather than shifting elements.

```
[ Head ] -> [ Node 1: Value | Next ] -> [ Node 2: Value | Next ] -> [ Node 3: Value | nullptr ]
```

---

## 🎯 THE CORE
### Why use Linked Lists? (Comparison with Arrays)
In arrays, inserting or deleting elements at arbitrary positions requires shifting all elements after that position to maintain contiguity. This is an $O(N)$ operation. In a linked list, once the position is located, insertion or deletion is done in $O(1)$ time by rewiring pointers.

| Operation | Array / Dynamic Array | Singly Linked List | Doubly Linked List |
| :--- | :--- | :--- | :--- |
| **Access / Search** | $O(1)$ / $O(N)$ | $O(N)$ / $O(N)$ | $O(N)$ / $O(N)$ |
| **Insert / Delete at Front** | $O(N)$ (unless deque/circular) | $O(1)$ | $O(1)$ |
| **Insert / Delete at Back** | $O(1)$ amortized | $O(N)$ (without tail) / $O(1)$ (with tail) | $O(1)$ (with tail) |
| **Insert / Delete at Index** | $O(N)$ | $O(N)$ (due to search time) | $O(N)$ (due to search time) |
| **Memory Overhead** | Minimal (no pointer overhead) | High ($1$ pointer per node) | Very High ($2$ pointers per node) |

---

### Memory Calculations
A linked list uses **linked allocation**, which means nodes can reside anywhere in memory.
* **32-Bit System Pointer Size**: $4$ bytes
* **64-Bit System Pointer Size**: $8$ bytes

#### Node Memory Overhead Analysis:
Suppose we have a node storing an `int` ($4$ bytes) and a pointer to the next node:
* **On a 32-bit machine**:
  $$\text{Size of Node} = \text{sizeof(int)} + \text{sizeof(Node*)} = 4\text{ bytes} + 4\text{ bytes} = 8\text{ bytes}$$
* **On a 64-bit machine**:
  $$\text{Size of Node} = \text{sizeof(int)} + \text{sizeof(Node*)} = 4\text{ bytes} + 8\text{ bytes} = 12\text{ bytes}$$
  *Due to alignment restrictions on 64-bit architectures, structures are aligned to 8-byte boundaries. Thus, a node containing a $4$-byte `int` and an $8$-byte pointer is padded to **$16$ bytes** in memory (4 bytes int + 4 bytes padding + 8 bytes pointer).*

---

---

> 💡 **Bonus & Applications:** 
> The sections below contain supplementary materials, lab applications, C++ reference code, and LeetCode problems. You may skip this part if you are only reviewing core theory for the exam.

## 🛠️ THE BONUS

## 2. Templated Singly Linked List Implementation

Below is a complete, templated C++ implementation of a Singly Linked List with public/private separation, constructor, destructor, and safety checks.

```cpp
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    T value;
    Node* next;

    // Constructor matching slide details
    Node(const T& val) : value(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* list_head;
    size_t list_size;

public:
    // Constructor
    LinkedList() : list_head(nullptr), list_size(0) {}

    // Destructor (Crucial for preventing memory leaks)
    ~LinkedList() {
        clear();
    }

    // Check if list is empty
    bool isEmpty() const {
        return list_head == nullptr;
    }

    // Get current size of list
    size_t size() const {
        return list_size;
    }

    // Access the head node
    Node<T>* getHead() const {
        return list_head;
    }

    // Insert value at the front of the list
    void push_front(const T& value) {
        Node<T>* h = new Node<T>(value);
        h->next = list_head;
        list_head = h;
        list_size++;
    }

    // Remove the first node in the list
    void pop_front() {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        Node<T>* temp = list_head;
        list_head = list_head->next;
        delete temp;
        list_size--;
    }

    // Insert value at a specific position (1-based index as per typical teaching slide convention)
    void insert(size_t position, const T& value) {
        if (position < 1 || position > list_size + 1) {
            throw std::out_of_range("Invalid position");
        }
        if (position == 1) {
            push_front(value);
            return;
        }

        Node<T>* h = list_head;
        // Traverse to the node prior to the insertion point (position - 1)
        for (size_t ni = 1; ni < position - 1; ++ni) {
            h = h->next;
        }

        Node<T>* n = new Node<T>(value);
        n->next = h->next;
        h->next = n;
        list_size++;
    }

    // Erase a node at a specific position
    void erase(size_t position) {
        if (isEmpty()) {
            throw std::underflow_error("List is empty");
        }
        if (position < 1 || position > list_size) {
            throw std::out_of_range("Invalid position");
        }
        if (position == 1) {
            pop_front();
            return;
        }

        Node<T>* h = list_head;
        // Traverse to the node prior to the deletion point
        for (size_t ni = 1; ni < position - 1; ++ni) {
            h = h->next;
        }

        Node<T>* out = h->next;
        h->next = h->next->next;
        delete out;
        list_size--;
    }

    // Search for a value in the list, returning the node pointer
    Node<T>* search(const T& val) const {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next) {
            if (ptr->value == val) {
                return ptr;
            }
        }
        return nullptr;
    }

    // Clear list and release memory
    void clear() {
        while (!isEmpty()) {
            pop_front();
        }
    }

    // Traversal output
    void print() const {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next) {
            std::cout << ptr->value << " -> ";
        }
        std::cout << "NULL" << std::endl;
    }
};

#endif
```

---

## 3. Stack: Linked List Implementation

A **Stack** is a Last-In-First-Out (LIFO) data structure. We can implement a stack efficiently using a Singly Linked List where all operations occur at the **front** (head) of the list. This ensures that `push` and `pop` operations are both $O(1)$.

```cpp
#ifndef STACK_LIST_H
#define STACK_LIST_H

#include <stdexcept>

template <typename Type>
class Stack_list {
private:
    Node<Type>* list_head;
    size_t stack_size;

public:
    Stack_list() : list_head(nullptr), stack_size(0) {}

    ~Stack_list() {
        clear();
    }

    bool isEmpty() const {
        return list_head == nullptr;
    }

    size_t size() const {
        return stack_size;
    }

    // Push value to stack (push_front) - O(1)
    void push(const Type& value) {
        Node<Type>* h = new Node<Type>(value);
        h->next = list_head;
        list_head = h;
        stack_size++;
    }

    // Pop top value from stack (pop_front) - O(1)
    Type pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        Node<Type>* temp = list_head;
        Type val = temp->value;
        list_head = list_head->next;
        delete temp;
        stack_size--;
        return val;
    }

    // Get the top value - O(1)
    Type top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return list_head->value;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif
```

---

## 4. Queue: Linked List Implementation

A **Queue** is a First-In-First-Out (FIFO) data structure. To implement a queue using a linked list with $O(1)$ operations, we must maintain references to both the **front** (head) and the **rear** (tail) of the list:
* **Enqueue (push_back)**: Appends new elements to the tail pointer.
* **Dequeue (pop_front)**: Removes elements from the head pointer.

```cpp
#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include <stdexcept>

template <typename Type>
class Queue_list {
private:
    Node<Type>* list_head;
    Node<Type>* list_tail;
    size_t queue_size;

public:
    Queue_list() : list_head(nullptr), list_tail(nullptr), queue_size(0) {}

    ~Queue_list() {
        clear();
    }

    bool isEmpty() const {
        return list_head == nullptr;
    }

    size_t size() const {
        return queue_size;
    }

    // Enqueue: Append to back (push_back) - O(1)
    void enqueue(const Type& value) {
        Node<Type>* n = new Node<Type>(value);
        if (isEmpty()) {
            list_head = list_tail = n;
        } else {
            list_tail->next = n;
            list_tail = n;
        }
        queue_size++;
    }

    // Dequeue: Remove from front (pop_front) - O(1)
    Type dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        Node<Type>* temp = list_head;
        Type val = temp->value;
        list_head = list_head->next;
        if (list_head == nullptr) {
            list_tail = nullptr;
        }
        delete temp;
        queue_size--;
        return val;
    }

    // Get the front element - O(1)
    Type front() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return list_head->value;
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

#endif
```

---

## 5. Doubly Linked List

A **Doubly Linked List (DLL)** contains nodes that have pointers to both their successor (`next`) and predecessor (`prev`). This structure allows bidirectional traversal (forward and backward) and simplifies node deletion, as a node contains a reference to its predecessor directly.

```cpp
template <typename T>
class DoublyNode {
public:
    T value;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};
```

### Doubly Linked List Operations Diagram

#### 1. Inserting Node `N` (value 10) *after* Node `P` (value 4)
Before insertion:
```
  [ Node P (4) ] <===========> [ Node S (6) ]
```
Steps:
1. `N->next = P->next;`
2. `N->prev = P;`
3. `if (P->next != nullptr) P->next->prev = N;`
4. `P->next = N;`

After insertion:
```
  [ Node P (4) ] <===> [ Node N (10) ] <===> [ Node S (6) ]
```

#### 2. Inserting Node `N` (value 1) *before* Node `S` (value 3)
Before insertion:
```
  nullptr <=== [ Node S (3) ] <===========> [ Node B (4) ]
```
Steps:
1. `N->next = S;`
2. `N->prev = S->prev;`
3. `if (S->prev != nullptr) S->prev->next = N; else head = N;`
4. `S->prev = N;`

After insertion:
```
  nullptr <=== [ Node N (1) ] <===> [ Node S (3) ] <===> [ Node B (4) ]
```

---

## 6. LeetCode Practice Problems

This section catalogs the LeetCode practice problems implemented in the repository, organized by difficulty.

### Easy Problems

1. **Reverse Linked List** (LeetCode 206)
   - **File Link**: [no1_reverse.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no1_reverse.cpp)
   - **Code Reference**: [Solution::reverseList](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no1_reverse.cpp#L43)
   - **Concept**: Reversing pointer directions in a singly linked list in-place.
   - **Approach**: Iterates through the list using two pointers (`prev` and `curr`). At each step, it stores the next node, redirects `curr->next` to `prev`, then advances both `prev` and `curr`.
   - **Complexities**: Time: $\mathcal{O}(N)$, Space: $\mathcal{O}(1)$

2. **Merge Two Sorted Lists** (LeetCode 21)
   - **File Link**: [no2_merge.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no2_merge.cpp)
   - **Code Reference**: [Solution::mergeTwoLists](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no2_merge.cpp#L48)
   - **Concept**: Combining two sorted lists into a single sorted list.
   - **Approach**: Employs a dummy node to simplify edge cases. Iterates through both lists, comparison-splicing the smaller node to the tail of the merged list. Any remaining nodes from the non-exhausted list are appended at the end.
   - **Complexities**: Time: $\mathcal{O}(N + M)$, Space: $\mathcal{O}(1)$

3. **Linked List Cycle** (LeetCode 141)
   - **File Link**: [no3_cycle.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no3_cycle.cpp)
   - **Code Reference**: [Solution::hasCycle](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no3_cycle.cpp#L52)
   - **Concept**: Detecting cycle presence in a linked list.
   - **Approach**: Applies Floyd’s Cycle Detection (Tortoise and Hare). Uses two pointers, `slow` (moves 1 step) and `fast` (moves 2 steps). If they meet, a cycle exists. If `fast` or `fast->next` reaches `nullptr`, no cycle exists.
   - **Complexities**: Time: $\mathcal{O}(N)$, Space: $\mathcal{O}(1)$

4. **Remove Duplicates from Sorted List** (LeetCode 83)
   - **File Link**: [no8_remove_duplicates.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no8_remove_duplicates.cpp)
   - **Code Reference**: [Solution::deleteDuplicates](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no8_remove_duplicates.cpp#L39)
   - **Concept**: Removing contiguous duplicate values in-place from a sorted linked list.
   - **Approach**: Iterates through the list using a single pointer. If the current node's value equals the next node's value, we bypass the next node and deallocate its memory. Otherwise, we advance the pointer.
   - **Complexities**: Time: $\mathcal{O}(N)$, Space: $\mathcal{O}(1)$

---

### Medium Problems

5. **Remove Nth Node From End of List** (LeetCode 19)
   - **File Link**: [no4_remove_nth.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no4_remove_nth.cpp)
   - **Code Reference**: [Solution::removeNthFromEnd](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no4_remove_nth.cpp#L45)
   - **Concept**: Deleting the $N$-th node from the tail of a linked list in a single pass.
   - **Approach**: Uses two pointers separated by a window of size $N+1$ (created using a dummy node). Moving both pointers forward at the same speed preserves the relative distance. When the `fast` pointer reaches `nullptr`, the `slow` pointer points to the node *preceding* the target node, allowing for an $O(1)$ deletion.
   - **Complexities**: Time: $\mathcal{O}(N)$, Space: $\mathcal{O}(1)$

6. **Linked List Cycle II** (LeetCode 142)
   - **File Link**: [no5_cycle_ii.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no5_cycle_ii.cpp)
   - **Code Reference**: [Solution::detectCycle](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no5_cycle_ii.cpp#L48)
   - **Concept**: Locating the exact node where a cycle starts.
   - **Approach**: Uses Floyd's Cycle Detection Algorithm. First, detects if a cycle exists when the slow and fast pointers meet. If a cycle exists, the slow pointer is reset to the head while the fast pointer remains at the meeting point. Moving both pointers one step at a time guarantees they will meet exactly at the cycle's starting node.
   - **Complexities**: Time: $\mathcal{O}(N)$, Space: $\mathcal{O}(1)$

7. **Reorder List** (LeetCode 143)
   - **File Link**: [no6_reorder.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no6_reorder.cpp)
   - **Code Reference**: [Solution::reorderList](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no6_reorder.cpp#L32)
   - **Concept**: Reordering a list into an alternating $L_0 \rightarrow L_n \rightarrow L_1 \rightarrow L_{n-1} \dots$ pattern.
   - **Approach**: Divided into three steps:
     1. Find the middle of the list using slow/fast pointers.
     2. Split the list at the middle and reverse the second half in-place.
     3. Interleave the first half and the reversed second half using two pointers.
   - **Complexities**: Time: $\mathcal{O}(N)$, Space: $\mathcal{O}(1)$

8. **Add Two Numbers** (LeetCode 2)
   - **File Link**: [no7_add_two_numbers.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no7_add_two_numbers.cpp)
   - **Code Reference**: [Solution::addTwoNumbers](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/4_LINKED_LIST/no7_add_two_numbers.cpp#L44)
   - **Concept**: Adding two numbers represented as linked lists in reverse order.
   - **Approach**: Employs a dummy node and a traverse pointer to build the result list. Iterates through both lists simultaneously, computing the sum of digits and carry at each position. Creates a new node for the digit sum and carries over any overflow.
   - **Complexities**: Time: $\mathcal{O}(\max(N, M))$, Space: $\mathcal{O}(\max(N, M))$
