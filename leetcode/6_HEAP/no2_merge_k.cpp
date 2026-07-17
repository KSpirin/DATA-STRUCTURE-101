/**
 * @file no2_merge_k_sorted.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 23: Merge k Sorted Lists (Hard)
 * @link https://leetcode.com/problems/merge-k-sorted-lists/
 */

/*
Problem Description:
--------------------
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:
Input: lists = []
Output: []

Example 3:
Input: lists = [[]]
Output: []

Constraints:
- k == lists.length
- 0 <= k <= 10^4
- 0 <= lists[i].length <= 500
- -10^4 <= lists[i][j] <= 10^4
- lists[i] is sorted in ascending order.
- The sum of lists[i].length will not exceed 10^4.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Functor for min-heap comparison.
// Note: In C++ std::priority_queue, the default comparator is std::less (which forms a Max Heap).
// Providing a greater-than comparison (lhs->val > rhs->val) creates a Min Heap
// where the node with the smallest value is stored at the top.
struct CompareNodes {
    bool operator()(const ListNode* lhs, const ListNode* rhs) const {
        if (!lhs || !rhs) {
            throw std::invalid_argument("Cannot compare null pointers");
        }
        return lhs->val > rhs->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // Guard Clause: If input is empty, return nullptr
        if (lists.empty()) {
            return nullptr;
        }

        // Declare the min-heap containing ListNode pointers, using custom comparator
        std::priority_queue<ListNode*, std::vector<ListNode*>, CompareNodes> minHeap;

        // Push the head of each non-empty list into the min-heap
        for (ListNode* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }

        // Dummy head to simplify list construction
        ListNode dummy(0);
        ListNode* tail = &dummy;

        // Extract the smallest node from the heap, append it to result, and insert its next node
        while (!minHeap.empty()) {
            ListNode* minNode = minHeap.top();
            minHeap.pop();

            // Link the extracted node to the merged list
            tail->next = minNode;
            tail = tail->next;

            // If there's a subsequent node in the extracted node's list, push it to heap
            if (minNode->next != nullptr) {
                minHeap.push(minNode->next);
            }
        }

        return dummy.next;
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE
======================================================================
Input: lists = [L1, L2, L3]
L1: 1 -> 4 -> 5
L2: 1 -> 3 -> 4
L3: 2 -> 6

Initialization:
- Push heads of lists to minHeap:
  - L1 head: 1 (from list 1)
  - L2 head: 1 (from list 2)
  - L3 head: 2 (from list 3)
  - minHeap holds: [1(L1), 1(L2), 2(L3)] (Heap top is L1's 1 or L2's 1)
- dummy list pointer: tail -> dummy(0)

Iteration Trace:
----------------------------------------------------------------------
1. Pop minNode = 1 (from L1). Heap holds: [1(L2), 2(L3)].
   - tail->next = 1(L1). tail moves to 1(L1).
   - Push minNode->next (4 from L1) to heap.
   - Heap holds: [1(L2), 2(L3), 4(L1)].

2. Pop minNode = 1 (from L2). Heap holds: [2(L3), 4(L1)].
   - tail->next = 1(L2). tail moves to 1(L2).
   - Push minNode->next (3 from L2) to heap.
   - Heap holds: [2(L3), 3(L2), 4(L1)].

3. Pop minNode = 2 (from L3). Heap holds: [3(L2), 4(L1)].
   - tail->next = 2(L3). tail moves to 2(L3).
   - Push minNode->next (6 from L3) to heap.
   - Heap holds: [3(L2), 4(L1), 6(L3)].

4. Pop minNode = 3 (from L2). Heap holds: [4(L1), 6(L3)].
   - tail->next = 3(L2). tail moves to 3(L2).
   - Push minNode->next (4 from L2) to heap.
   - Heap holds: [4(L1), 4(L2), 6(L3)].

5. Pop minNode = 4 (from L1). Heap holds: [4(L2), 6(L3)].
   - tail->next = 4(L1). tail moves to 4(L1).
   - Push minNode->next (5 from L1) to heap.
   - Heap holds: [4(L2), 5(L1), 6(L3)].

6. Pop minNode = 4 (from L2). Heap holds: [5(L1), 6(L3)].
   - tail->next = 4(L2). tail moves to 4(L2).
   - L2 list is exhausted (next is nullptr). No push.
   - Heap holds: [5(L1), 6(L3)].

7. Pop minNode = 5 (from L1). Heap holds: [6(L3)].
   - tail->next = 5(L1). tail moves to 5(L1).
   - L1 list is exhausted. No push.
   - Heap holds: [6(L3)].

8. Pop minNode = 6 (from L3). Heap holds: [].
   - tail->next = 6(L3). tail moves to 6(L3).
   - L3 list is exhausted. No push.
   - Heap is empty. Loop terminates.

Result List: dummy.next -> 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6 (Correct!)

======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity:
- Let N be the total number of nodes across all k lists.
- Each node is pushed into the heap and popped from the heap exactly once.
- The size of the heap is at most k (one element from each list).
- Thus, each push and pop operation takes O(log k) time.
- Total Time Complexity: O(N log k).

Space Complexity:
- The heap stores at most k nodes at any given time.
- Total Space Complexity: O(k) auxiliary space for the min-heap.
*/

// Helper function to build a linked list from a vector
ListNode* buildList(const std::vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int val : vals) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    return dummy.next;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << (head->next ? " -> " : "");
        head = head->next;
    }
    std::cout << std::endl;
}

// Helper function to delete list memory
void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Solution solver;
    std::vector<ListNode*> lists;
    
    // Lists to merge: [[1,4,5], [1,3,4], [2,6]]
    lists.push_back(buildList({1, 4, 5}));
    lists.push_back(buildList({1, 3, 4}));
    lists.push_back(buildList({2, 6}));

    std::cout << "Input lists:" << std::endl;
    for (size_t i = 0; i < lists.size(); ++i) {
        std::cout << "List " << i + 1 << ": ";
        printList(lists[i]);
    }

    ListNode* merged = solver.mergeKLists(lists);

    std::cout << "\nMerged list: ";
    printList(merged);

    // Cleanup memory
    freeList(merged);

    return 0;
}
