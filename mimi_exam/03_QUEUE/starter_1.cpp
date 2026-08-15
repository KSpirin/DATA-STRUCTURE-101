#include <iostream>
#include <cassert>

// PROBLEM: LeetCode 622 - Circular Queue
// Use an array with head/tail indices that wrap around using modulo (%).

class CircularQueue {
private:
    // TODO 0: Declare members
    //   int* data;
    //   int head, tail, size, capacity;

public:
    CircularQueue(int k) {
        // TODO 1: Allocate array, set capacity=k, head=-1, tail=-1, size=0
    }

    bool enqueue(int value) {
        // TODO 2: If full (size == capacity) return false
        // TODO 3: tail = (tail + 1) % capacity, data[tail] = value
        // TODO 4: If head == -1, set head = tail
        // TODO 5: size++, return true
        return false;
    }

    bool dequeue() {
        // TODO 6: If empty (size == 0) return false
        // TODO 7: head = (head + 1) % capacity, size--
        // TODO 8: If size == 0, reset head=tail=-1, return true
        return false;
    }

    int Front() {
        // TODO 9: Return data[head] or -1 if empty
        return -1;
    }

    int Rear() {
        // TODO 10: Return data[tail] or -1 if empty
        return -1;
    }
};

int main() {
    CircularQueue q(3);
    assert(q.enqueue(1) == true);
    assert(q.enqueue(2) == true);
    assert(q.Rear() == 2);
    assert(q.Front() == 1);
    std::cout << "3_QUEUE Coding 1 Passed!" << std::endl;
    return 0;
}
