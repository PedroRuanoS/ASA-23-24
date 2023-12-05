#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        // Adjusting for 0-based index as C++ uses 0-based indexing
        adj[v - 1].push_back(w - 1);
    }

    // Utility function for finding the longest path using DFS
    int longestPathDFS(int v, vector<bool>& visited, vector<bool>& currentPath, int currentDepth) {
        visited[v] = true;
        currentPath[v] = true;

        int maxDepth = currentDepth;
        for (int i : adj[v]) {
            if (!visited[i]) {
                maxDepth = max(maxDepth, longestPathDFS(i, visited, currentPath, currentDepth + 1));
            } else if (currentPath[i]) {
                // Cycle detected, so ignore this path
                continue;
            }
        }

        // Remove from current path
        currentPath[v] = false;
        return maxDepth;
    }

    // Function to find the longest path in the graph
    int longestPath() {
        int maxDepth = 0;

        for (int i = 0; i < V; i++) {
            vector<bool> visited(V, false);
            vector<bool> currentPath(V, false);
            maxDepth = max(maxDepth, longestPathDFS(i, visited, currentPath, 1));
        }

        return maxDepth;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g.addEdge(x, y);
    }

    cout << g.longestPath() << endl;

    return 0;
}
