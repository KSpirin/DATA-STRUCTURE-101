/**
 * @file no6_task_scheduler.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 621: Task Scheduler (Medium)
 * @link https://leetcode.com/problems/task-scheduler/
 */

/*
Problem Description:
--------------------
Given a characters array tasks, representing the tasks a CPU needs to do, where 
each character represents a unique task. Tasks could be done in any order. Each 
task is done in one unit of time. For each unit of time, the CPU could complete 
either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period 
between two same tasks (the same letter in the array), that is that there must 
be at least n units of time between any two same tasks.

Return the minimum number of intervals required to complete all the given tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.

Example 2:
Input: tasks = ["A","C","A","B","D","B"], n = 1
Output: 6
Explanation: A -> B -> C -> D -> A -> B
With n = 1, there is at least 1 unit of time between any two same tasks.

Example 3:
Input: tasks = ["A","A","A","B","B","B"], n = 3
Output: 10
Explanation: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B
There is at least 3 units of time between any two same tasks.

Constraints:
------------
- 1 <= tasks.length <= 10^4
- tasks[i] is an uppercase English letter.
- 0 <= n <= 100
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <algorithm>

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
        // Guard Clause: Validate input arguments
        if (tasks.empty()) {
            return 0;
        }
        if (n < 0) {
            throw std::invalid_argument("Cooldown period n cannot be negative.");
        }

        // Step 1: Count frequency of each task
        std::unordered_map<char, int> taskCounts;
        for (char task : tasks) {
            taskCounts[task]++;
        }

        // Step 2: Push frequencies into a Max-Heap (priority queue)
        // Since we only care about frequencies (greedy choice of most frequent tasks),
        // we store only the integers representing the counts.
        std::priority_queue<int> maxHeap;
        for (const auto& [task, count] : taskCounts) {
            maxHeap.push(count);
        }

        int totalTime = 0;

        // Step 3: Simulate task execution cycle of length (n + 1)
        while (!maxHeap.empty()) {
            std::vector<int> tempStorage;
            int timeInCycle = 0;

            // Try to execute up to (n + 1) unique tasks to avoid cooldowns
            for (int i = 0; i <= n; ++i) {
                if (!maxHeap.empty()) {
                    int currentFreq = maxHeap.top();
                    maxHeap.pop();

                    // Execute the task: decrement frequency
                    currentFreq--;
                    timeInCycle++;

                    // If task still has pending instances, save it for the next cycle
                    if (currentFreq > 0) {
                        tempStorage.push_back(currentFreq);
                    }
                }
            }

            // Push pending tasks back into the max heap
            for (int remainingFreq : tempStorage) {
                maxHeap.push(remainingFreq);
            }

            // If the heap is empty, we don't need to count idle times for the last cycle.
            // Otherwise, we spent the full n + 1 intervals in this cycle.
            if (maxHeap.empty()) {
                totalTime += timeInCycle;
            } else {
                totalTime += (n + 1);
            }
        }

        return totalTime;
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE
======================================================================
Input: tasks = ["A","A","A","B","B","B"], n = 2

1. Count Frequencies:
   taskCounts = { 'A': 3, 'B': 3 }

2. Populate Max-Heap:
   maxHeap = [3, 3]  (representing frequencies of 'A' and 'B')

3. Simulation Loop:
   - Cycle 1 (n + 1 = 3 slots):
     * slot 1: Pop 3 from heap -> heap = [3]. Freq decrements to 2. tempStorage = [2]
     * slot 2: Pop 3 from heap -> heap = []. Freq decrements to 2. tempStorage = [2, 2]
     * slot 3: Heap is empty. No more tasks can be executed.
     * End of Cycle 1: 
       - Push tempStorage [2, 2] back to heap. heap = [2, 2]
       - Since heap is not empty, totalTime += (n + 1) -> totalTime = 3.
       (Sequence: A -> B -> idle)

   - Cycle 2 (n + 1 = 3 slots):
     * slot 1: Pop 2 from heap -> heap = [2]. Freq decrements to 1. tempStorage = [1]
     * slot 2: Pop 2 from heap -> heap = []. Freq decrements to 1. tempStorage = [1, 1]
     * slot 3: Heap is empty.
     * End of Cycle 2:
       - Push tempStorage [1, 1] back to heap. heap = [1, 1]
       - Since heap is not empty, totalTime += (n + 1) -> totalTime = 3 + 3 = 6.
       (Sequence: A -> B -> idle -> A -> B -> idle)

   - Cycle 3 (n + 1 = 3 slots):
     * slot 1: Pop 1 from heap -> heap = [1]. Freq decrements to 0. tempStorage = []
     * slot 2: Pop 1 from heap -> heap = []. Freq decrements to 0. tempStorage = []
     * slot 3: Heap is empty.
     * End of Cycle 3:
       - tempStorage is empty, maxHeap is empty.
       - Since heap is empty, we only add actual executions: timeInCycle = 2.
       - totalTime = 6 + 2 = 8.
       (Sequence: A -> B -> idle -> A -> B -> idle -> A -> B)

Result: 8 (Correct!)

======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity:
- Step 1 (Frequency count): O(N), where N is the number of tasks.
- Step 2 (Heap insertion): O(U log U), where U is the number of unique tasks.
  Since there are only 26 uppercase letters, U <= 26. Thus, heap operations are 
  bounded by a small constant.
- Step 3 (Simulation): The maximum number of heap elements is 26. Each cycle 
  does at most 26 pops and pushes. The total execution time is proportional to 
  the number of tasks. Specifically, the simulation takes O(T log U) where T 
  is the total CPU intervals (T >= N). Since U <= 26, the time complexity is 
  dominated by O(N) to read the tasks array.
- Overall Time Complexity: O(N) because the unique character limit (26) makes 
  priority queue operations O(1) in practice.

Space Complexity:
- Frequency Map: O(U) space for unique tasks, which is O(1) as U <= 26.
- Max-Heap: O(U) space, which is O(1).
- Temp Storage: O(U) space, which is O(1).
- Overall Space Complexity: O(1) auxiliary space (excluding input/output).
*/

int main() {
    Solution solver;
    std::vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;

    try {
        int result = solver.leastInterval(tasks, n);
        std::cout << "Minimum intervals required: " << result << " (Expected: 8)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
