/**
 * @file no1_circular_queue.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 622: Design Circular Queue
 * @difficulty Medium
 * @link https://leetcode.com/problems/design-circular-queue/
 * 
 * @details
 * Problem Description:
 * Design your implementation of the circular queue. The circular queue is a linear data 
 * structure in which the operations are performed based on FIFO (First In First Out) 
 * principle and the last position is connected back to the first position to make a 
 * circle. It is also called "Ring Buffer".
 * 
 * One of the benefits of the circular queue is that we can make use of the spaces in 
 * front of the queue. In a normal queue, once the queue becomes full, we cannot insert 
 * the next element even if there is a space in front of the queue. But using the 
 * circular queue, we can store the next element in those free spaces.
 * 
 * Your MyCircularQueue class should support the following operations:
 * - MyCircularQueue(k): Constructor, set the size of the queue to be k.
 * - Front(): Get the front item from the queue. If the queue is empty, return -1.
 * - Rear(): Get the last item from the queue. If the queue is empty, return -1.
 * - enQueue(value): Insert an element into the circular queue. Return true if successful.
 * - deQueue(): Delete an element from the circular queue. Return true if successful.
 * - isEmpty(): Checks whether the circular queue is empty or not.
 * - isFull(): Checks whether the circular queue is full or not.
 */

#include <iostream>
#include <vector>
#include <cassert>

class MyCircularQueue {
private:
    std::vector<int> data;
    int head;
    int tail;
    int capacity;

public:
    /**
     * @brief Constructor to initialize the circular queue with capacity `k`.
     * @time_complexity O(K) where K is the size of the buffer to allocate.
     * @space_complexity O(K) to store elements.
     */
    MyCircularQueue(int k) {
        capacity = k;
        data.resize(k);
        head = -1;
        tail = -1;
    }
    
    /**
     * @brief Inserts an element into the circular queue.
     * @time_complexity O(1)
     * @space_complexity O(1)
     */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (isEmpty()) {
            head = 0; // If queue is empty, set head to the first index
        }
        tail = (tail + 1) % capacity; // Wrap around rear pointer cyclicly
        data[tail] = value;
        return true;
    }
    
    /**
     * @brief Deletes an element from the circular queue.
     * @time_complexity O(1)
     * @space_complexity O(1)
     */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (head == tail) {
            // If there's only one element, resetting the queue to empty state
            head = -1;
            tail = -1;
        } else {
            head = (head + 1) % capacity; // Wrap around front pointer cyclicly
        }
        return true;
    }
    
    /**
     * @brief Gets the front item from the queue.
     * @time_complexity O(1)
     */
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }
    
    /**
     * @brief Gets the last item from the queue.
     * @time_complexity O(1)
     */
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }
    
    /**
     * @brief Checks whether the circular queue is empty.
     * @time_complexity O(1)
     */
    bool isEmpty() {
        return head == -1;
    }
    
    /**
     * @brief Checks whether the circular queue is full.
     * @time_complexity O(1)
     */
    bool isFull() {
        if (isEmpty()) {
            return false;
        }
        return (tail + 1) % capacity == head;
    }
};

/**
 * ==========================================
 *          MANUAL DRY-RUN TRACE
 * ==========================================
 * Let's trace the following operations with k = 3:
 * 
 * 1. MyCircularQueue(3)
 *    - capacity = 3, data = [0, 0, 0], head = -1, tail = -1
 * 
 * 2. enQueue(1) -> Returns true
 *    - isEmpty() is true -> head = 0
 *    - tail = (tail + 1) % 3 = (-1 + 1) % 3 = 0
 *    - data[0] = 1. State: data = [1, 0, 0], head = 0, tail = 0
 * 
 * 3. enQueue(2) -> Returns true
 *    - tail = (tail + 1) % 3 = (0 + 1) % 3 = 1
 *    - data[1] = 2. State: data = [1, 2, 0], head = 0, tail = 1
 * 
 * 4. enQueue(3) -> Returns true
 *    - tail = (tail + 1) % 3 = (1 + 1) % 3 = 2
 *    - data[2] = 3. State: data = [1, 2, 3], head = 0, tail = 2
 * 
 * 5. enQueue(4) -> Returns false (isFull() is true because (tail + 1) % 3 == head -> (2 + 1) % 3 == 0)
 * 
 * 6. Rear() -> Returns 3 (data[tail] = data[2] = 3)
 * 
 * 7. isFull() -> Returns true
 * 
 * 8. deQueue() -> Returns true
 *    - head != tail (0 != 2) -> head = (head + 1) % 3 = 1
 *    - State: head = 1, tail = 2
 * 
 * 9. enQueue(4) -> Returns true
 *    - tail = (tail + 1) % 3 = (2 + 1) % 3 = 0
 *    - data[0] = 4. State: data = [4, 2, 3], head = 1, tail = 0
 * 
 * 10. Rear() -> Returns 4 (data[tail] = data[0] = 4)
 */

int main() {
    // Basic Verification
    MyCircularQueue* q = new MyCircularQueue(3);
    assert(q->enQueue(1) == true);
    assert(q->enQueue(2) == true);
    assert(q->enQueue(3) == true);
    assert(q->enQueue(4) == false); // Capacity reached
    assert(q->Rear() == 3);
    assert(q->isFull() == true);
    assert(q->deQueue() == true);
    assert(q->enQueue(4) == true);  // Wraps around to index 0
    assert(q->Rear() == 4);
    
    std::cout << "All assertions passed successfully!" << std::endl;
    delete q;
    return 0;
}
