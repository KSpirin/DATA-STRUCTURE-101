/**
 * @file no1_fibonacci.cpp
 * @brief LeetCode 509: Fibonacci Number
 * @difficulty Easy
 * @link https://leetcode.com/problems/fibonacci-number/
 */

/*
--------------------------------------------------------------------------------
PROBLEM DESCRIPTION
--------------------------------------------------------------------------------
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the 
Fibonacci sequence, such that each number is the sum of the two preceding ones, 
starting from 0 and 1. That is:

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.

Given n, calculate F(n).

Example 1:
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

Constraints:
0 <= n <= 30
--------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>

class Solution {
public:
    /**
     * @brief Computes the n-th Fibonacci number using space-optimized iterative DP.
     * 
     * Time Complexity: O(n) - We iterate from 2 to n exactly once.
     * Space Complexity: O(1) - Only a few state variables are kept in memory.
     * 
     * @param n The index of the Fibonacci number to compute.
     * @return The n-th Fibonacci number.
     */
    int fib(int n) {
        // Base case: F(0) = 0
        if (n == 0) {
            return 0;
        }
        // Base case: F(1) = 1
        if (n == 1) {
            return 1;
        }

        // State variables to keep track of F(i-2) and F(i-1)
        int prev2 = 0; // Represents F(i - 2)
        int prev1 = 1; // Represents F(i - 1)
        int current = 0; // Represents F(i)

        // Iterate from 2 up to n to compute the Fibonacci numbers sequentially
        for (int i = 2; i <= n; ++i) {
            current = prev1 + prev2; // F(i) = F(i - 1) + F(i - 2)
            prev2 = prev1;           // Shift prev2 to F(i - 1)
            prev1 = current;         // Shift prev1 to F(i)
        }

        return current;
    }
};

/*
--------------------------------------------------------------------------------
MANUAL DRY-RUN TRACE
--------------------------------------------------------------------------------
Let's dry-run the function call: Solution{}.fib(5)

1. Initial Check:
   n = 5. Since n > 1, we bypass the early returns.

2. State Initialization:
   prev2 = 0
   prev1 = 1
   current = 0

3. Loop Execution (i from 2 to 5):
   
   - i = 2:
     current = prev1 + prev2 = 1 + 0 = 1
     prev2 = prev1 = 1
     prev1 = current = 1
     [State: prev2 = 1, prev1 = 1, current = 1]
     
   - i = 3:
     current = prev1 + prev2 = 1 + 1 = 2
     prev2 = prev1 = 1
     prev1 = current = 2
     [State: prev2 = 1, prev1 = 2, current = 2]
     
   - i = 4:
     current = prev1 + prev2 = 2 + 1 = 3
     prev2 = prev1 = 2
     prev1 = current = 3
     [State: prev2 = 2, prev1 = 3, current = 3]
     
   - i = 5:
     current = prev1 + prev2 = 3 + 2 = 5
     prev2 = prev1 = 3
     prev1 = current = 5
     [State: prev2 = 3, prev1 = 5, current = 5]

4. Termination:
   Loop ends as i exceeds n (i = 6).
   Return current = 5.

Correctness Verification:
F(0) = 0
F(1) = 1
F(2) = 1 + 0 = 1
F(3) = 1 + 1 = 2
F(4) = 2 + 1 = 3
F(5) = 3 + 2 = 5 (Matches return value)

--------------------------------------------------------------------------------
COMPLEXITY ANALYSIS
--------------------------------------------------------------------------------
Time Complexity: O(n)
- A single loop runs from 2 to n. Each step takes O(1) time. Thus, the time 
  taken scales linearly with the input size n.

Space Complexity: O(1)
- We use only three integer variables (prev1, prev2, current) to store the states.
  No dynamic memory allocation, vectors, or recursive call stack space is used.
--------------------------------------------------------------------------------
*/

int main() {
    Solution solution;
    int testCases[] = {0, 1, 2, 3, 4, 5, 6};
    
    for (int n : testCases) {
        std::cout << "F(" << n << ") = " << solution.fib(n) << std::endl;
    }
    
    return 0;
}
