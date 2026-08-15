/**
 * @brief LeetCode 622 - Design Circular Queue
 * @difficulty Medium
 * @link https://leetcode.com/problems/design-circular-queue/
 *
 * Problem:
 * Fixed-capacity circular queue.
 * Implement: enQueue, deQueue, Front, Rear, isEmpty, isFull.
 * 
 * Constraints: 1 <= k <= 1000, 0 <= value <= 1000 */

#include <iostream>
#include <vector>
#include <cassert>
#include <string>

class MyCircularQueue {
public:
    MyCircularQueue(int k) { // TODO
    }
    bool enQueue(int value) { // TODO
    }
    bool deQueue() { // TODO
    }
    int Front() { // TODO
    }
    int Rear() { // TODO
    }
    bool isEmpty() { // TODO
    }
    bool isFull() { // TODO
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        MyCircularQueue q(3);
        check(q.enQueue(1) == true,  "enQueue(1) -> true");
        check(q.enQueue(2) == true,  "enQueue(2) -> true");
        check(q.enQueue(3) == true,  "enQueue(3) -> true");
        check(q.enQueue(4) == false, "enQueue(4) full -> false");
        check(q.Rear() == 3,         "Rear() == 3");
        check(q.isFull() == true,    "isFull() == true");
        check(q.deQueue() == true,   "deQueue() -> true");
        check(q.enQueue(4) == true,  "enQueue(4) after dequeue -> true");
        check(q.Rear() == 4,         "Rear() == 4");
    }
    {
        MyCircularQueue q2(1);
        check(q2.Front() == -1,      "Front() on empty == -1");
        check(q2.enQueue(10) == true,"enQueue(10) -> true");
        check(q2.Front() == 10,      "Front() == 10");
        check(q2.deQueue() == true,  "deQueue -> true");
        check(q2.isEmpty() == true,  "isEmpty after dequeue -> true");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
