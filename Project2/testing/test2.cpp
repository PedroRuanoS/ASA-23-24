/*

    300 - 1 teste com Time Limit Exceeded 3 testes com Runtime Error 5 testes com Accepted 13 testes com Wrong Answer

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

void topologicalSortUtil(int v, vector<bool>& visited, vector<int>& sortedNodes, const vector<vector<int>>& graph) {
    visited[v] = true;
    for (auto i : graph[v])
        if (!visited[i])
            topologicalSortUtil(i, visited, sortedNodes, graph);
    sortedNodes.push_back(v);
}

vector<int> topologicalSort(const vector<vector<int>>& graph, int n) {
    vector<int> sortedNodes;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, sortedNodes, graph);

    reverse(sortedNodes.begin(), sortedNodes.end());
    return sortedNodes;
}

int longestPath(const vector<vector<int>>& graph, int n) {
    vector<int> sortedNodes = topologicalSort(graph, n);
    vector<int> dist(n, numeric_limits<int>::min());
    dist[sortedNodes[0]] = 0;

    for (int node : sortedNodes) {
        for (auto successor : graph[node])
            dist[successor] = max(dist[successor], dist[node] + 1);
    }

    return *max_element(dist.begin(), dist.end());
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Adjust for 0-based indexing
        graph[u].push_back(v);
    }

    cout << longestPath(graph, n) << endl;
    return 0;
}
