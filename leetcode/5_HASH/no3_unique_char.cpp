/**
 * @file no3_first_unique_char.cpp
 * @brief LeetCode 387: First Unique Character in a String
 * @difficulty Easy
 * @link https://leetcode.com/problems/first-unique-character-in-a-string/
 * 
 * Problem Description:
 * Given a string `s`, find the first non-repeating character in it and return its index. 
 * If it does not exist, return -1.
 */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

class Solution {
public:
    int firstUniqChar(std::string s) {
        // Direct subtraction hashing: Key = char, Hash Function = key - 'a'
        // Since the string only contains lowercase English letters, the table size is 26.
        std::vector<int> freq(26, 0);
        
        // Pass 1: Count frequency of each character
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Pass 2: Find the first character with a frequency of 1
        for (int i = 0; i < s.length(); ++i) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        // No unique character found
        return -1;
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Input: s = "leetcode"

Initial State:
  freq = [0, 0, ..., 0] (size 26)

Pass 1 (Frequency counting):
  i = 0, char = 'l' -> freq['l'-'a'] = freq[11]++ -> freq[11] = 1
  i = 1, char = 'e' -> freq['e'-'a'] = freq[4]++  -> freq[4] = 1
  i = 2, char = 'e' -> freq['e'-'a'] = freq[4]++  -> freq[4] = 2
  i = 3, char = 't' -> freq['t'-'a'] = freq[19]++ -> freq[19] = 1
  i = 4, char = 'c' -> freq['c'-'a'] = freq[2]++  -> freq[2] = 1
  i = 5, char = 'o' -> freq['o'-'a'] = freq[14]++ -> freq[14] = 1
  i = 6, char = 'd' -> freq['d'-'a'] = freq[3]++  -> freq[3] = 1
  i = 7, char = 'e' -> freq['e'-'a'] = freq[4]++  -> freq[4] = 3

Final freq array has:
  freq[11] ('l') = 1
  freq[4]  ('e') = 3
  freq[19] ('t') = 1
  freq[2]  ('c') = 1
  freq[14] ('o') = 1
  freq[3]  ('d') = 1
  others = 0

Pass 2 (Finding first unique):
  i = 0, s[0] = 'l' -> freq['l'-'a'] = freq[11] = 1.
  Since freq[11] == 1, we return index 0 immediately.

Output: 0
================================================================================
Complexity Analysis:
- Time Complexity: O(N)
  We traverse the string of length N twice. Frequency map lookup and update operations 
  take O(1) time.
- Space Complexity: O(1)
  The frequency table has a fixed size of 26, which does not depend on the input size N.
================================================================================
*/

int main() {
    Solution solver;
    std::string s1 = "leetcode";
    std::string s2 = "loveleetcode";
    std::string s3 = "aabb";
    
    assert(solver.firstUniqChar(s1) == 0);
    assert(solver.firstUniqChar(s2) == 2);
    assert(solver.firstUniqChar(s3) == -1);
    
    std::cout << "First Unique Character test passed!" << std::endl;
    return 0;
}
