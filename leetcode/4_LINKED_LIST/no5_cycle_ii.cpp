/**
 * @file no5_list_cycle_ii.cpp
 * @brief LeetCode 142: Linked List Cycle II
 * @difficulty Medium
 * @link https://leetcode.com/problems/linked-list-cycle-ii/
 */

/*
Problem Description:
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously 
following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer 
is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.

Do not modify the linked list.

Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:
Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:
Input: head = [1], pos = -1
Output: no cycle
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
     * Finds the node where the cycle begins using Floyd's Cycle Detection Algorithm.
     * @param head Pointer to the head of the linked list.
     * @return Pointer to the node where the cycle starts, or nullptr if there is no cycle.
     */
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr; // No cycle possible if list has 0 or 1 node without a self-loop
        }

        ListNode* slow = head;
        ListNode* fast = head;

        // Step 1: Detect if a cycle exists.
        // slow moves 1 step, fast moves 2 steps.
        bool hasCycle = false;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break; // Meeting point found
            }
        }

        // If no cycle was detected, return nullptr
        if (!hasCycle) {
            return nullptr;
        }

        // Step 2: Find the start of the cycle.
        // Reset one pointer to the head of the list. Keep the other at the meeting point.
        // Move both pointers at the same speed (1 step at a time).
        // They will meet at the start of the cycle.
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow; // The node where they meet is the start of the cycle
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: head -> [3] -> [2] -> [0] -> [-4] -+
                       ^                  |
                       |                  | (cycle back to [2])
                       +------------------+
Pos index of cycle start = 1 (Node with value 2)

Step 1: Cycle Detection
- Initialization:
  slow = head (points to [3])
  fast = head (points to [3])

- Iteration 1:
  slow = slow->next => points to [2]
  fast = fast->next->next => points to [0]
  slow != fast ([2] != [0])

- Iteration 2:
  slow = slow->next => points to [0]
  fast = fast->next->next => points to [2] (from [0] -> [-4] -> [2])
  slow != fast ([0] != [2])

- Iteration 3:
  slow = slow->next => points to [-4]
  fast = fast->next->next => points to [-4] (from [2] -> [0] -> [-4])
  slow == fast (meeting point found at node with value -4)
  hasCycle = true

Step 2: Find Cycle Start Node
- Reset slow to head (points to [3])
- Keep fast at meeting point (points to [-4])

- Iteration 1:
  slow != fast ([3] != [-4])
  slow = slow->next => points to [2]
  fast = fast->next => points to [2] (from [-4] -> [2])

- Loop condition check:
  slow == fast ([2] == [2])
  Loop terminates.

- Return slow (points to Node with value 2)

Result: Node with value 2 is returned (correct cycle entry point).

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(N)
- Step 1: In the worst case, the slow pointer travels less than N steps (before meeting).
- Step 2: The distance from the head to the cycle start is L1, which is at most N. 
  Traversing this distance takes O(L1) <= O(N) steps.
- Total time complexity is O(N).

Space Complexity: O(1)
- Only two pointers (slow, fast) are used, which requires constant additional space.
- The algorithm does not allocate any new nodes or use recursion stacks.
*/
