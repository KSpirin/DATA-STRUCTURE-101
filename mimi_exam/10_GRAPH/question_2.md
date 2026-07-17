# LeetCode 743. Network Delay Time (Dijkstra)

You are given a network of `n` nodes, labeled from 1 to `n`. You are also given `times`, a list of travel times as directed edges `times[i] = (ui, vi, wi)`.

We will send a signal from a given node `k`. Return the minimum time it takes for all the `n` nodes to receive the signal. If it is impossible, return -1.

## Example 1:
**Input:** `adj = [[(1, 50)]] (from 2 to 1 with delay 50), n = 2, k = 2`
**Output:** `50`
