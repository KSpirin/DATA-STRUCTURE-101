/**
 * @brief LeetCode 295 - Find Median from Data Stream
 * @difficulty Hard
 * @link https://leetcode.com/problems/find-median-from-data-stream/
 *
 * Problem:
 * addNum and findMedian from a growing stream.
 * 
 * Example: addNum(1),addNum(2),findMedian()==1.5, addNum(3),findMedian()==2.0
 * 
 * Constraints: -10^5 <= num <= 10^5 */

#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

class MedianFinder {
public:
    void addNum(int num) { // TODO (dual heap)
    }
    double findMedian() { // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        MedianFinder mf;
        mf.addNum(1); mf.addNum(2);
        check(mf.findMedian()==1.5, "median of [1,2] == 1.5");
        mf.addNum(3);
        check(mf.findMedian()==2.0, "median of [1,2,3] == 2.0");
    }
    {
        MedianFinder mf2;
        mf2.addNum(6);
        check(mf2.findMedian()==6.0, "single 6 -> 6.0");
        mf2.addNum(10);
        check(mf2.findMedian()==8.0, "[6,10] -> 8.0");
        mf2.addNum(2);
        check(mf2.findMedian()==6.0, "[2,6,10] -> 6.0");
        mf2.addNum(6);
        check(mf2.findMedian()==6.0, "[2,6,6,10] -> 6.0");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
