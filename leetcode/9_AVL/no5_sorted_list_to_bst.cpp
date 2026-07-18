/**
 * @brief LeetCode 109 - Sorted List to BST
 * @difficulty Medium
 * @link https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
 *
 * Problem:
 * Convert sorted linked list to height-balanced BST.
 * 
 * Example: [-10,-3,0,5,9] -> [0,-3,9,-10,null,5]
 * 
 * Constraints: 0 <= nodes <= 2*10^4 */

#include <iostream>
#include <cassert>

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        // TODO: slow/fast pointer to find mid
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        ListNode* h=new ListNode(-10);
        h->next=new ListNode(-3); h->next->next=new ListNode(0);
        h->next->next->next=new ListNode(5); h->next->next->next->next=new ListNode(9);
        TreeNode* r=Solution().sortedListToBST(h);
        check(r!=nullptr,"result not null");
        check(r->val==0,"mid element as root");
    }
    {
        ListNode* h2=new ListNode(1);
        TreeNode* r2=Solution().sortedListToBST(h2);
        check(r2->val==1&&r2->left==nullptr&&r2->right==nullptr,"single -> leaf");
    }
    {
        TreeNode* r3=Solution().sortedListToBST(nullptr);
        check(r3==nullptr,"null list -> null tree");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
