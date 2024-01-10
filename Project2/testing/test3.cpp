/*

    300 - 3 testes com Time Limit Exceeded 3 testes com Runtime Error 4 testes com Memory Limit Exceeded 5 testes com Accepted 7 testes com Wrong Answer

*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void DFS(const vector<vector<int>>& graph, int v, set<int>& seen, vector<int>& path, vector<vector<int>>& paths) {
    seen.insert(v);
    path.push_back(v);

    bool isLeaf = true;
    for (auto t : graph[v]) {
        if (seen.find(t) == seen.end()) {
            isLeaf = false;
            DFS(graph, t, seen, path, paths);
        }
    }

    if (isLeaf) {
        paths.push_back(path);
    }

    path.pop_back();
    seen.erase(v);
}

int findLongestPathLength(const vector<vector<int>>& graph, int n) {
    vector<vector<int>> allPaths;
    for (int v = 0; v < n; v++) {
        set<int> seen;
        vector<int> path;
        DFS(graph, v, seen, path, allPaths);
    }

    int longestPath = 0;
    for (const auto& p : allPaths) {
        longestPath = max(longestPath, static_cast<int>(p.size()));
    }
    return longestPath - 1; // Subtract 1 because the path length is number of nodes - 1
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

    cout << findLongestPathLength(graph, n) << endl;
    return 0;
}
