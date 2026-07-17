/**
 * @file no4_find_median_from_data_stream.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 295: Find Median from Data Stream (Hard)
 * @link https://leetcode.com/problems/find-median-from-data-stream/
 */

/*
Problem Description:
--------------------
The median is the middle value in an ordered integer list. If the size of the list is even, 
there is no middle value, and the median is the mean of the two middle values.

- For example, for arr = [2,3,4], the median is 3.
- For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.

Implement the MedianFinder class:
- MedianFinder() initializes the MedianFinder object.
- void addNum(int num) adds the integer num from the data stream to the data structure.
- double findMedian() returns the median of all elements so far. Answers within 10^-5 of the 
  actual answer will be accepted.

Example 1:
Input:
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output:
[null, null, null, 1.5, null, 2.0]

Explanation:
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr = [1, 2, 3]
medianFinder.findMedian(); // return 2.0

Constraints:
------------
- -10^5 <= num <= 10^5
- There will be at least one element in the data structure before calling findMedian.
- At most 5 * 10^4 calls will be made to addNum and findMedian.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>
#include <iomanip>

class MedianFinder {
private:
    // maxHeap stores the smaller half of the numbers.
    // The largest of this half is at the top.
    std::priority_queue<int> maxHeap;

    // minHeap stores the larger half of the numbers.
    // The smallest of this half is at the top.
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

public:
    MedianFinder() {
        // Constructor is empty as member heaps initialize automatically
    }
    
    void addNum(int num) {
        // Step 1: Insert to maxHeap (smaller half)
        maxHeap.push(num);
        
        // Step 2: Balance check - the largest of maxHeap must be smaller than or equal to 
        // the smallest of minHeap.
        // We ensure this by immediately passing maxHeap's top element to minHeap.
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        // Step 3: Size constraint - we maintain maxHeap's size >= minHeap's size.
        // Since we pushed an element to minHeap, it might exceed maxHeap in size.
        // If so, we move the top of minHeap back to maxHeap.
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        // Guard Clause: No elements in the data stream yet
        if (maxHeap.empty()) {
            throw std::underflow_error("MedianFinder is empty: No elements to find median.");
        }

        // If the total size is odd, maxHeap will have exactly one more element than minHeap.
        // The median is the top of maxHeap.
        if (maxHeap.size() > minHeap.size()) {
            return static_cast<double>(maxHeap.top());
        }
        // If the total size is even, both heaps are of equal size.
        // The median is the average of the tops of both heaps.
        return (static_cast<double>(maxHeap.top()) + static_cast<double>(minHeap.top())) / 2.0;
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE
======================================================================
We trace the calls: addNum(1), addNum(2), findMedian(), addNum(3), findMedian().

1. Initialize MedianFinder:
   maxHeap = []
   minHeap = []

2. addNum(1):
   - maxHeap.push(1)      -> maxHeap = [1]
   - minHeap.push(1)      -> minHeap = [1], maxHeap.pop() -> maxHeap = []
   - Size check: maxHeap.size() (0) < minHeap.size() (1)
     * maxHeap.push(1)    -> maxHeap = [1]
     * minHeap.pop()      -> minHeap = []
   - State after addNum(1): maxHeap = [1], minHeap = []

3. addNum(2):
   - maxHeap.push(2)      -> maxHeap = [2, 1] (2 is root)
   - minHeap.push(2)      -> minHeap = [2], maxHeap.pop() -> maxHeap = [1]
   - Size check: maxHeap.size() (1) == minHeap.size() (1) (No action needed)
   - State after addNum(2): maxHeap = [1], minHeap = [2]

4. findMedian():
   - maxHeap.size() (1) == minHeap.size() (1) (Even total elements)
   - return (maxHeap.top() + minHeap.top()) / 2.0 -> (1 + 2) / 2.0 = 1.5 (Correct!)

5. addNum(3):
   - maxHeap.push(3)      -> maxHeap = [3, 1] (3 is root)
   - minHeap.push(3)      -> minHeap = [2, 3], maxHeap.pop() -> maxHeap = [1]
   - Size check: maxHeap.size() (1) < minHeap.size() (2)
     * maxHeap.push(2)    -> maxHeap = [2, 1] (2 is root)
     * minHeap.pop()      -> minHeap = [3]
   - State after addNum(3): maxHeap = [2, 1], minHeap = [3]

6. findMedian():
   - maxHeap.size() (2) > minHeap.size() (1) (Odd total elements)
   - return maxHeap.top() -> returns 2.0 (Correct!)

======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity:
- addNum(num): 
  - Pushing to maxHeap takes O(log N).
  - Popping and pushing to minHeap takes O(log N).
  - Conditional balancing step takes O(log N).
  - Total Time Complexity: O(log N) per insertion.
- findMedian():
  - Retrieving the top elements takes O(1) time.
  - Total Time Complexity: O(1) per median query.

Space Complexity:
- We store all N numbers in the two heaps.
- Total Space Complexity: O(N) auxiliary space.
*/

int main() {
    MedianFinder medianFinder;
    
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "Adding 1..." << std::endl;
    medianFinder.addNum(1);
    
    std::cout << "Adding 2..." << std::endl;
    medianFinder.addNum(2);
    
    std::cout << "Current Median: " << medianFinder.findMedian() << " (Expected: 1.5)" << std::endl;
    
    std::cout << "Adding 3..." << std::endl;
    medianFinder.addNum(3);
    
    std::cout << "Current Median: " << medianFinder.findMedian() << " (Expected: 2.0)" << std::endl;

    return 0;
}
