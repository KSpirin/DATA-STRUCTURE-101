/**
 * @file no3_recent_calls.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 933: Number of Recent Calls
 * @difficulty Easy
 * @link https://leetcode.com/problems/number-of-recent-calls/
 * 
 * @details
 * Problem Description:
 * You have a RecentCounter class which counts the number of recent requests within a 
 * certain time frame.
 * 
 * Implement the RecentCounter class:
 * - RecentCounter() Initializes the counter with zero recent requests.
 * - int ping(int t) Adds a new request at time t, where t represents some time in 
 *   milliseconds, and returns the number of requests that has happened in the past 
 *   3000 milliseconds (including the new request). Specifically, return the number 
 *   of requests that have happened in the inclusive range [t - 3000, t].
 * 
 * It is guaranteed that every call to ping uses a strictly larger value of t than 
 * the previous call.
 */

#include <iostream>
#include <queue>
#include <cassert>

class RecentCounter {
private:
    std::queue<int> q;

public:
    /**
     * @brief Construct a new Recent Counter object.
     */
    RecentCounter() {}
    
    /**
     * @brief Adds a new request at time `t` and returns the number of requests in `[t - 3000, t]`.
     * @details Since `t` is strictly increasing, any request older than `t - 3000` is obsolete
     * and will never be relevant for any future pings. Thus, we can safely pop them from the 
     * front of the queue.
     * 
     * @time_complexity O(N) worst-case if many elements are popped, but O(1) amortized 
     * since each element is pushed and popped at most once.
     * @space_complexity O(W) where W is the maximum number of requests in a 3000ms window.
     */
    int ping(int t) {
        // Enqueue the new request time
        q.push(t);
        
        // Remove all requests that occurred before t - 3000
        int limit = t - 3000;
        while (!q.empty() && q.front() < limit) {
            q.pop();
        }
        
        // The remaining elements in the queue are within the [t - 3000, t] window
        return q.size();
    }
};

/**
 * ==========================================
 *          MANUAL DRY-RUN TRACE
 * ==========================================
 * Let's trace the calls to ping:
 * 
 * 1. RecentCounter counter;
 *    - q = []
 * 
 * 2. counter.ping(1) -> Returns 1
 *    - q.push(1) -> q = [1]
 *    - limit = 1 - 3000 = -2999
 *    - q.front() = 1 >= -2999 -> loop doesn't run.
 *    - Returns q.size() = 1
 * 
 * 3. counter.ping(100) -> Returns 2
 *    - q.push(100) -> q = [1, 100]
 *    - limit = 100 - 3000 = -2900
 *    - q.front() = 1 >= -2900 -> loop doesn't run.
 *    - Returns q.size() = 2
 * 
 * 4. counter.ping(3001) -> Returns 3
 *    - q.push(3001) -> q = [1, 100, 3001]
 *    - limit = 3001 - 3000 = 1
 *    - q.front() = 1 >= 1 -> loop doesn't run (since 1 is not strictly less than limit).
 *    - Returns q.size() = 3
 * 
 * 5. counter.ping(3002) -> Returns 3
 *    - q.push(3002) -> q = [1, 100, 3001, 3002]
 *    - limit = 3002 - 3000 = 2
 *    - Loop condition: q.front() < 2
 *        - q.front() = 1 < 2 -> q.pop() -> q = [100, 3001, 3002]
 *        - q.front() = 100 >= 2 -> loop terminates.
 *    - Returns q.size() = 3
 */

int main() {
    RecentCounter* recentCounter = new RecentCounter();
    assert(recentCounter->ping(1) == 1);     // requests = [1], range is [-2999,1], return 1
    assert(recentCounter->ping(100) == 2);   // requests = [1, 100], range is [-2900,100], return 2
    assert(recentCounter->ping(3001) == 3);  // requests = [1, 100, 3001], range is [1,3001], return 3
    assert(recentCounter->ping(3002) == 3);  // requests = [100, 3001, 3002], range is [2,3002], return 3
    
    std::cout << "All assertions passed successfully!" << std::endl;
    delete recentCounter;
    return 0;
}
