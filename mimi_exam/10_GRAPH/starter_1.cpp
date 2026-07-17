#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// PROBLEM: Kahn's Topological Sort
// Find a valid order to complete courses given prerequisites.

class Solution {
public:
    std::vector<int> findOrder(int numCourses, const std::vector<std::pair<int,int>>& prerequisites) {
        // TODO:
        // - Build adjacency list and indegree vector
        // - Push all nodes with indegree 0 to queue
        // - BFS: pop, add to order, decrement neighbors' indegree, push if 0
        // - If order.size() != numCourses -> cycle exists, return {}

        return {};
    }
};

int main() {
    // Courses 0,1,2,3 where 3 must come first (prereq for 1 and 2, which are prereq for 0)
    std::vector<std::pair<int,int>> prereqs = {{0,1},{0,2},{1,3},{2,3}};
    std::vector<int> order = Solution().findOrder(4, prereqs);
    assert(order.size() == 4 && order[0] == 3);
    std::cout << "10_GRAPH Coding 1 Passed!" << std::endl;
    return 0;
}
