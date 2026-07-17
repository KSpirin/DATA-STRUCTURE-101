/**
 * @file no4_reverse_string.cpp
 * @brief LeetCode 344: Reverse String
 * @difficulty Easy
 * @link https://leetcode.com/problems/reverse-string/
 */

/*
--------------------------------------------------------------------------------
PROBLEM DESCRIPTION
--------------------------------------------------------------------------------
Write a function that reverses a string. The input string is given as an array 
of characters `s`.

You must do this by modifying the input array in-place with O(1) extra memory.

Example 1:
Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Example 2:
Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]

Constraints:
- 1 <= s.length <= 10^5
- s[i] is a printable ascii character.
--------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <utility>

class Solution {
public:
    /**
     * @brief Reverses a vector of characters in-place.
     * 
     * Time Complexity: O(N) - We iterate through half the vector of size N.
     * Space Complexity: O(1) - Only two pointers/indices are used for swapping.
     * 
     * @param s The vector of characters to reverse in-place.
     */
    void reverseString(std::vector<char>& s) {
        // Guard clause: empty vector or vector with single character is already reversed
        if (s.empty()) {
            return;
        }

        int left = 0;
        int right = s.size() - 1;

        // Keep swapping characters from both ends moving towards the center
        while (left < right) {
            std::swap(s[left], s[right]); // In-place swap using std::swap
            left++;                       // Move left pointer forward
            right--;                      // Move right pointer backward
        }
    }
};

/*
--------------------------------------------------------------------------------
MANUAL DRY-RUN TRACE
--------------------------------------------------------------------------------
Let's dry-run the function call: Solution{}.reverseString(s) with s = ['h', 'e', 'l', 'l', 'o']

1. Initial Check:
   s is not empty. We bypass the early return.

2. State Initialization:
   left = 0
   right = s.size() - 1 = 4
   s = ['h', 'e', 'l', 'l', 'o']

3. Loop Execution (while left < right):
   
   - Iteration 1 (left = 0, right = 4):
     left (0) < right (4) is true.
     std::swap(s[0], s[4]) -> swaps 'h' and 'o'.
     s = ['o', 'e', 'l', 'l', 'h']
     left increments to 1
     right decrements to 3
     [State: left = 1, right = 3, s = ['o', 'e', 'l', 'l', 'h']]
     
   - Iteration 2 (left = 1, right = 3):
     left (1) < right (3) is true.
     std::swap(s[1], s[3]) -> swaps 'e' and 'l'.
     s = ['o', 'l', 'l', 'e', 'h']
     left increments to 2
     right decrements to 2
     [State: left = 2, right = 2, s = ['o', 'l', 'l', 'e', 'h']]
     
   - Iteration 3 (left = 2, right = 2):
     left (2) < right (2) is false. Loop terminates.

4. Termination:
   Function returns void. The string s has been reversed to ['o', 'l', 'l', 'e', 'h'].

Correctness Verification:
Input:  ['h', 'e', 'l', 'l', 'o']
Output: ['o', 'l', 'l', 'e', 'h'] (Matches expected output)

--------------------------------------------------------------------------------
COMPLEXITY ANALYSIS
--------------------------------------------------------------------------------
Time Complexity: O(N)
- We perform N/2 swaps, where N is the length of the character vector s. 
  Each swap operation takes O(1) time. Thus, the overall time complexity is linear.

Space Complexity: O(1)
- The algorithm modifies the input vector in-place. We only allocate a couple of 
  integer variables (left, right) which occupy constant extra memory.
--------------------------------------------------------------------------------
*/

int main() {
    Solution solution;
    
    // Test Case 1
    std::vector<char> s1 = {'h', 'e', 'l', 'l', 'o'};
    std::cout << "Original 1: ";
    for (char c : s1) std::cout << c;
    std::cout << std::endl;
    
    solution.reverseString(s1);
    
    std::cout << "Reversed 1: ";
    for (char c : s1) std::cout << c;
    std::cout << "\n" << std::endl;

    // Test Case 2
    std::vector<char> s2 = {'H', 'a', 'n', 'n', 'a', 'h'};
    std::cout << "Original 2: ";
    for (char c : s2) std::cout << c;
    std::cout << std::endl;
    
    solution.reverseString(s2);
    
    std::cout << "Reversed 2: ";
    for (char c : s2) std::cout << c;
    std::cout << std::endl;

    return 0;
}
