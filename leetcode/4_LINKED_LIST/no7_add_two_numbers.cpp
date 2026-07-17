/**
 * @file no7_add_two_numbers.cpp
 * @brief LeetCode 2: Add Two Numbers
 * @difficulty Medium
 * @link https://leetcode.com/problems/add-two-numbers/
 */

/*
Problem Description:
You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order, and each of their nodes contains a single digit. 
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example 1:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
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
     * Adds two numbers represented by linked lists in reverse order.
     * @param l1 Pointer to the head of the first list.
     * @param l2 Pointer to the head of the second list.
     * @return Pointer to the head of the sum linked list.
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);      // Dummy node to simplify head initialization
        ListNode* curr = &dummy; // Pointer to traverse and construct the result list
        int carry = 0;           // Variable to store the carry-over from addition

        // Loop as long as there is at least one digit remaining or a carry value exists
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int val1 = (l1 != nullptr) ? l1->val : 0; // Current digit from l1 or 0 if l1 is finished
            int val2 = (l2 != nullptr) ? l2->val : 0; // Current digit from l2 or 0 if l2 is finished

            // Compute sum of current digits and carry
            int sum = val1 + val2 + carry;
            carry = sum / 10;                     // Update carry for the next step
            
            // Create a new node with the digit part of the sum
            curr->next = new ListNode(sum % 10);
            curr = curr->next;                    // Advance result pointer

            // Advance inputs if they haven't reached the end
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }

        return dummy.next; // Return the first actual sum node
    }
};

/*
================================================================================
MANUAL DRY-RUN TRACE:
================================================================================
Input: 
- l1 -> [2] -> [4] -> [3] -> nullptr (represents 342)
- l2 -> [5] -> [6] -> [4] -> nullptr (represents 465)

Initialization:
- dummy = ListNode(0)
- curr = &dummy
- carry = 0

Iteration 1 (l1 points to [2], l2 points to [5], carry = 0):
1. val1 = l1->val = 2, val2 = l2->val = 5
2. sum = 2 + 5 + 0 = 7
3. carry = 7 / 10 = 0
4. curr->next = new ListNode(7 % 10) = new ListNode(7)
5. curr = curr->next (points to [7])
6. l1 = l1->next (points to [4]), l2 = l2->next (points to [6])
Result List state: dummy -> [7] -> nullptr

Iteration 2 (l1 points to [4], l2 points to [6], carry = 0):
1. val1 = l1->val = 4, val2 = l2->val = 6
2. sum = 4 + 6 + 0 = 10
3. carry = 10 / 10 = 1
4. curr->next = new ListNode(10 % 10) = new ListNode(0)
5. curr = curr->next (points to [0])
6. l1 = l1->next (points to [3]), l2 = l2->next (points to [4])
Result List state: dummy -> [7] -> [0] -> nullptr

Iteration 3 (l1 points to [3], l2 points to [4], carry = 1):
1. val1 = l1->val = 3, val2 = l2->val = 4
2. sum = 3 + 4 + 1 = 8
3. carry = 8 / 10 = 0
4. curr->next = new ListNode(8 % 10) = new ListNode(8)
5. curr = curr->next (points to [8])
6. l1 = l1->next (nullptr), l2 = l2->next (nullptr)
Result List state: dummy -> [7] -> [0] -> [8] -> nullptr

Loop Terminates (l1 == nullptr, l2 == nullptr, carry == 0)
Return dummy.next (points to [7])

Result: [7] -> [0] -> [8] -> nullptr (represents 807)

================================================================================
COMPLEXITY ANALYSIS:
================================================================================
Time Complexity: O(max(N, M))
- We traverse both lists once, where N is the length of l1 and M is the length of l2.
- The loop runs max(N, M) times. Each iteration takes O(1) time.

Space Complexity: O(max(N, M))
- The space complexity is O(max(N, M)) due to the creation of a new linked list 
  storing the result. The length of the new list is at most max(N, M) + 1.
- Auxiliary space (excluding the output list) is O(1).
*/
