#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

// PROBLEM: Next Greater Element
// For each element, find the next element to its RIGHT that is GREATER.
// If none exists, output -1.

class Solution {
public:
    std::vector<int> nextGreater(const std::vector<int>& nums) {
        // TODO:
        // - Create result vector filled with -1
        // - Iterate left to right
        // - While stack is not empty AND nums[i] > nums[stack.top()]:
        //     result[stack.top()] = nums[i]   (found the next greater!)
        //     pop the stack
        // - Push current index onto stack
        // - Return result

        return {};
    }
};

int main() {
    // {4, 5, 2, 25} -> next greater: {5, 25, 25, -1}
    std::vector<int> nums = {4, 5, 2, 25};
    std::vector<int> res = Solution().nextGreater(nums);
    assert(res[0] == 5 && res[1] == 25 && res[2] == 25 && res[3] == -1);
    std::cout << "2_STACK Coding 3 Passed!" << std::endl;
    return 0;
}
