/**
 * @file no6_group_anagrams.cpp
 * @brief LeetCode 49: Group Anagrams
 * @difficulty Medium
 * @link https://leetcode.com/problems/group-anagrams/
 * 
 * Problem Description:
 * Given an array of strings `strs`, group the anagrams together. 
 * You can return the answer in any order.
 * 
 * An Anagram is a word or phrase formed by rearranging the letters of a 
 * different word or phrase, typically using all the original letters exactly once.
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cassert>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        // Map from sorted string representation to a list of anagrams
        std::unordered_map<std::string, std::vector<std::string>> groups;
        
        for (const std::string& s : strs) {
            // Create a copy of the string to sort it
            std::string sorted_s = s;
            std::sort(sorted_s.begin(), sorted_s.end());
            // Group anagrams by their sorted representative
            groups[sorted_s].push_back(s);
        }
        
        // Collect results from the map
        std::vector<std::vector<std::string>> result;
        result.reserve(groups.size());
        for (auto& pair : groups) {
            result.push_back(std::move(pair.second));
        }
        
        return result;
    }
};

/*
================================================================================
Manual Dry-Run Trace:
Input: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

Initial state:
  groups = {} (empty hash map)
  result = {} (empty 2D vector)

Iterate through each string in strs:

1. s = "eat"
   - sorted_s = "aet"
   - groups["aet"] = ["eat"]

2. s = "tea"
   - sorted_s = "aet"
   - groups["aet"] = ["eat", "tea"]

3. s = "tan"
   - sorted_s = "ant"
   - groups["ant"] = ["tan"]

4. s = "ate"
   - sorted_s = "aet"
   - groups["aet"] = ["eat", "tea", "ate"]

5. s = "nat"
   - sorted_s = "ant"
   - groups["ant"] = ["tan", "nat"]

6. s = "bat"
   - sorted_s = "abt"
   - groups["abt"] = ["bat"]

After traversing all strings, map keys and values:
  "aet" -> ["eat", "tea", "ate"]
  "ant" -> ["tan", "nat"]
  "abt" -> ["bat"]

Convert groups map to 2D vector (order of outer groups does not matter):
  result = [
    ["eat", "tea", "ate"],
    ["tan", "nat"],
    ["bat"]
  ]

================================================================================
Complexity Analysis:
- Time Complexity: O(N * L log L)
  where N is the number of strings in strs, and L is the maximum length of a string in strs.
  For each of the N strings, we copy and sort the string of length L, which takes O(L log L) time.
  Inserting and accessing keys in std::unordered_map takes O(L) time on average due to string hashing.
  Hence, the overall time complexity is dominated by sorting, i.e., O(N * L log L).
  (Note: An alternative count-based representation approach runs in O(N * L) but has a higher constant factor.)
- Space Complexity: O(N * L)
  We store all characters of all strings in the hash map, which takes O(N * L) space in total.
================================================================================
*/

int main() {
    Solution solver;
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto result = solver.groupAnagrams(strs);
    
    // Validate number of groups
    assert(result.size() == 3);
    
    // Verify that groups contain correct members
    int aet_count = 0, ant_count = 0, abt_count = 0;
    for (const auto& group : result) {
        // Sort individual group contents to ease matching
        std::vector<std::string> sortedGroup = group;
        std::sort(sortedGroup.begin(), sortedGroup.end());
        
        if (sortedGroup == std::vector<std::string>{"ate", "eat", "tea"}) {
            aet_count++;
        } else if (sortedGroup == std::vector<std::string>{"nat", "tan"}) {
            ant_count++;
        } else if (sortedGroup == std::vector<std::string>{"bat"}) {
            abt_count++;
        }
    }
    
    assert(aet_count == 1);
    assert(ant_count == 1);
    assert(abt_count == 1);
    
    std::cout << "Group Anagrams tests passed!" << std::endl;
    return 0;
}
