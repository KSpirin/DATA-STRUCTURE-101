/**
 * @brief LeetCode 19 - Remove Nth Node From End
 * @difficulty Medium
 * @link https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 *
 * Problem:
 * Remove the nth node from the end of the list in one pass.
 * 
 * Example: 1->2->3->4->5, n=2 -> 1->2->3->5
 * 
 * Constraints: 1 <= n <= sz <= 30 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // TODO (two-pointer, one pass)
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
        for (int v : {2,3,4,5}) { ListNode* t=h; while(t->next) t=t->next; t->next=new ListNode(v); }
        ListNode* r = Solution().removeNthFromEnd(h, 2);
        // 1->2->3->4->5 remove 2nd from end (4) -> 1->2->3->5
        check(r->next->next->next->val==5, "remove 4 from 1-2-3-4-5");
    }
    {
        ListNode* h2 = new ListNode(1);
        ListNode* r2 = Solution().removeNthFromEnd(h2, 1);
        check(r2==nullptr, "remove only node -> null");
    }
    {
        ListNode* h3 = new ListNode(1); h3->next = new ListNode(2);
        ListNode* r3 = Solution().removeNthFromEnd(h3, 1);
        check(r3->val==1 && r3->next==nullptr, "remove last of [1,2]");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
