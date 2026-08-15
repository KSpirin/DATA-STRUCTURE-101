/**
 * @brief LeetCode 83 - Remove Duplicates from Sorted List
 * @difficulty Easy
 * @link https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 *
 * Problem:
 * Delete all duplicates from a sorted list so each element appears once.
 * 
 * Example: 1->1->2->3->3 -> 1->2->3
 * 
 * Constraints: 0 <= nodes <= 300 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
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
        ListNode* h = new ListNode(1); h->next=new ListNode(1); h->next->next=new ListNode(2);
        ListNode* r = Solution().deleteDuplicates(h);
        check(r->val==1 && r->next->val==2 && r->next->next==nullptr, "1-1-2 -> 1-2");
    }
    {
        ListNode* h2 = new ListNode(1); h2->next=new ListNode(1); h2->next->next=new ListNode(2);
        h2->next->next->next=new ListNode(3); h2->next->next->next->next=new ListNode(3);
        ListNode* r2 = Solution().deleteDuplicates(h2);
        check(r2->val==1 && r2->next->val==2 && r2->next->next->val==3 && r2->next->next->next==nullptr,
              "1-1-2-3-3 -> 1-2-3");
    }
    {
        ListNode* h3 = new ListNode(1);
        check(Solution().deleteDuplicates(h3)->val==1, "single node unchanged");
    }
    {
        check(Solution().deleteDuplicates(nullptr)==nullptr, "null -> null");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
