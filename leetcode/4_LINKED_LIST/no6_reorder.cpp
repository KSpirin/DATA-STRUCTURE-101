/**
 * @file no6_reorder_list.cpp
 * @brief LeetCode 143: Reorder List
 * @difficulty Medium
 * @link https://leetcode.com/problems/reorder-list/
 */

/*
Problem Description:
You are given the head of a singly linked-list. The list can be represented as:
L0 → L1 → … → Ln - 1 → Ln

Reorder the list to be on the following form:
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …

You may not modify the values in the list's nodes. Only nodes themselves may be changed.

Example 1:
Input: head = [1,2,3,4]
Output: [1,4,2,3]

Example 2:
Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
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
     * Reorders the list in place to match the L0 -> Ln -> L1 -> Ln-1 -> ... pattern.
     * @param head Pointer to the head of the linked list.
     */
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return; // No reordering needed for 0, 1, or 2 nodes
        }

        // Step 1: Find the middle of the linked list.
        // slow will point to the end of the first half.
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Split the list and reverse the second half.
        // secondHalfHead starts right after slow.
        ListNode* secondHalfHead = slow->next;
        slow->next = nullptr; // Disconnect the first half from the second half

        ListNode* prev = nullptr;
        ListNode* curr = secondHalfHead;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        // prev now points to the head of the reversed second half

        // Step 3: Merge the two halves in an alternating fashion.
        ListNode* first = head;
        ListNode* second = prev;
        while (second != nullptr) {
            ListNode* tmp1 = first->next;
            ListNode* tmp2 = second->next;

            first->next = second;
            second->next = tmp1;

            first = tmp1;
            second = tmp2;
        }
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: head -> [1] -> [2] -> [3] -> [4] -> [5] -> nullptr

Step 1: Finding Middle
- Initialization:
  slow = [1]
  fast = [1]

- Loop Check: fast->next ([2]) != nullptr and fast->next->next ([3]) != nullptr
  slow = slow->next => [2]
  fast = fast->next->next => [3]

- Loop Check: fast->next ([4]) != nullptr and fast->next->next ([5]) != nullptr
  slow = slow->next => [3]
  fast = fast->next->next => [5]

- Loop Check: fast->next ([5]) != nullptr, but fast->next->next is nullptr.
  Loop terminates. Middle found. slow = [3].

Step 2: Splitting and Reversing Second Half
- secondHalfHead = slow->next => [4]
- slow->next = nullptr (List 1 is now: [1] -> [2] -> [3] -> nullptr)
- Reverse List 2: [4] -> [5] -> nullptr
  - Init: prev = nullptr, curr = [4]
  - Iteration 1:
    nextNode = [5]
    curr->next = nullptr
    prev = [4]
    curr = [5]
  - Iteration 2:
    nextNode = nullptr
    curr->next = [4]
    prev = [5]
    curr = nullptr
  Reversed second half: [5] -> [4] -> nullptr (headed by prev)

Step 3: Alternating Merge
- first = [1], second = [5]

- Iteration 1:
  tmp1 = first->next => [2]
  tmp2 = second->next => [4]
  first->next = second => [1]->next = [5] (List: [1] -> [5])
  second->next = tmp1 => [5]->next = [2] (List: [1] -> [5] -> [2])
  first = tmp1 => [2]
  second = tmp2 => [4]

- Iteration 2:
  tmp1 = first->next => [3]
  tmp2 = second->next => nullptr
  first->next = second => [2]->next = [4] (List: ... -> [2] -> [4])
  second->next = tmp1 => [4]->next = [3] (List: ... -> [2] -> [4] -> [3])
  first = tmp1 => [3]
  second = tmp2 => nullptr

- Loop condition check: second == nullptr.
  Loop terminates.

Final list configuration:
[1] -> [5] -> [2] -> [4] -> [3] -> nullptr

Result: List has been successfully reordered in-place.

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N)
- Step 1 (Finding middle): O(N) since we traverse the list with slow/fast pointers.
- Step 2 (Reversing second half): O(N) since we reverse N/2 nodes.
- Step 3 (Merging): O(N) since we merge two halves of size N/2.
- Total time complexity is O(N) + O(N) + O(N) = O(N).

Space Complexity: O(1)
- The reordering is done completely in-place by altering next pointers.
- Only a few auxiliary pointers (slow, fast, prev, curr, nextNode, tmp1, tmp2) are used.
- No recursion stacks or extra data structures are allocated.
*/
