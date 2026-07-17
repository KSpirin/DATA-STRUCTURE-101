/**
 * @file no3_list_cycle.cpp
 * @brief LeetCode 141: Linked List Cycle
 * @difficulty Easy
 * @link https://leetcode.com/problems/linked-list-cycle/
 */

/*
Problem Description:
Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again 
by continuously following the next pointer. Internally, pos is used to denote the index of 
the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).

Example 2:
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.

Example 3:
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
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
     * Detects if a linked list contains a cycle using Floyd's Cycle-Finding Algorithm.
     * @param head Pointer to the head of the linked list.
     * @return True if there is a cycle, false otherwise.
     */
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false; // Guard clause: 0 or 1 node lists cannot have cycles (without self-loops)
        }

        ListNode* slow = head; // Moves 1 step at a time
        ListNode* fast = head; // Moves 2 steps at a time

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;       // Slow pointer advances by 1
            fast = fast->next->next; // Fast pointer advances by 2

            if (slow == fast) {
                return true; // Cycle detected: slow and fast pointers met!
            }
        }

        return false; // Fast pointer reached the end: no cycle exists
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: head = [3, 2, 0, -4] with a cycle back to [2] (index 1)
Layout:
Node A (3) -> Node B (2) -> Node C (0) -> Node D (-4)
                 ^                           |
                 +---------------------------+

Initialization:
- slow = Node A (3)
- fast = Node A (3)

Iteration 1:
- slow = slow->next => Node B (2)
- fast = fast->next->next => Node C (0)
- Are they equal? Node B != Node C. Loop continues.

Iteration 2:
- slow = slow->next => Node C (0)
- fast = fast->next->next => Node B (2) (from C to D to B)
- Are they equal? Node C != Node B. Loop continues.

Iteration 3:
- slow = slow->next => Node D (-4)
- fast = fast->next->next => Node D (-4) (from B to C to D)
- Are they equal? Node D == Node D.
- slow == fast is true! Return true.

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N)
- If there is no cycle: The fast pointer reaches the end of the list in N/2 steps, so O(N).
- If there is a cycle: Once both pointers enter the cycle, they will meet. The distance between 
  them decreases by 1 in each step. If the cycle length is C and the non-cyclic part is K, 
  they meet in at most K + C steps, which is O(N) total time.

Space Complexity: O(1)
- We only track two node pointers (slow and fast), so memory usage is constant.
*/
