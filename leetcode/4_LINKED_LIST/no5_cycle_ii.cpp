/**
 * @brief LeetCode 142 - Linked List Cycle II
 * @difficulty Medium
 * @link https://leetcode.com/problems/linked-list-cycle-ii/
 *
 * Problem:
 * Return the node where the cycle begins. nullptr if no cycle. O(1) memory.
 * 
 * Constraints: 0 <= nodes <= 10^4 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        // TODO (Floyd's two-phase)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        ListNode* h = new ListNode(3);
        ListNode* cycle = new ListNode(2);
        h->next = cycle; cycle->next = new ListNode(0);
        cycle->next->next = new ListNode(-4);
        cycle->next->next->next = cycle;
        check(Solution().detectCycle(h) == cycle, "cycle start at node(2)");
    }
    {
        ListNode* h2 = new ListNode(1); ListNode* n2 = new ListNode(2);
        h2->next = n2; n2->next = h2;
        check(Solution().detectCycle(h2) == h2, "cycle at head");
    }
    {
        ListNode* h3 = new ListNode(1);
        check(Solution().detectCycle(h3) == nullptr, "no cycle -> null");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
