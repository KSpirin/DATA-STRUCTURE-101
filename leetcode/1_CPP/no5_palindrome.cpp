/**
 * @file no5_palindrome.cpp
 * @brief LeetCode 125: Valid Palindrome
 * @difficulty Easy
 * @link https://leetcode.com/problems/valid-palindrome/
 */

/*
--------------------------------------------------------------------------------
PROBLEM DESCRIPTION
--------------------------------------------------------------------------------
A phrase is a palindrome if, after converting all uppercase letters into lowercase 
letters and removing all non-alphanumeric characters, it reads the same forward 
and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

Example 1:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.

Constraints:
- 1 <= s.length <= 2 * 10^5
- s consists only of printable ASCII characters.
--------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <cctype>

class Solution {
public:
    /**
     * @brief Checks if a string is a palindrome, ignoring case and non-alphanumeric characters.
     * 
     * Time Complexity: O(N) - Single pass through the string of length N.
     * Space Complexity: O(1) - Pointers/indices are adjusted in-place.
     * 
     * @param s The input string.
     * @return true if the string is a palindrome, false otherwise.
     */
    bool isPalindrome(std::string s) {
        // Guard clause: empty string is a palindrome
        if (s.empty()) {
            return true;
        }

        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Move left pointer forward while character is non-alphanumeric
            while (left < right && !std::isalnum(static_cast<unsigned char>(s[left]))) {
                left++;
            }
            // Move right pointer backward while character is non-alphanumeric
            while (left < right && !std::isalnum(static_cast<unsigned char>(s[right]))) {
                right--;
            }

            // Compare characters case-insensitively
            if (std::tolower(static_cast<unsigned char>(s[left])) != std::tolower(static_cast<unsigned char>(s[right]))) {
                return false;
            }

            // Move pointers inwards
            left++;
            right--;
        }

        return true;
    }
};

/*
--------------------------------------------------------------------------------
MANUAL DRY-RUN TRACE
--------------------------------------------------------------------------------
Let's dry-run the function call: Solution{}.isPalindrome("A man, a plan, a canal: Panama")

1. Initial Check:
   The string is not empty. We bypass the early return.

2. State Initialization:
   left = 0
   right = 29 (length is 30)
   s = "A man, a plan, a canal: Panama"

3. Loop Execution (while left < right):
   
   - Step 1:
     s[left] = 'A' (alphanumeric). left stays 0.
     s[right] = 'a' (alphanumeric). right stays 29.
     Compare: tolower('A') == tolower('a') ('a' == 'a') -> Match.
     left becomes 1, right becomes 28.

   - Step 2:
     s[left] = ' ' (non-alphanumeric) -> left increments to 2.
     s[left] = 'm' (alphanumeric). left stays 2.
     s[right] = 'm' (alphanumeric). right stays 28.
     Compare: tolower('m') == tolower('m') ('m' == 'm') -> Match.
     left becomes 3, right becomes 27.

   - Step 3:
     s[left] = 'a' (alphanumeric) -> left stays 3.
     s[right] = 'a' (alphanumeric) -> right stays 27.
     Compare: tolower('a') == tolower('a') -> Match.
     left becomes 4, right becomes 26.

   ... (Skipping intermediate matches: "n", "a", "p", "l", "a", "n", "a", "c", "a", "n", "a") ...

   - Let's trace near the center:
     Filtered string: "a m a n a p l a n a c a n a l p a n a m a"
     Center is 'c' at index 15 ("canal: Panama" section).
     When left = 14 ('a') and right = 16 ('a'), they match and move to left = 15, right = 15.
     The loop condition left < right (15 < 15) is false.
     Loop terminates.

4. Termination:
   Returns true. Correct.

--------------------------------------------------------------------------------
COMPLEXITY ANALYSIS
--------------------------------------------------------------------------------
Time Complexity: O(N)
- We traverse the string with two pointers starting from both ends and moving 
  towards the middle. Each character is visited at most twice (once by the skip 
  loop and once by the main loop). Hence, the time complexity is linear, O(N).

Space Complexity: O(1)
- We do not create a filtered string copy. The checks are performed in-place 
  using constant auxiliary space for pointers/indices and character functions.
--------------------------------------------------------------------------------
*/

int main() {
    Solution solution;
    
    // Test Case 1
    std::string s1 = "A man, a plan, a canal: Panama";
    std::cout << "Input 1: \"" << s1 << "\"" << std::endl;
    std::cout << "Is Palindrome? " << (solution.isPalindrome(s1) ? "Yes" : "No") << "\n" << std::endl;

    // Test Case 2
    std::string s2 = "race a car";
    std::cout << "Input 2: \"" << s2 << "\"" << std::endl;
    std::cout << "Is Palindrome? " << (solution.isPalindrome(s2) ? "Yes" : "No") << "\n" << std::endl;

    // Test Case 3
    std::string s3 = " ";
    std::cout << "Input 3: \"" << s3 << "\"" << std::endl;
    std::cout << "Is Palindrome? " << (solution.isPalindrome(s3) ? "Yes" : "No") << std::endl;

    return 0;
}
