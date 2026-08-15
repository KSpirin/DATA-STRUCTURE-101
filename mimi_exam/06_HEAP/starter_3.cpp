#include <iostream>
#include <queue>
#include <cassert>

// PROBLEM: LeetCode 295 - Find Median from Data Stream
// After each addNum(), findMedian() should return the current median.

class MedianFinder {
private:
    // TODO 0: Declare:
    //   std::priority_queue<int> max_h;
    //   std::priority_queue<int, vector<int>, greater<int>> min_h;

public:
    void addNum(int num) {
        // TODO 1: Always push to max_h first
        // TODO 2: Then move max_h.top() to min_h (balance)
        // TODO 3: If max_h.size() < min_h.size(), move min_h.top() back to max_h
    }

    double findMedian() {
        // TODO 4: If max_h has more elements, return max_h.top()
        // TODO 5: Otherwise return (max_h.top() + min_h.top()) / 2.0
        return 0.0;
    }
};

int main() {
    MedianFinder mf;
    mf.addNum(1); mf.addNum(2);
    assert(mf.findMedian() == 1.5);
    mf.addNum(3);
    assert(mf.findMedian() == 2.0);
    std::cout << "6_HEAP Coding 3 Passed!" << std::endl;
    return 0;
}
