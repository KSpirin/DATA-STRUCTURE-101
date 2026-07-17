/**
 * @file no2_merge_sorted_lists.cpp
 * @brief LeetCode 21: Merge Two Sorted Lists
 * @difficulty Easy
 * @link https://leetcode.com/problems/merge-two-sorted-lists/
 */

/*
Problem Description:
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

Example 1:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:
Input: list1 = [], list2 = []
Output: []

Example 3:
Input: list1 = [], list2 = [0]
Output: [0]
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
     * Merges two sorted lists into one sorted list using a dummy node.
     * @param list1 Head pointer of the first sorted list.
     * @param list2 Head pointer of the second sorted list.
     * @return Head pointer of the merged sorted list.
     */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Dummy node acts as a placeholder to simplify tail appending
        ListNode dummy(0);
        ListNode* tail = &dummy;

        // Traverse both lists until one is exhausted
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;   // Link the smaller node from list1
                list1 = list1->next;  // Advance list1 pointer
            } else {
                tail->next = list2;   // Link the smaller node from list2
                list2 = list2->next;  // Advance list2 pointer
            }
            tail = tail->next;        // Advance the tail pointer of merged list
        }

        // Splicing the remaining nodes of the non-empty list (guard clause/efficiency)
        if (list1 != nullptr) {
            tail->next = list1;
        } else {
            tail->next = list2;
        }

        // Return the actual head of the merged list (skip dummy node)
        return dummy.next;
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: list1 = [1, 2, 4], list2 = [1, 3, 4]

Initialization:
- dummy.val = 0, dummy.next = nullptr
- tail = &dummy

Loop Iteration 1:
- Compare list1->val (1) and list2->val (1)
- Since list1->val <= list2->val:
  - tail->next = list1  (dummy.next points to [1_from_list1])
  - list1 = list1->next (list1 now points to [2])
- tail = tail->next     (tail now points to [1_from_list1])

Loop Iteration 2:
- Compare list1->val (2) and list2->val (1)
- Since list2->val < list1->val:
  - tail->next = list2  ([1_from_list1]->next points to [1_from_list2])
  - list2 = list2->next (list2 now points to [3])
- tail = tail->next     (tail now points to [1_from_list2])

Loop Iteration 3:
- Compare list1->val (2) and list2->val (3)
- Since list1->val <= list2->val:
  - tail->next = list1  ([1_from_list2]->next points to [2])
  - list1 = list1->next (list1 now points to [4])
- tail = tail->next     (tail now points to [2])

Loop Iteration 4:
- Compare list1->val (4) and list2->val (3)
- Since list2->val < list1->val:
  - tail->next = list2  ([2]->next points to [3])
  - list2 = list2->next (list2 now points to [4])
- tail = tail->next     (tail now points to [3])

Loop Iteration 5:
- Compare list1->val (4) and list2->val (4)
- Since list1->val <= list2->val:
  - tail->next = list1  ([3]->next points to [4_from_list1])
  - list1 = list1->next (list1 now points to nullptr)
- tail = tail->next     (tail now points to [4_from_list1])

Loop terminates since list1 == nullptr.

Post-Loop Link:
- Since list1 is nullptr, tail->next = list2 (links the remaining [4_from_list2] to the tail).

Return:
- dummy.next (points to [1_from_list1] -> [1_from_list2] -> [2] -> [3] -> [4_from_list1] -> [4_from_list2])

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N + M)
- Where N and M are the sizes of list1 and list2, respectively.
- We traverse each node of both lists at most once.

Space Complexity: O(1)
- The algorithm uses O(1) auxiliary space as it re-links existing nodes rather than allocating new ones.
*/
