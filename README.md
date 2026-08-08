# The Bible of Data Structures

A personal study repository covering the complete **Data Structures & Algorithms** curriculum in C++.
Built to score 100/100 — and structured to be useful for anyone learning the same topics.

> **Weekly update**: Solutions to mock coding challenges are pushed every week so you can follow the learning path over time.
> 
> **Maintenance Note:** Currently reviewing and updating quizzes/theory for topics 6-10. Topics 1-5 have been fully verified.

---

## Interactive Quiz Portal

**-> [Open Quiz Portal](https://kspirin.github.io/DATA-STRUCTURE-101/mimi_exam/quiz/)** — 300 multiple choice questions across all 10 topics, runs in the browser, instant answer checking.

> _Why "mimi"? it's not a typo — it's just my thing_ 

---

## What's inside

| Folder | Contents |
|--------|----------|
| `everything_you_should_know/` | Deep theory guides + complexity tables for each topic |
| `leetcode/` | Blank starter files for LeetCode problems — implement, then run the built-in test cases |
| `mimi_exam/` | 30 LeetCode-style coding challenges (3 per topic) with blank starter files _(yes, "mimi" not "mini" — intentional)_ |
| `solution/` | Weekly-pushed solutions to the coding challenges |

---

## Topics

| # | Topic | Theory | LeetCode Solutions | Mock Challenges |
|---|-------|--------|-------------------|-----------------|
| 01 | C++ Basics & Memory | [Guide](everything_you_should_know/1_CPP/README.md) | [5 problems](leetcode/1_CPP/) | [3 challenges](mimi_exam/1_CPP/) |
| 02 | Stack | [Guide](everything_you_should_know/2_STACK/README.md) | [7 problems](leetcode/2_STACK/) | [3 challenges](mimi_exam/2_STACK/) |
| 03 | Queue | [Guide](everything_you_should_know/3_QUEUE/README.md) | [7 problems](leetcode/3_QUEUE/) | [3 challenges](mimi_exam/3_QUEUE/) |
| 04 | Linked List | [Guide](everything_you_should_know/4_LINKED_LIST/README.md) | [8 problems](leetcode/4_LINKED_LIST/) | [3 challenges](mimi_exam/4_LINKED_LIST/) |
| 05 | Hash Table | [Guide](everything_you_should_know/5_HASH/README.md) | [7 problems](leetcode/5_HASH/) | [3 challenges](mimi_exam/5_HASH/) |
| 06 | Heap / Priority Queue | [Guide](everything_you_should_know/6_HEAP/README.md) | [7 problems](leetcode/6_HEAP/) | [3 challenges](mimi_exam/6_HEAP/) |
| 07 | Binary Tree | [Guide](everything_you_should_know/7_BINARY_TREE/README.md) | [7 problems](leetcode/7_BINARY_TREE/) | [3 challenges](mimi_exam/7_BINARY_TREE/) |
| 08 | Binary Search Tree | [Guide](everything_you_should_know/8_BST/README.md) | [7 problems](leetcode/8_BST/) | [3 challenges](mimi_exam/8_BST/) |
| 09 | AVL Tree | [Guide](everything_you_should_know/9_AVL/README.md) | [5 problems](leetcode/9_AVL/) | [3 challenges](mimi_exam/9_AVL/) |
| 10 | Graph (BFS / DFS / Dijkstra / DSU) | [Guide](everything_you_should_know/10_GRAPH/README.md) | [8 problems](leetcode/10_GRAPH/) | [3 challenges](mimi_exam/10_GRAPH/) |

---

## Mock Exam Format

Each challenge in `mimi_exam/` follows the LeetCode problem structure:

```
mimi_exam/
 2_STACK/
 question_1.md problem statement + examples + constraints
 starter_1.cpp blank skeleton with numbered // TODO comments
 question_2.md
 starter_2.cpp
 ...
```

`solution/` is updated weekly as problems get solved.

---

## Running any C++ file

```bash
# macOS (clang++ is default)
clang++ -std=c++17 filename.cpp -o out && ./out

# or with g++
g++ -std=c++17 -Wall filename.cpp -o out && ./out
```

---

## Key concepts at a glance

| Data Structure | Insert | Delete | Search | Space |
|----------------|--------|--------|--------|-------|
| Stack (array) | O(1) | O(1) | O(n) | O(n) |
| Queue (circular array) | O(1) | O(1) | O(n) | O(n) |
| Singly Linked List | O(1) head | O(n) tail | O(n) | O(n) |
| Hash Table (avg) | O(1) | O(1) | O(1) | O(n) |
| Binary Heap | O(log n) | O(log n) | O(n) | O(n) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(n) |
| AVL Tree | O(log n) | O(log n) | O(log n) | O(n) |
| Graph BFS/DFS | — | — | O(V+E) | O(V+E) |

---

## Tips

- **Dry-run on paper first** — stacks, queues, AVL rotations, and Dijkstra all appear as trace questions in exams.
- **Memorize the 3 BST deletion cases** and the 4 AVL rotation cases (LL, RR, LR, RL).
- **Floyd's cycle detection** (tortoise & hare) shows up constantly — know it cold.
- Build and run every file locally. No IDE required:
 ```bash
 clang++ -std=c++17 starter_1.cpp -o test && ./test
 ```

---

*Started: July 2026 — updated weekly with new solutions.*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) [![GitHub](https://img.shields.io/badge/GitHub-KSpirin%2FDATA--STRUCTURE--101-181717?logo=github)](https://github.com/KSpirin/DATA-STRUCTURE-101)
