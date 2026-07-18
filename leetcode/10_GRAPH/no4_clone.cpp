/**
 * @brief LeetCode 133 - Clone Graph
 * @difficulty Medium
 * @link https://leetcode.com/problems/clone-graph/
 *
 * Problem:
 * Deep copy of a connected undirected graph.
 * 
 * Constraints: 1 <= nodes <= 100, 1 <= Node.val <= 100 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

struct Node {
    int val;
    std::vector<Node*> neighbors;
    Node(int x) : val(x) {}
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // TODO (hash map to track cloned nodes)
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        Node* n1=new Node(1); Node* n2=new Node(2);
        Node* n3=new Node(3); Node* n4=new Node(4);
        n1->neighbors={n2,n4}; n2->neighbors={n1,n3};
        n3->neighbors={n2,n4}; n4->neighbors={n1,n3};
        Node* clone=Solution().cloneGraph(n1);
        check(clone!=n1,"clone is a different object");
        check(clone->val==1,"clone has same value");
        check(clone->neighbors.size()==2,"clone has same neighbor count");
        check(clone->neighbors[0]!=n2,"neighbors are also cloned");
    }
    {
        Node* single=new Node(1);
        Node* c=Solution().cloneGraph(single);
        check(c->val==1&&c->neighbors.empty(),"single node cloned");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
