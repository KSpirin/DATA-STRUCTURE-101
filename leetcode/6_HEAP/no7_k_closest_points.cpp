/**
 * @file no7_k_closest_points.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 973: K Closest Points to Origin (Medium)
 * @link https://leetcode.com/problems/k-closest-points-to-origin/
 */

/*
Problem Description:
--------------------
Given an array of points where points[i] = [xi, yi] represents a point on the 
X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance 
(i.e., sqrt((x1 - x2)^2 + (y1 - y2)^2)).

You may return the answer in any order. The answer is guaranteed to be unique 
(except for the order that it is in).

Example 1:
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(1^2 + 3^2) = sqrt(10).
The distance between (-2, 2) and the origin is sqrt((-2)^2 + 2^2) = sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the k = 1 closest points to the origin, so we return [[-2,2]].

Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

Constraints:
------------
- 1 <= k <= points.length <= 10^4
- -10^4 <= xi, yi <= 10^4
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Guard Clause: Validate input parameters
        if (points.empty() || k <= 0) {
            throw std::invalid_argument("Points list cannot be empty and k must be positive.");
        }
        if (k > static_cast<int>(points.size())) {
            throw std::invalid_argument("k cannot exceed the total number of points.");
        }

        // Use a Max-Heap to store the points.
        // A Max-Heap keeps the point with the largest distance at the top.
        // We store pairs of: (squared_distance, index_in_points_array)
        // Note: We use squared distance (x^2 + y^2) to avoid floating-point errors
        // and costly square root operations.
        std::priority_queue<std::pair<int, int>> maxHeap;

        // Iterate through all points
        for (int i = 0; i < static_cast<int>(points.size()); ++i) {
            int x = points[i][0];
            int y = points[i][1];
            int distSquared = x * x + y * y;

            // Push current point's distance and index to the heap
            maxHeap.push({distSquared, i});

            // If the heap size exceeds k, pop the top element.
            // Since this is a Max-Heap, the top element has the largest distance 
            // among the current k + 1 points, so popping it leaves the k closest points.
            if (maxHeap.size() > static_cast<size_t>(k)) {
                maxHeap.pop();
            }
        }

        // Extract the k points from the heap
        std::vector<std::vector<int>> result;
        result.reserve(k);
        while (!maxHeap.empty()) {
            int index = maxHeap.top().second;
            result.push_back(points[index]);
            maxHeap.pop();
        }

        return result;
    }
};

/*
======================================================================
MANUAL DRY-RUN TRACE
======================================================================
Input: points = [[3,3], [5,-1], [-2,4]], k = 2

1. Initialize Max-Heap:
   maxHeap = []

2. Process Points:
   - Point 0: [3, 3] -> dist^2 = 3^2 + 3^2 = 9 + 9 = 18
     * maxHeap.push({18, 0})
     * maxHeap = [ {18, 0} ] (size 1 <= 2)

   - Point 1: [5, -1] -> dist^2 = 5^2 + (-1)^2 = 25 + 1 = 26
     * maxHeap.push({26, 1})
     * maxHeap = [ {26, 1}, {18, 0} ] (size 2 <= 2)

   - Point 2: [-2, 4] -> dist^2 = (-2)^2 + 4^2 = 4 + 16 = 20
     * maxHeap.push({20, 2})
     * maxHeap = [ {26, 1}, {20, 2}, {18, 0} ] (size 3 > 2)
     * maxHeap.pop() -> Pops {26, 1} (largest distance of 26)
     * maxHeap = [ {20, 2}, {18, 0} ] (size 2)

3. Extract results:
   - Pop {20, 2} -> add points[2] = [-2, 4] to result
   - Pop {18, 0} -> add points[0] = [3, 3] to result
   - result = [[-2, 4], [3, 3]]

Result: [[-2, 4], [3, 3]] (Correct!)

======================================================================
COMPLEXITY ANALYSIS
======================================================================
Time Complexity:
- For each of the N points, we compute the squared distance in O(1) time and 
  insert it into a heap.
- Inserting into a heap of size at most K costs O(log K) time.
- If the size exceeds K, popping the maximum element costs O(log K) time.
- Performing this for N points yields a time complexity of O(N log K).
- Extracting K elements at the end costs O(K log K) time.
- Overall Time Complexity: O(N log K). Since K <= N, this is faster than O(N log N) 
  when K is small.

Space Complexity:
- Max-Heap: O(K) space to store at most K + 1 pairs of (distance, index).
- Result Array: O(K) space to store the returned points.
- Overall Space Complexity: O(K) auxiliary space (excluding input/output).
*/

int main() {
    Solution solver;
    std::vector<std::vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
    int k = 2;

    try {
        std::vector<std::vector<int>> result = solver.kClosest(points, k);
        std::cout << "The " << k << " closest points are: " << std::endl;
        for (const auto& pt : result) {
            std::cout << "[" << pt[0] << ", " << pt[1] << "] " << std::endl;
        }
        std::cout << "Expected: [3, 3] and [-2, 4] (in any order)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
