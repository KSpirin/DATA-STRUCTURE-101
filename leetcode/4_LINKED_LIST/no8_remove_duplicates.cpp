/**
 * @file no8_remove_duplicates.cpp
 * @brief LeetCode 83: Remove Duplicates from Sorted List
 * @difficulty Easy
 * @link https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 */

/*
Problem Description:
Given the head of a sorted linked list, delete all duplicates such that each element 
appears only once. Return the linked list sorted as well.

Example 1:
Input: head = [1,1,2]
Output: [1,2]

Example 2:
Input: head = [1,1,2,3,3]
Output: [1,2,3]
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
     * Deletes all duplicates from a sorted linked list in-place.
     * @param head Pointer to the head of the sorted linked list.
     * @return Pointer to the head of the modified list.
     */
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* curr = head; // Start pointer at the head of the list

        // Traverse the list until we reach the end or the last node
        while (curr != nullptr && curr->next != nullptr) {
            if (curr->val == curr->next->val) {
                // Duplicate found: link the current node to the node after the duplicate
                ListNode* temp = curr->next;
                curr->next = curr->next->next;
                delete temp; // Crucial: free memory for the deleted node to prevent memory leaks
            } else {
                // No duplicate: move the current pointer forward
                curr = curr->next;
            }
        }

        return head; // Return the head of the modified list
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: head -> [1] -> [1] -> [2] -> [3] -> [3] -> nullptr

Initialization:
- curr = head (points to first [1])

Iteration 1 (curr points to first [1], curr->next points to second [1]):
1. curr->val == curr->next->val (1 == 1) is true.
2. temp = curr->next (points to second [1])
3. curr->next = curr->next->next (first [1]->next now points to [2])
4. delete temp (second [1] is deallocated)
List state: head -> [1] -> [2] -> [3] -> [3] -> nullptr
curr still points to first [1]

Iteration 2 (curr points to first [1], curr->next points to [2]):
1. curr->val == curr->next->val (1 == 2) is false.
2. curr = curr->next (curr now points to [2])
List state: head -> [1] -> [2] -> [3] -> [3] -> nullptr

Iteration 3 (curr points to [2], curr->next points to first [3]):
1. curr->val == curr->next->val (2 == 3) is false.
2. curr = curr->next (curr now points to first [3])
List state: head -> [1] -> [2] -> [3] -> [3] -> nullptr

Iteration 4 (curr points to first [3], curr->next points to second [3]):
1. curr->val == curr->next->val (3 == 3) is true.
2. temp = curr->next (points to second [3])
3. curr->next = curr->next->next (first [3]->next now points to nullptr)
4. delete temp (second [3] deallocated)
List state: head -> [1] -> [2] -> [3] -> nullptr
curr still points to first [3]

Loop Terminates (curr->next == nullptr)
Return head (points to first [1])

Result: [1] -> [2] -> [3] -> nullptr

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N)
- We traverse the linked list of length N exactly once. 
- In each step, we either advance curr or bypass a duplicate node. Both operations are O(1).
- Total time complexity is linear in terms of the number of nodes.

Space Complexity: O(1)
- The deletion is performed in-place.
- Only a few local pointers (curr, temp) are used, resulting in constant auxiliary space.
*/
