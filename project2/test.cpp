/*

    800 - 2 testes com Time Limit Exceeded 3 testes com Memory Limit Exceeded 7 testes com Wrong Answer 10 testes com Accepted

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    vector<vector<int>> L(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Adjusting for 0-based indexing
        graph[u].push_back(v);
    }

    // Base case
    L[n - 1] = {n - 1};

    // Recursive case
    for (int s = n - 2; s >= 0; --s) {
        L[s] = {s};
        for (int v : graph[s]) {
            if (v > s && L[s].size() < 1 + L[v].size()) {
                L[s] = {s};
                L[s].insert(L[s].end(), L[v].begin(), L[v].end());
            }
        }
    }

    // Find the longest path
    vector<int> longest_path = L[0];
    for (int i = 1; i < n; ++i) {
        if (L[i].size() > longest_path.size()) {
            longest_path = L[i];
        }
    }

    // Output the length of the longest path
    cout << longest_path.size() - 1 << endl;

    return 0;
}
