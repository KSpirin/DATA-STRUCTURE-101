#include <iostream>
#include <cassert>

// PROBLEM: LeetCode 92 - Reverse Linked List II
// Reverse nodes from position `left` to position `right`.
// iteratively "pick up" nodes and move them to front of sublist.

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // TODO:
        // 1. Create a dummy node pointing to head
        // 2. Walk `prev` pointer to node just BEFORE position `left`
        // 3. For (right - left) times:
        //    - Pick up curr->next, insert it AFTER prev
        // 4. Return dummy.next

        return head;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    // 1->2->3->4, reverse positions 2..4 => 1->4->3->2
    ListNode* res = Solution().reverseBetween(head, 2, 4);
    assert(res->val == 1);
    assert(res->next->val == 4);
    assert(res->next->next->val == 3);
    std::cout << "4_LINKED_LIST Coding 1 Passed!" << std::endl;
    return 0;
}
