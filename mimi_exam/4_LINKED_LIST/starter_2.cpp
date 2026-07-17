#include <iostream>
#include <cassert>

// PROBLEM: LeetCode 142 - Linked List Cycle II
// Return the node where the cycle BEGINS (not just whether it exists).

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        // TODO:
        // Phase 1 - find meeting point
        //   slow = head, fast = head
        //   while fast && fast->next: slow = slow->next, fast = fast->next->next
        //     if slow == fast: break
        // Phase 2 - find cycle entry
        //   entry = head
        //   while entry != slow: entry = entry->next, slow = slow->next
        //   return entry
        // If no cycle: return nullptr

        return nullptr;
    }
};

int main() {
    ListNode* head = new ListNode(3);
    ListNode* cycle = new ListNode(2);
    head->next = cycle;
    cycle->next = new ListNode(0);
    cycle->next->next = new ListNode(-4);
    cycle->next->next->next = cycle;  // cycle starts at `cycle` node
    assert(Solution().detectCycle(head) == cycle);
    std::cout << "4_LINKED_LIST Coding 2 Passed!" << std::endl;
    return 0;
}
