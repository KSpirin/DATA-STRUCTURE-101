/**
 * @brief LeetCode 2 - Add Two Numbers
 * @difficulty Medium
 * @link https://leetcode.com/problems/add-two-numbers/
 *
 * Problem:
 * Two linked lists represent integers in reverse order. Add them.
 * 
 * Example: (2->4->3) + (5->6->4) = 7->0->8  (342+465=807)
 * 
 * Constraints: 1 <= nodes <= 100 */

#include <iostream>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // TODO (simulate addition with carry)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        ListNode* l1 = new ListNode(2); l1->next=new ListNode(4); l1->next->next=new ListNode(3);
        ListNode* l2 = new ListNode(5); l2->next=new ListNode(6); l2->next->next=new ListNode(4);
        ListNode* r = Solution().addTwoNumbers(l1, l2);
        check(r->val==7 && r->next->val==0 && r->next->next->val==8, "342+465=807");
    }
    {
        ListNode* l3 = new ListNode(0);
        ListNode* l4 = new ListNode(0);
        ListNode* r2 = Solution().addTwoNumbers(l3, l4);
        check(r2->val==0, "0+0=0");
    }
    {
        // 9999999 + 9999 = 10009998 -> 8,9,9,0,0,1
        ListNode* l5 = new ListNode(9); l5->next=new ListNode(9); l5->next->next=new ListNode(9);
        l5->next->next->next=new ListNode(9); l5->next->next->next->next=new ListNode(9);
        l5->next->next->next->next->next=new ListNode(9); l5->next->next->next->next->next->next=new ListNode(9);
        ListNode* l6 = new ListNode(9); l6->next=new ListNode(9); l6->next->next=new ListNode(9); l6->next->next->next=new ListNode(9);
        ListNode* r3 = Solution().addTwoNumbers(l5, l6);
        check(r3->val==8, "9999999+9999 last digit=8");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
