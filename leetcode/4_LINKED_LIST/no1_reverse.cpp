/**
 * @brief LeetCode 206 - Reverse Linked List
 * @difficulty Easy
 * @link https://leetcode.com/problems/reverse-linked-list/
 *
 * Problem:
 * Reverse a singly linked list.
 * 
 * Example: 1->2->3->4->5 -> 5->4->3->2->1
 * 
 * Constraints: 0 <= nodes <= 5000 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
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
        ListNode* h = new ListNode(1);
        h->next = new ListNode(2); h->next->next = new ListNode(3);
        ListNode* r = Solution().reverseList(h);
        check(r->val==3 && r->next->val==2 && r->next->next->val==1, "1->2->3 reversed");
    }
    {
        ListNode* h2 = new ListNode(1);
        h2->next = new ListNode(2);
        ListNode* r2 = Solution().reverseList(h2);
        check(r2->val==2 && r2->next->val==1, "1->2 reversed");
    }
    {
        ListNode* h3 = new ListNode(42);
        ListNode* r3 = Solution().reverseList(h3);
        check(r3->val==42, "single node unchanged");
    }
    {
        ListNode* r4 = Solution().reverseList(nullptr);
        check(r4==nullptr, "null input -> null");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
