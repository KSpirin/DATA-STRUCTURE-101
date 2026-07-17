/**
 * @file no4_remove_nth_node.cpp
 * @brief LeetCode 19: Remove Nth Node From End of List
 * @difficulty Medium
 * @link https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 */

/*
Problem Description:
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Example 1:
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]
*/

#include <iostream>

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    /**
     * Removes the N-th node from the end of a singly linked list.
     * Uses a dummy node and two-pointer (fast/slow) sliding window approach.
     * @param head Pointer to the head of the linked list.
     * @param n The position of the node to remove, counting from the end.
     * @return Pointer to the head of the modified linked list.
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0); // Dummy node to simplify edge cases (e.g. removing the head)
        dummy.next = head;

        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Move fast pointer n + 1 steps forward to create a gap of size n between slow and fast
        for (int i = 0; i <= n; ++i) {
            fast = fast->next;
        }

        // Move both pointers forward until fast reaches the end (nullptr)
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        // slow->next is the node to delete.
        ListNode* nodeToDelete = slow->next;
        slow->next = slow->next->next; // Bypass the node to delete
        delete nodeToDelete;            // Free memory of deleted node (crucial for C++!)

        return dummy.next; // Return the actual head
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: head = [1, 2, 3, 4, 5], n = 2

Initialization:
- dummy.val = 0, dummy.next = head
- slow = &dummy (points to 0)
- fast = &dummy (points to 0)

1. Move fast pointer n + 1 (3) steps forward:
- Step 1: fast points to [1]
- Step 2: fast points to [2]
- Step 3: fast points to [3]
Now, slow points to 0, fast points to [3]. The distance between them is 3.

2. Move both slow and fast pointers until fast is nullptr:
- Iteration 1:
  - slow points to [1]
  - fast points to [4]
- Iteration 2:
  - slow points to [2]
  - fast points to [5]
- Iteration 3:
  - slow points to [3]
  - fast points to nullptr
Loop terminates.

3. Re-link pointers to remove the node:
- slow points to [3]. slow->next points to [4] (node to delete).
- nodeToDelete = slow->next (points to [4])
- slow->next = slow->next->next (makes [3]->next point to [5])
- delete nodeToDelete (deletes [4] from heap memory)

Return:
- dummy.next (points to [1] -> [2] -> [3] -> [5])

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N)
- We traverse the list with the fast pointer exactly once.
- Since it runs in a single pass, it is highly optimized.

Space Complexity: O(1)
- Only a constant number of extra pointers (fast, slow, dummy, nodeToDelete) are used.
- Modifies the list structure in-place.
*/
