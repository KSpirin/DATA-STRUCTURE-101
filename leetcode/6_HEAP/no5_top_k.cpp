/**
 * @brief LeetCode 347 - Top K Frequent Elements
 * @difficulty Medium
 * @link https://leetcode.com/problems/top-k-frequent-elements/
 *
 * Problem:
 * Return the k most frequent elements. Must be better than O(n log n).
 * 
 * Example: [1,1,1,2,2,3], k=2 -> [1,2]
 * 
 * Constraints: 1 <= k <= number of unique elements */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
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
        std::vector<int> n1={1,1,1,2,2,3};
        auto r=Solution().topKFrequent(n1,2);
        check(r.size()==2,"top 2 freqs, size==2");
    }
    {
        std::vector<int> n2={1};
        auto r=Solution().topKFrequent(n2,1);
        check(r.size()==1&&r[0]==1,"[1] k=1 -> [1]");
    }
    {
        std::vector<int> n3={4,1,-1,2,-1,2,3};
        auto r=Solution().topKFrequent(n3,2);
        check(r.size()==2,"7 nums k=2 -> 2 results");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
