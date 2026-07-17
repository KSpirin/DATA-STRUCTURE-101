/**
 * @file no3_transitive_closure.cpp
 * @brief Custom Transitive Closure using Warshall's Algorithm
 * @difficulty Medium / Academic Core
 *
 * Problem Description:
 * Given a directed graph represented by an adjacency matrix of size V x V,
 * determine its transitive closure (reachability matrix).
 * In the reachability matrix TC, TC[i][j] = 1 if there exists a directed path of
 * length >= 1 from vertex i to vertex j, and 0 otherwise.
 * Implement Warshall's Algorithm to solve this in O(V^3) time.
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class WarshallTransitiveClosure {
public:
    /**
     * @brief Computes the transitive closure of a directed graph using Warshall's Algorithm.
     * 
     * @param adjMatrix The V x V adjacency matrix of the graph.
     *                  adjMatrix[i][j] = 1 if edge i -> j exists, 0 otherwise.
     * @return vector<vector<int>> The V x V transitive closure matrix.
     */
    vector<vector<int>> computeTransitiveClosure(const vector<vector<int>>& adjMatrix) {
        int V = adjMatrix.size();
        
        // Initialize the transitive closure matrix with the adjacency matrix
        vector<vector<int>> tc = adjMatrix;

        // Warshall's Algorithm:
        // In each iteration of the outer loop (k), we check if vertex k can be
        // used as an intermediate vertex in a path between any vertex i and j.
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    // tc[i][j] is 1 if there's already a path i -> j,
                    // OR if there is a path from i -> k AND a path from k -> j.
                    tc[i][j] = tc[i][j] || (tc[i][k] && tc[k][j]);
                }
            }
        }
        return tc;
    }

    /**
     * @brief Helper to display a matrix on the console.
     */
    void printMatrix(const vector<vector<int>>& matrix, const vector<char>& labels) {
        int V = matrix.size();
        cout << "    ";
        for (char label : labels) {
            cout << label << "  ";
        }
        cout << "\n";
        for (int i = 0; i < V; ++i) {
            cout << labels[i] << "   ";
            for (int j = 0; j < V; ++j) {
                cout << matrix[i][j] << "  ";
            }
            cout << "\n";
        }
        cout << endl;
    }
};

/**
 * ============================================================================
 * MANUAL DRY-RUN TRACE (MATCHING LECTURE SLIDES)
 * ============================================================================
 * Graph Vertices: A=0, B=1, C=2, D=3
 * Labels mapping: [A, B, C, D]
 * 
 * Initial Adjacency Matrix R^(0):
 *     A  B  C  D
 * A   0  0  1  0  (Edge A -> C)
 * B   1  0  0  1  (Edges B -> A, B -> D)
 * C   0  0  0  0  (No outgoing edges)
 * D   0  1  0  0  (Edge D -> B)
 * 
 * 1. k = 0 (Vertex A):
 *    - Check paths going through A as intermediate node.
 *    - We look for nodes i such that R[i][A] == 1, and nodes j such that R[A][j] == 1.
 *    - i = B (R[B][A]=1), j = C (R[A][C]=1).
 *    - Update: R[B][C] = R[B][C] || (R[B][A] && R[A][C]) = 0 || (1 && 1) = 1.
 *    - Matrix R^(A):
 *          A  B  C  D
 *      A   0  0  1  0
 *      B   1  0  1  1  <-- R[B][C] updated to 1 (Path: B -> A -> C)
 *      C   0  0  0  0
 *      D   0  1  0  0
 * 
 * 2. k = 1 (Vertex B):
 *    - Check paths going through B as intermediate node.
 *    - Nodes with edges to B: D (R[D][B]=1).
 *    - Nodes reachable from B: A, C, D (R[B][A]=1, R[B][C]=1, R[B][D]=1).
 *    - Paths created: D -> B -> A, D -> B -> C, D -> B -> D.
 *    - Update: R[D][A] = 1, R[D][C] = 1, R[D][D] = 1.
 *    - Matrix R^(B):
 *          A  B  C  D
 *      A   0  0  1  0
 *      B   1  0  1  1
 *      C   0  0  0  0
 *      D   1  1  1  1  <-- Row D updated (Paths: D->B->A, D->B->C, D->B->D)
 * 
 * 3. k = 2 (Vertex C):
 *    - Check paths going through C as intermediate node.
 *    - Since C has no outgoing edges (no j exists such that R[C][j] == 1), no changes.
 *    - Matrix R^(C) = R^(B).
 * 
 * 4. k = 3 (Vertex D):
 *    - Check paths going through D as intermediate node.
 *    - Nodes with edges to D: B (R[B][D]=1) and D (R[D][D]=1).
 *    - Nodes reachable from D: A, B, C, D (all of row D is 1).
 *    - Paths created from B: B -> D -> A, B -> D -> B, B -> D -> C, B -> D -> D.
 *    - Update: R[B][A]=1, R[B][B]=1, R[B][C]=1, R[B][D]=1. (R[B][B] is the key change here).
 *    - Matrix R^(D) (Final Transitive Closure):
 *          A  B  C  D
 *      A   0  0  1  0
 *      B   1  1  1  1  <-- R[B][B] updated to 1 (Cycle detected: B -> D -> B)
 *      C   0  0  0  0
 *      D   1  1  1  1
 * 
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Time Complexity: O(V^3)
 * - Where V is the number of vertices. We use three nested loops, each running V times.
 * 
 * Space Complexity: O(V^2)
 * - To store the transitive closure matrix. 
 * - Note: Can be solved in-place, modifying the adjacency matrix directly, requiring O(1) auxiliary space.
 */

int main() {
    // Adjacency Matrix from slides example
    vector<vector<int>> adjMatrix = {
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 1, 0, 0}
    };
    vector<char> labels = {'A', 'B', 'C', 'D'};

    WarshallTransitiveClosure solver;

    cout << "=== Adjacency Matrix (Input) ===" << endl;
    solver.printMatrix(adjMatrix, labels);

    vector<vector<int>> tc = solver.computeTransitiveClosure(adjMatrix);

    cout << "=== Transitive Closure Matrix (Warshall's Output) ===" << endl;
    solver.printMatrix(tc, labels);

    return 0;
}
