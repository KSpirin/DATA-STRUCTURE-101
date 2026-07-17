/**
 * @file no4_clone_graph.cpp
 * @brief LeetCode 133: Clone Graph
 * @difficulty Medium
 * @link https://leetcode.com/problems/clone-graph/
 *
 * Problem Description:
 * Given a reference of a node in a connected undirected graph.
 * Return a deep copy (clone) of the graph.
 * 
 * Each node in the graph contains a value (int) and a list (vector<Node*>) of its neighbors.
 * 
 * class Node {
 * public:
 *     int val;
 *     vector<Node*> neighbors;
 * };
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
private:
    // Hash map to map original nodes to their corresponding cloned nodes.
    // This also acts as a visited set to prevent infinite loops in cyclic graphs.
    unordered_map<Node*, Node*> visited;

public:
    /**
     * @brief Recursively clones the graph using Depth-First Search (DFS).
     * 
     * @param node The starting node of the original graph to clone.
     * @return Node* The deep-copied clone of the original node.
     */
    Node* cloneGraph(Node* node) {
        // Guard clause: if the graph is empty, return nullptr.
        if (node == nullptr) {
            return nullptr;
        }

        // If the node has already been cloned, return the existing clone.
        if (visited.find(node) != visited.end()) {
            return visited[node];
        }

        // Create a new clone for the current node.
        // Copy the value (but keep neighbors empty initially).
        Node* cloneNode = new Node(node->val);
        
        // Register the clone in the visited map BEFORE processing neighbors
        // to avoid infinite recursion on cyclic paths.
        visited[node] = cloneNode;

        // Iterate through all neighbors of the current node and recursively clone them.
        for (Node* neighbor : node->neighbors) {
            cloneNode->neighbors.push_back(cloneGraph(neighbor));
        }

        return cloneNode;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE
 * ============================================================================
 * Let's trace cloneGraph on a graph with 4 nodes forming a cycle:
 * 1 --- 2
 * |     |
 * 4 --- 3
 * 
 * Input node: Node 1
 * neighbors of 1: [2, 4]
 * neighbors of 2: [1, 3]
 * neighbors of 3: [2, 4]
 * neighbors of 4: [1, 3]
 * 
 * Step-by-Step Execution:
 * 1. Call cloneGraph(Node 1):
 *    - node is not null, not in visited.
 *    - Create cloneNode1 (val = 1).
 *    - visited[Node 1] = cloneNode1.
 *    - Loop through neighbors of Node 1: [Node 2, Node 4]
 *      - neighbor = Node 2:
 *        - Call cloneGraph(Node 2):
 *          - node is not null, not in visited.
 *          - Create cloneNode2 (val = 2).
 *          - visited[Node 2] = cloneNode2.
 *          - Loop through neighbors of Node 2: [Node 1, Node 3]
 *            - neighbor = Node 1:
 *              - Call cloneGraph(Node 1):
 *                - Node 1 IS in visited. Return visited[Node 1] (cloneNode1).
 *              - cloneNode2->neighbors.push_back(cloneNode1).
 *            - neighbor = Node 3:
 *              - Call cloneGraph(Node 3):
 *                - node is not null, not in visited.
 *                - Create cloneNode3 (val = 3).
 *                - visited[Node 3] = cloneNode3.
 *                - Loop through neighbors of Node 3: [Node 2, Node 4]
 *                  - neighbor = Node 2:
 *                    - Call cloneGraph(Node 2):
 *                      - Node 2 IS in visited. Return visited[Node 2] (cloneNode2).
 *                    - cloneNode3->neighbors.push_back(cloneNode2).
 *                  - neighbor = Node 4:
 *                    - Call cloneGraph(Node 4):
 *                      - node is not null, not in visited.
 *                      - Create cloneNode4 (val = 4).
 *                      - visited[Node 4] = cloneNode4.
 *                      - Loop through neighbors of Node 4: [Node 1, Node 3]
 *                        - neighbor = Node 1:
 *                          - Call cloneGraph(Node 1):
 *                            - Node 1 IS in visited. Return cloneNode1.
 *                          - cloneNode4->neighbors.push_back(cloneNode1).
 *                        - neighbor = Node 3:
 *                          - Call cloneGraph(Node 3):
 *                            - Node 3 IS in visited. Return cloneNode3.
 *                          - cloneNode4->neighbors.push_back(cloneNode3).
 *                      - Return cloneNode4.
 *                  - cloneNode3->neighbors.push_back(cloneNode4).
 *                - Return cloneNode3.
 *            - cloneNode2->neighbors.push_back(cloneNode3).
 *          - Return cloneNode2.
 *        - cloneNode1->neighbors.push_back(cloneNode2).
 *      - neighbor = Node 4:
 *        - Call cloneGraph(Node 4):
 *          - Node 4 IS in visited. Return visited[Node 4] (cloneNode4).
 *        - cloneNode1->neighbors.push_back(cloneNode4).
 *    - Return cloneNode1.
 * 
 * Result:
 * A fully deep-copied graph where all connections match the original structure.
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(V + E)
 * - V is the number of vertices, E is the number of edges.
 * - Each vertex is visited exactly once because we register it in the visited
 *   hash map.
 * - For each vertex, we iterate over all its adjacency list neighbors (sum of
 *   all adjacency lists is 2E for undirected graphs).
 * 
 * Space Complexity: O(V)
 * - The hash map stores V entries mapping original nodes to cloned nodes.
 * - The recursion call stack can reach a depth of O(V) in the worst-case (e.g.,
 *   a graph that is a single line / path).
 */

// Helper function to print adjacency list of a graph starting from a node (for testing)
void printGraphBFS(Node* node) {
    if (!node) return;
    unordered_map<Node*, bool> visited;
    queue<Node*> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << "Node " << curr->val << " neighbors: [";
        for (size_t i = 0; i < curr->neighbors.size(); ++i) {
            cout << curr->neighbors[i]->val;
            if (i < curr->neighbors.size() - 1) cout << ", ";
            if (!visited[curr->neighbors[i]]) {
                visited[curr->neighbors[i]] = true;
                q.push(curr->neighbors[i]);
            }
        }
        cout << "]\n";
    }
}

// Helper function to clean up graph memory
void deleteGraph(Node* node, unordered_map<Node*, bool>& visited) {
    if (!node || visited[node]) return;
    visited[node] = true;
    for (Node* neighbor : node->neighbors) {
        deleteGraph(neighbor, visited);
    }
    delete node;
}

int main() {
    // Create the test graph:
    // 1 --- 2
    // |     |
    // 4 --- 3
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);

    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};

    cout << "--- Original Graph Structure ---" << endl;
    printGraphBFS(n1);

    Solution solver;
    Node* cloned = solver.cloneGraph(n1);

    cout << "\n--- Cloned Graph Structure ---" << endl;
    printGraphBFS(cloned);

    // Verify deep copy address difference
    cout << "\nOriginal Node 1 address: " << n1 << endl;
    cout << "Cloned Node 1 address: " << cloned << endl;
    if (n1 != cloned && n1->val == cloned->val) {
        cout << "SUCCESS: Cloned node is a deep copy!" << endl;
    } else {
        cout << "FAILURE: Cloned node address or value mismatch." << endl;
    }

    // Clean up memory
    unordered_map<Node*, bool> visitedOriginal;
    deleteGraph(n1, visitedOriginal);
    unordered_map<Node*, bool> visitedCloned;
    deleteGraph(cloned, visitedCloned);

    return 0;
}
