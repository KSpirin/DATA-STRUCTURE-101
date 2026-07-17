/**
 * @file no1_reverse_list.cpp
 * @brief LeetCode 206: Reverse Linked List
 * @difficulty Easy
 * @link https://leetcode.com/problems/reverse-linked-list/
 */

/*
Problem Description:
Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:
Input: head = [1,2]
Output: [2,1]

Example 3:
Input: head = []
Output: []
*/

#include <iostream>

// Definition for singly-linked list node (matching LeetCode's definition).
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
     * Reverses a singly linked list in-place.
     * @param head Pointer to the head of the linked list.
     * @return Pointer to the new head of the reversed list.
     */
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr; // Tracks the previously processed node (new successor)
        ListNode* curr = head;    // Tracks the node currently being processed

        while (curr != nullptr) {
            ListNode* nextNode = curr->next; // Temporarily save the next node
            curr->next = prev;               // Reverse the current node's pointer to point to prev
            prev = curr;                     // Move prev forward to the current node
            curr = nextNode;                 // Move curr forward to the saved next node
        }

        return prev; // At the end, prev points to the new head of the reversed list
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: head -> [1] -> [2] -> [3] -> nullptr

Initialization:
- prev = nullptr
- curr = head (points to [1])

Iteration 1 (curr != nullptr: curr points to [1]):
1. nextNode = curr->next  => nextNode points to [2]
2. curr->next = prev      => [1]->next = nullptr
3. prev = curr            => prev points to [1]
4. curr = nextNode        => curr points to [2]
List state: [1] -> nullptr

Iteration 2 (curr != nullptr: curr points to [2]):
1. nextNode = curr->next  => nextNode points to [3]
2. curr->next = prev      => [2]->next = [1]
3. prev = curr            => prev points to [2]
4. curr = nextNode        => curr points to [3]
List state: [2] -> [1] -> nullptr

Iteration 3 (curr != nullptr: curr points to [3]):
1. nextNode = curr->next  => nextNode points to nullptr
2. curr->next = prev      => [3]->next = [2]
3. prev = curr            => prev points to [3]
4. curr = nextNode        => curr points to nullptr
List state: [3] -> [2] -> [1] -> nullptr

Loop Terminates (curr == nullptr)
Return prev (points to [3])

Result: [3] -> [2] -> [1] -> nullptr

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N)
- We traverse the list exactly once, where N is the number of nodes in the list.
- Each step does constant time O(1) operations (pointer reassignments).

Space Complexity: O(1)
- We only use two auxiliary pointers (prev, nextNode), which consumes constant memory.
- In-place reversal does not allocate any new nodes.
*/
