#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// PROBLEM: LeetCode 23 - Merge k Sorted Lists
// Merge multiple sorted linked lists into one sorted list.

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct Comp {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;  // min-heap: smaller val = higher priority
    }
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // TODO:
        // 1. Push all non-null list heads into priority_queue<ListNode*, vector<ListNode*>, Comp>
        // 2. Create dummy node, curr = &dummy
        // 3. While heap not empty:
        //    - Pop min node, attach to curr->next, move curr forward
        //    - If popped node has next, push it into heap
        // 4. Return dummy.next

        return nullptr;
    }
};

int main() {
    ListNode* l1 = new ListNode(1); l1->next = new ListNode(4);
    ListNode* l2 = new ListNode(2); l2->next = new ListNode(5);
    std::vector<ListNode*> lists = {l1, l2};
    ListNode* res = Solution().mergeKLists(lists);
    assert(res->val == 1 && res->next->val == 2 && res->next->next->val == 4);
    std::cout << "4_LINKED_LIST Coding 3 Passed!" << std::endl;
    return 0;
}
