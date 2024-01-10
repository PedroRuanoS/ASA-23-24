/*

    800 - 1 teste com Time Limit Exceeded 3 testes com Runtime Error 8 testes com Wrong Answer 10 testes com Accepted

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(int node, const vector<vector<int>>& graph, vector<int>& memo, vector<bool>& visited) {
    if (visited[node]) {
        return 0; // In case of a cycle, do not continue further in this path
    }

    if (memo[node] != -1) {
        return memo[node];
    }

    visited[node] = true;
    int max_dist = 0;

    for (int neighbor : graph[node]) {
        max_dist = max(max_dist, dfs(neighbor, graph, memo, visited) + 1);
    }

    visited[node] = false; // Mark the node as unvisited for other paths
    memo[node] = max_dist;
    return max_dist;
}

int findLongestPath(const vector<vector<int>>& graph, int n) {
    vector<int> memo(n, -1);
    int longest_path = 0;

    for (int i = 0; i < n; i++) {
        vector<bool> visited(n, false);
        longest_path = max(longest_path, dfs(i, graph, memo, visited));
    }

    return longest_path;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1); // Adjust for 0-based indexing
    }

    cout << findLongestPath(graph, n) << endl;
    return 0;
}
