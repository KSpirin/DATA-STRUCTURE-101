/**
 * @file no2_climbing_stairs.cpp
 * @brief LeetCode 70: Climbing Stairs
 * @difficulty Easy
 * @link https://leetcode.com/problems/climbing-stairs/
 */

/*
--------------------------------------------------------------------------------
PROBLEM DESCRIPTION
--------------------------------------------------------------------------------
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you 
climb to the top?

Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

Constraints:
1 <= n <= 45
--------------------------------------------------------------------------------
*/

#include <iostream>

class Solution {
public:
    /**
     * @brief Computes the number of distinct ways to climb n stairs.
     * 
     * The problem is equivalent to the Fibonacci sequence:
     * To reach the i-th step, we can either:
     * 1. Take a 1-step from the (i-1)-th step.
     * 2. Take a 2-step from the (i-2)-th step.
     * Therefore, Ways(i) = Ways(i-1) + Ways(i-2).
     * 
     * Time Complexity: O(n) - Single loop iteration from 3 to n.
     * Space Complexity: O(1) - Only constant extra variables are used.
     * 
     * @param n The number of steps to reach the top.
     * @return The number of distinct ways to reach the top.
     */
    int climbStairs(int n) {
        // Base case: 1 step has exactly 1 way (1)
        if (n == 1) {
            return 1;
        }
        // Base case: 2 steps have exactly 2 ways (1+1, or 2)
        if (n == 2) {
            return 2;
        }

        // State variables:
        // prev2 corresponds to Ways(i-2)
        // prev1 corresponds to Ways(i-1)
        int prev2 = 1; 
        int prev1 = 2; 
        int current = 0; // corresponds to Ways(i)

        // Compute the values iteratively from step 3 up to n
        for (int i = 3; i <= n; ++i) {
            current = prev1 + prev2; // Ways(i) = Ways(i-1) + Ways(i-2)
            prev2 = prev1;           // Shift to prepare for next iteration
            prev1 = current;
        }

        return current;
    }
};

/*
--------------------------------------------------------------------------------
MANUAL DRY-RUN TRACE
--------------------------------------------------------------------------------
Let's dry-run the function call: Solution{}.climbStairs(5)

1. Initial Check:
   n = 5. Since n > 2, we bypass the early returns.

2. State Initialization:
   prev2 = 1 (representing climbStairs(1))
   prev1 = 2 (representing climbStairs(2))
   current = 0

3. Loop Execution (i from 3 to 5):
   
   - i = 3:
     current = prev1 + prev2 = 2 + 1 = 3
     prev2 = prev1 = 2
     prev1 = current = 3
     [State: prev2 = 2, prev1 = 3, current = 3]
     
   - i = 4:
     current = prev1 + prev2 = 3 + 2 = 5
     prev2 = prev1 = 3
     prev1 = current = 5
     [State: prev2 = 3, prev1 = 5, current = 5]
     
   - i = 5:
     current = prev1 + prev2 = 5 + 3 = 8
     prev2 = prev1 = 5
     prev1 = current = 8
     [State: prev2 = 5, prev1 = 8, current = 8]

4. Termination:
   Loop ends as i exceeds n (i = 6).
   Return current = 8.

Verification of Ways for n = 5:
Ways(1) = 1
Ways(2) = 2
Ways(3) = 2 + 1 = 3
Ways(4) = 3 + 2 = 5
Ways(5) = 5 + 3 = 8 (Matches return value)

--------------------------------------------------------------------------------
COMPLEXITY ANALYSIS
--------------------------------------------------------------------------------
Time Complexity: O(n)
- The algorithm calculates the number of ways iteratively using a single loop 
  that runs (n-2) times. Each iteration takes O(1) time.

Space Complexity: O(1)
- We only store three integer variables. No arrays or lists are allocated, and 
  there are no recursive call overheads.
--------------------------------------------------------------------------------
*/

int main() {
    Solution solution;
    int testCases[] = {1, 2, 3, 4, 5, 10};
    
    for (int n : testCases) {
        std::cout << "Ways to climb " << n << " stairs: " << solution.climbStairs(n) << std::endl;
    }
    
    return 0;
}
