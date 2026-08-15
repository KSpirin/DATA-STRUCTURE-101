/**
 * @brief LeetCode 21 - Merge Two Sorted Lists
 * @difficulty Easy
 * @link https://leetcode.com/problems/merge-two-sorted-lists/
 *
 * Problem:
 * Merge two sorted linked lists into one sorted list.
 * 
 * Example: 1->2->4, 1->3->4 -> 1->1->2->3->4->4
 * 
 * Constraints: 0 <= nodes <= 50 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        ListNode* l1 = new ListNode(1); l1->next = new ListNode(2); l1->next->next = new ListNode(4);
        ListNode* l2 = new ListNode(1); l2->next = new ListNode(3); l2->next->next = new ListNode(4);
        ListNode* r = Solution().mergeTwoLists(l1, l2);
        check(r->val==1 && r->next->val==1 && r->next->next->val==2, "merge 1-2-4 and 1-3-4");
    }
    {
        ListNode* r2 = Solution().mergeTwoLists(nullptr, nullptr);
        check(r2==nullptr, "both null -> null");
    }
    {
        ListNode* l3 = nullptr;
        ListNode* l4 = new ListNode(5);
        ListNode* r3 = Solution().mergeTwoLists(l3, l4);
        check(r3->val==5, "merge null with [5] -> [5]");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
