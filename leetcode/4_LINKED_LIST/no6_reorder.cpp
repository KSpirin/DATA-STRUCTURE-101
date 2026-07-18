/**
 * @brief LeetCode 143 - Reorder List
 * @difficulty Medium
 * @link https://leetcode.com/problems/reorder-list/
 *
 * Problem:
 * Reorder L0->L1->...->Ln to L0->Ln->L1->Ln-1->L2->...
 * Modify in-place.
 * 
 * Example: 1->2->3->4 -> 1->4->2->3
 * 
 * Constraints: 1 <= nodes <= 5*10^4 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        // TODO: find mid, reverse second half, merge
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
        h->next=new ListNode(2); h->next->next=new ListNode(3); h->next->next->next=new ListNode(4);
        Solution().reorderList(h);
        // 1->2->3->4 becomes 1->4->2->3
        check(h->val==1 && h->next->val==4 && h->next->next->val==2 && h->next->next->next->val==3,
              "1-2-3-4 reordered to 1-4-2-3");
    }
    {
        ListNode* h2 = new ListNode(1);
        h2->next=new ListNode(2); h2->next->next=new ListNode(3);
        h2->next->next->next=new ListNode(4); h2->next->next->next->next=new ListNode(5);
        Solution().reorderList(h2);
        // 1->2->3->4->5 becomes 1->5->2->4->3
        check(h2->val==1 && h2->next->val==5 && h2->next->next->val==2,
              "1-2-3-4-5 reordered to 1-5-2-4-3");
    }
    {
        ListNode* h3 = new ListNode(1);
        Solution().reorderList(h3);
        check(h3->val==1 && h3->next==nullptr, "single node unchanged");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
