#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

// Function prototypes
void dfs(vector<vector<int>>& graph, vector<int>& finish);
void dfs_visit(int v, vector<vector<int>>& graph, vector<int>& color, vector<int>& finish, int& time);
void dfs_transposed(vector<vector<int>>& transposedGraph, vector<int>& finish, vector<int>& pathLength);
void dfs_visit_transposed(int v, vector<vector<int>>& transposedGraph, vector<int>& color, int& path, vector<int>& pathLength);

// Main function
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n), transposedGraph(n);

    // Building the graph and its transpose
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].push_back(y - 1);
        transposedGraph[y - 1].push_back(x - 1);
    }

    // Variables for DFS
    vector<int> finish(n, 0); // Finish times
    vector<int> pathLength(n, 0); // Path lengths for each vertex

    // Perform DFS on the original graph
    dfs(graph, finish);

    // Perform DFS on the transposed graph
    dfs_transposed(transposedGraph, finish, pathLength);

    // Find the maximum path length
    int maxPath = *max_element(pathLength.begin(), pathLength.end());
    cout << maxPath << endl;

    return 0;
}

// DFS function for the original graph
void dfs(vector<vector<int>>& graph, vector<int>& finish) {
    int n = graph.size();
    vector<int> color(n, 0); // 0: white, 1: gray, 2: black
    int time = 0;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            dfs_visit(i, graph, color, finish, time);
        }
    }
}

void dfs_visit(int v, vector<vector<int>>& graph, vector<int>& color, vector<int>& finish, int& time) {
    stack<int> s;
    s.push(v);
    color[v] = 1; // Gray

    while (!s.empty()) {
        int u = s.top();
        bool allAdjacentVisited = true;

        for (int adj : graph[u]) {
            if (color[adj] == 0) { // White
                s.push(adj);
                color[adj] = 1; // Gray
                allAdjacentVisited = false;
            }
        }

        if (allAdjacentVisited) {
            s.pop();
            color[u] = 2; // Black
            finish[u] = time++;
        }
    }
}

// DFS function for the transposed graph
void dfs_transposed(vector<vector<int>>& transposedGraph, vector<int>& finish, vector<int>& pathLength) {
    int n = transposedGraph.size();
    vector<int> color(n, 0);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);

    // Sorting vertices by finish time in descending order
    sort(order.begin(), order.end(), [&finish](int i, int j) { return finish[i] > finish[j]; });

    for (int i : order) {
        if (color[i] == 0) {
            int path = 0;
            dfs_visit_transposed(i, transposedGraph, color, path, pathLength);
        }
    }
}

void dfs_visit_transposed(int v, vector<vector<int>>& transposedGraph, vector<int>& color, int& path, vector<int>& pathLength) {
    stack<int> s;
    s.push(v);
    color[v] = 1; // Gray

    while (!s.empty()) {
        int u = s.top();
        bool allAdjacentVisited = true;

        for (int adj : transposedGraph[u]) {
            if (color[adj] == 0) { // White
                s.push(adj);
                color[adj] = 1; // Gray
                allAdjacentVisited = false;
            }
            pathLength[u] = max(pathLength[u], pathLength[adj] + 1);
        }

        if (allAdjacentVisited) {
            s.pop();
            color[u] = 2; // Black
            path = max(path, pathLength[u]);
        }
    }
}
