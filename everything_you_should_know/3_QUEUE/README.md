# 📘 Bible of Data Structures: Queue Module

Welcome to the ultimate guide on the **Queue** data structure. This document serves as a comprehensive study reference, combining rigorous computer science theory, mathematical models, practical memory layouts, and professional C++ implementations.

---

## 1. Theoretical Foundations

### 1.1 What is a Queue?
A **Queue** is a linear data structure that operates on the **FIFO (First-In, First-Out)** principle. This means that the first element added to the queue will be the first one to be removed. It mimics real-world queues (lines), such as customers waiting at a grocery store checkout or a bank teller.

```
       Incoming Elements (Enqueue) 
             │
             ▼
      ┌──────┬──────┬──────┬──────┐
Rear  │  99  │  42  │  17  │  13  │  Front
      └──────┴──────┴──────┴──────┘
                               │
                               ▼
                        Outgoing Elements (Dequeue)
```

### 1.2 Core Operations
*   **Enqueue (Push)**: Inserts an element at the end of the queue (the `rear` or `tail`).
*   **Dequeue (Pop)**: Removes and returns the element from the front of the queue (the `front` or `head`).
*   **Front/Peek**: Returns the element at the front of the queue without removing it.
*   **IsEmpty**: Checks whether the queue contains any elements.
*   **IsFull**: Checks whether the queue has reached its maximum capacity (applicable to fixed-size array implementations).

### 1.3 Complexity Analysis

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :--- | :--- | :--- |
| **Enqueue** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Inserting an element at the rear index. |
| **Dequeue** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Removing an element from the front index. |
| **Peek / Front** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Directly accessing the element at the front index. |
| **IsEmpty / IsFull** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Simple pointer comparison or counter check. |
| **Total Space** | — | $\mathcal{O}(N)$ | Linear space proportional to the maximum capacity $N$. |

---

## 2. Array-Based Implementations

### 2.1 The Simple Array-Based Queue (1-Indexed Slide Model)
In a basic array-based implementation, we maintain two pointer indices, `front` and `rear`, along with a fixed maximum `size` and an `Array` buffer.

Following the slide architecture, here is the class layout:
```cpp
class Queue {
 public:
  int Array[6];
  int size = 4;
  int front = 1;
  int rear = 0;
  
  bool empty();
  bool full();
  void enqueue(int data);
  int dequeue();
};
```

#### Key Mechanics of the Simple Queue:
*   **Initial State**: `front = 1`, `rear = 0`. The condition `front > rear` evaluates to `true`, indicating the queue is empty.
*   **Enqueueing**:
    1. Check if the queue is full (`rear == size`).
    2. If not full, increment `rear` (`rear++`).
    3. Write the data: `Array[rear] = data`.
*   **Dequeuing**:
    1. Check if the queue is empty (`front > rear`).
    2. If not empty, read the data at the front index: `temp = Array[front]`.
    3. Increment `front` (`front++`).
    4. Return `temp`.

#### ⚠️ The Critical Limitation: Rightward Drift
In this simple array implementation, both `front` and `rear` only move forward (to the right). 
*   If we enqueue 4 elements, `rear` reaches `size` (4). The queue is now **full** (`rear == size`).
*   If we then dequeue all 4 elements, `front` becomes 5. The queue is now **empty** (`front > rear`).
*   However, we cannot enqueue any more elements because `rear` remains at 4. The space at indices 1, 2, 3, and 4 is completely wasted! This phenomenon is known as **Rightward Drift** or **Memory Exhaustion**.

---

### 2.2 The Circular Array-Based Queue
To solve Rightward Drift, we view the array indices as a cyclic ring. When an index increments past the last position, it wraps around to `0`.

```
          [0]
        /     \
      [5]     [1]   <-- Cyclic Index wrapping
       |       |        Index = (Index + 1) % Capacity
      [4]     [2]
        \     /
          [3]
```

#### Index Wrapping Arithmetic
Instead of performing standard increments, we use modulo arithmetic:
$$\text{Next Index} = (\text{Current Index} + 1) \pmod{\text{Capacity}}$$

In C++, this can be written as:
```cpp
iback = (iback + 1) % capacity;
```

#### Empty vs. Full Ambiguity
If we allow the queue to store elements in all positions of the array, both an **empty** queue and a **full** queue will satisfy `front == rear`. To resolve this, we can use two different design strategies:

