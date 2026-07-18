/**
 * @brief LeetCode 23 - Merge k Sorted Lists
 * @difficulty Hard
 * @link https://leetcode.com/problems/merge-k-sorted-lists/
 *
 * Problem:
 * Merge an array of k sorted linked lists into one sorted list.
 * 
 * Example: [1->4->5, 1->3->4, 2->6] -> 1->1->2->3->4->4->5->6
 * 
 * Constraints: k == lists.length, 0 <= k <= 10^4 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <string>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // TODO (min-heap)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        ListNode* l1 = new ListNode(1); l1->next = new ListNode(4); l1->next->next = new ListNode(5);
        ListNode* l2 = new ListNode(1); l2->next = new ListNode(3); l2->next->next = new ListNode(4);
        ListNode* l3 = new ListNode(2); l3->next = new ListNode(6);
        std::vector<ListNode*> lists = {l1, l2, l3};
        ListNode* r = Solution().mergeKLists(lists);
        check(r->val==1, "first element is 1");
        check(r->next->val==1, "second element is 1");
        check(r->next->next->val==2, "third element is 2");
        // full sequence: 1->1->2->3->4->4->5->6
        ListNode* t = r; int cnt = 0;
        while (t) { cnt++; t = t->next; }
        check(cnt == 8, "merged list has 8 nodes");
    }
    {
        std::vector<ListNode*> empty = {};
        check(Solution().mergeKLists(empty) == nullptr, "empty input -> null");
    }
    {
        std::vector<ListNode*> oneNull = {nullptr};
        check(Solution().mergeKLists(oneNull) == nullptr, "single null list -> null");
    }
    {
        ListNode* l1 = new ListNode(1);
        std::vector<ListNode*> single = {l1};
        check(Solution().mergeKLists(single)->val == 1, "single list passthrough");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
