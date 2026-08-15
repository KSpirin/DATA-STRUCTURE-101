/**
 * @brief LeetCode 141 - Linked List Cycle
 * @difficulty Easy
 * @link https://leetcode.com/problems/linked-list-cycle/
 *
 * Problem:
 * Return true if the linked list has a cycle. Use O(1) memory.
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
    bool hasCycle(ListNode* head) {
        // TODO (Floyd's tortoise & hare)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        ListNode* h = new ListNode(1); h->next = new ListNode(2);
        h->next->next = h;
        check(Solution().hasCycle(h) == true, "cycle -> true");
    }
    {
        ListNode* h2 = new ListNode(1); h2->next = new ListNode(2);
        check(Solution().hasCycle(h2) == false, "no cycle -> false");
    }
    {
        ListNode* h3 = new ListNode(1);
        check(Solution().hasCycle(h3) == false, "single node no cycle");
    }
    {
        check(Solution().hasCycle(nullptr) == false, "null -> false");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