##### Strategy A: Leave One Slot Empty (The Slide Method)
Under this strategy, we define the queue as "full" when the slot immediately following the `rear` is the `front`. Thus, we can store at most `SIZE - 1` elements in an array of size `SIZE`.

According to **Page 25 of the lecture notes**, the queue is full under two distinct index states:
*   **Case 1**: `FRONT == 0 && REAR == SIZE - 1` (The queue starts at the beginning, and `rear` is at the very end).
*   **Case 2**: `FRONT == REAR + 1` (The `rear` has wrapped around and is immediately behind the `front`).

Using modulo math, these two cases are unified into a single elegant expression:
$$\text{IsFull} \iff (\text{rear} + 1) \pmod{\text{size}} == \text{front}$$

The queue is empty if:
$$\text{IsEmpty} \iff \text{front} == \text{rear}$$

##### Strategy B: Track Size Explicitly (The Count Method)
Alternatively, we can maintain an explicit `count` variable tracking the current number of elements:
*   `IsEmpty` $\iff \text{count} == 0$
*   `IsFull` $\iff \text{count} == \text{capacity}$
*   This approach allows us to use all `capacity` slots in the array.

---

## 3. Complete Templated C++ Implementations

Here are production-ready, templated implementations of both the Simple Queue and the Circular Queue, fully adhering to C++ best practices.

