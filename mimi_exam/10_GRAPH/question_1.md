# LeetCode 210. Course Schedule II (Topological Sort)

There are a total of `numCourses` courses you have to take, labeled from 0 to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

Return the ordering of courses you should take to finish all courses.

## Example 1:
**Input:** `numCourses = 4, prerequisites = [[0,1],[0,2],[1,3],[2,3]]`
**Output:** `[3,1,2,0] (or [3,2,1,0])`