### 3.1 Simple Queue (Slide Model)
[SimpleQueue Implementation](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/everything_you_should_know/3_QUEUE/README.md#L143-L200)

```cpp
#include <iostream>
#include <stdexcept>

template <typename T, size_t Capacity>
class SimpleQueue {
private:
    T Array[Capacity + 2]; // Buffer matching the slide's index offsets safely
    size_t size;
    size_t front;
    size_t rear;

public:
    SimpleQueue() : size(Capacity), front(1), rear(0) {}

    bool empty() const {
        return front > rear;
    }

    bool full() const {
        return rear == size;
    }

    void enqueue(const T& data) {
        if (full()) {
            throw std::overflow_error("Queue Overflow: Capacity limit reached due to Rightward Drift.");
        }
        rear++;
        Array[rear] = data;
    }

    T dequeue() {
        if (empty()) {
            throw std::underflow_error("Queue Underflow: Queue is empty.");
        }
        T temp = Array[front];
        front++;
        return temp;
    }

    T peek() const {
        if (empty()) {
            throw std::underflow_error("Queue is empty.");
        }
        return Array[front];
    }
};
```

### 3.2 Circular Queue (Strategy A - Leaving One Slot Empty)
[CircularQueue Implementation](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/everything_you_should_know/3_QUEUE/README.md#L202-L269)

```cpp
template <typename T, size_t Size>
class CircularQueue {
private:
    T Array[Size];
    size_t front;
    size_t rear;

public:
    CircularQueue() : front(0), rear(0) {}

    bool empty() const {
        return front == rear;
    }

    bool full() const {
        // Case 1: FRONT == 0 && REAR == SIZE - 1
        // Case 2: FRONT == REAR + 1
        // Unified mathematically: (rear + 1) % Size == front
        return (rear + 1) % Size == front;
    }

    void enqueue(const T& data) {
        if (full()) {
            throw std::overflow_error("Circular Queue Overflow: Buffer is full.");
        }
        Array[rear] = data;
        rear = (rear + 1) % Size;
    }

    T dequeue() {
        if (empty()) {
            throw std::underflow_error("Circular Queue Underflow: Buffer is empty.");
        }
        T temp = Array[front];
        front = (front + 1) % Size;
        return temp;
    }

    T peek() const {
        if (empty()) {
            throw std::underflow_error("Circular Queue is empty.");
        }
        return Array[front];
    }
    
    size_t get_size() const {
        if (rear >= front) {
            return rear - front;
        }
        return Size - (front - rear);
    }
};
```

---

## 4. Real-World Applications

### 4.1 Client-Server Systems
Queues are fundamental in scheduling requests asynchronously:
*   **Network Request Processing**: Shared computer services (Web, File, Database, Mail, Printers) utilize queues to handle incoming client traffic in a orderly FIFO manner.
*   **Secure Session Protocols**: SFTP and SSH clients submit commands and files which are queued and processed sequentially by the server.

### 4.2 Uniprocessor CPU Scheduling
Operating Systems manage running threads/processes using queue structures:
*   **FCFS (First-Come, First-Served)**: Simple FIFO process execution.
*   **Round-Robin (RR)**: Each process is placed in a circular queue and runs for a small time slice ($q$). When the time slice expires, it is dequeued and enqueued at the tail to wait for its next turn.

### 4.3 Breadth-First Traversal of a Directory Tree
When searching directory structures, a queue is used to process directories level-by-level (breadth-first) rather than descending immediately down one path (depth-first).

#### The BFS Algorithm:
1. Place the root directory into a queue.
2. While the queue is not empty:
   *   Pop the directory at the front of the queue.
   *   Push all of its sub-directories into the queue.
3. The directories emerge from the queue in exact breadth-first order.

#### Walkthrough Example (from Lecture Notes):
Let's trace a directory structure where `A` has children `B` and `H`; `B` has children `C`, `D`, and `G`; `H` has child `I`; `D` has children `E` and `F`; `I` has children `J` and `K`.

| Step | Action | Queue State (Front ➔ Rear) | Output Traversal |
| :--- | :--- | :--- | :--- |
| **0** | Initial State | `[ A ]` | — |
| **1** | Pop A, Push B, H | `[ B, H ]` | **A** |
| **2** | Pop B, Push C, D, G | `[ H, C, D, G ]` | A, **B** |
| **3** | Pop H, Push I | `[ C, D, G, I ]` | A, B, **H** |
| **4** | Pop C, Push None | `[ D, G, I ]` | A, B, H, **C** |
| **5** | Pop D, Push E, F | `[ G, I, E, F ]` | A, B, H, C, **D** |
| **6** | Pop G, Push None | `[ I, E, F ]` | A, B, H, C, D, **G** |
| **7** | Pop I, Push J, K | `[ E, F, J, K ]` | A, B, H, C, D, G, **I** |
| **8** | Pop E, Push None | `[ F, J, K ]` | A, B, H, C, D, G, I, **E** |
| **9** | Pop F, Push None | `[ J, K ]` | A, B, H, C, D, G, I, E, **F** |
| **10** | Pop J, Push None | `[ K ]` | A, B, H, C, D, G, I, E, F, **J** |
| **11** | Pop K, Push None | `[ ]` (Empty) | A, B, H, C, D, G, I, E, F, J, **K** |

Final Breadth-First Order: **`A B H C D G I E F J K`**

---

## 5. Standard Template Library (STL) Queue

The C++ Standard Library provides `std::queue` via the `<queue>` header. It is a container adapter, typically wrapping a `std::deque` or `std::list`.

```cpp
#include <iostream>
#include <queue> // Include queue header

int main() {
    std::queue<int> iqueue;

    // Enqueue elements
    iqueue.push(13);
    iqueue.push(42);

    // Access front element
    std::cout << "Head: " << iqueue.front() << std::endl; // Output: 13

    // Dequeue elements (Note: pop does not return a value)
    iqueue.pop(); 

    // Access new front
    std::cout << "Head: " << iqueue.front() << std::endl; // Output: 42
    std::cout << "Size: " << iqueue.size() << std::endl;   // Output: 1

    return 0;
}
```

---

## 6. LeetCode Practice Problems

This section catalogs the LeetCode practice problems implemented in the repository, organized by difficulty.

### Easy Problems

1. **Number of Recent Calls** (LeetCode 933)
   - **File Link**: [no3_warshall.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no3_recent.cpp)
   - **Concept**: Tracking events in a fixed time window.
   - **Approach**: Uses a standard FIFO queue. Every time a new request arrives, we push it to the queue and pop any older requests that fall outside the 3000ms window limit.
   - **Complexities**: Time: $\mathcal{O}(1)$ amortized per ping, Space: $\mathcal{O}(W)$ where $W$ is the maximum number of requests in the window.

---

### Medium Problems

2. **Design Circular Queue** (LeetCode 622)
   - **File Link**: [no1_islands.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no1_circular_queue.cpp)
   - **Concept**: Implementing a queue in a fixed-size array without memory drift.
   - **Approach**: Uses two pointers (`head` and `tail`) with cyclic modulo indexing: `(tail + 1) % capacity`. It tracks whether the queue is empty or full using special value flags (`head == -1` or pointer equations).
   - **Complexities**: Time: $\mathcal{O}(1)$ for all operations, Space: $\mathcal{O}(K)$ for the underlying array of capacity $K$.

3. **Implement Stack using Queues** (LeetCode 225)
   - **File Link**: [no2_course.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no2_stack_queue.cpp)
   - **Concept**: Emulating LIFO behavior using FIFO queues.
   - **Approach**: Can be implemented using either two queues (where one acts as a buffer) or a single queue. With a single queue, when we push a new element, we enqueue it and then rotate the queue by popping all previously existing elements from the front and enqueuing them back to the rear, reversing their order.
   - **Complexities**: Time: $\mathcal{O}(N)$ for `push`, $\mathcal{O}(1)$ for `pop`/`top` (single queue approach), Space: $\mathcal{O}(N)$ total space.

4. **Shortest Path in Binary Matrix** (LeetCode 1091)
   - **File Link**: [no5_redundant.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no5_shortest_path.cpp)
   - **Code Reference**: [Solution::shortestPathBinaryMatrix](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no5_shortest_path.cpp#L46)
   - **Concept**: Shortest path in an unweighted grid with 8-directional movement.
   - **Approach**: Employs Breadth-First Search (BFS) starting from the top-left cell `(0, 0)`. BFS uses a queue to visit cells level-by-level, ensuring that the first time we reach the bottom-right cell `(n - 1, n - 1)`, it is guaranteed to be the shortest path. We mark cells as visited (e.g., by changing their value to 1 in-place) before pushing them to the queue to avoid duplicate visits.
   - **Complexities**: Time: $\mathcal{O}(N^2)$ to visit each cell in an $N \times N$ grid, Space: $\mathcal{O}(N^2)$ in the worst case for the queue.

5. **Rotting Oranges** (LeetCode 994)
   - **File Link**: [no6_rotting_oranges.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no6_rotting_oranges.cpp)
   - **Code Reference**: [Solution::orangesRotting](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no6_rotting_oranges.cpp#L53)
   - **Concept**: Multi-source Breadth-First Search (BFS) in a grid.
   - **Approach**: Simulated as a BFS starting with all initially rotten oranges in a queue. We track the number of fresh oranges and decrement it as they rot. Every minute, we process all rotten oranges at the current queue level, spreading the rot to their 4-directional fresh neighbors.
   - **Complexities**: Time: $\mathcal{O}(M \times N)$ where $M$ is the number of rows and $N$ is the number of columns, Space: $\mathcal{O}(M \times N)$ in the worst case for the queue.

6. **Dota2 Senate** (LeetCode 649)
   - **File Link**: [no7_dota2_senate.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no7_dota2_senate.cpp)
   - **Code Reference**: [Solution::predictPartySenate](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no7_dota2_senate.cpp#L63)
   - **Concept**: Round-based greedy simulation using FIFO queues.
   - **Approach**: Maintain two queues storing the voting indices of Radiant and Dire senators respectively. In each turn, compare the indices at the front of both queues. The senator with the smaller index bans the opponent, and is re-enqueued for the next round with their index incremented by $N$.
   - **Complexities**: Time: $\mathcal{O}(N)$ where $N$ is the senate length, Space: $\mathcal{O}(N)$ for the two queues.

---

### Hard Problems

7. **Sliding Window Maximum** (LeetCode 239)
   - **File Link**: [no4_clone.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no4_sliding_max.cpp)
   - **Code Reference**: [Solution::maxSlidingWindow](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/3_QUEUE/no4_sliding_max.cpp#L44)
   - **Concept**: Finding the maximum value in a moving subarray of size $K$.
   - **Approach**: Uses a Monotonic Deque (double-ended queue) to store indices of elements in the array.
     - **Monotonicity**: The deque is maintained such that the values corresponding to indices in the deque are in strictly decreasing order. When processing a new element `nums[i]`, we pop all indices from the back of the deque whose values are less than or equal to `nums[i]`.
     - **Window Bound**: We pop indices from the front of the deque if they are out of the current sliding window range `[i - k + 1, i]`.
     - **Result**: The index at the front of the deque always represents the maximum element of the current window.
   - **Complexities**: Time: $\mathcal{O}(N)$ since each element index is pushed to and popped from the deque at most once, Space: $\mathcal{O}(K)$ for the deque storing at most $K$ indices.

---
*Developed as part of the Bible of Data Structures study guides.*
