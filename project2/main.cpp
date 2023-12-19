#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> dfs(vector<vector<int>>& graph);
int dfs_visit(int v, vector<vector<int>>& graph, vector<int>& color, vector<int>& finish, int time);
int dfs_transposed(vector<vector<int>>& transposedGraph, vector<int>& finish);
void dfs_visit_transposed(int v, vector<vector<int>>& transposedGraph, vector<int>& color,vector<int>& pathLength);
int id = 1;
vector<int> ids;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> graph(n), transposedGraph(n);

    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x - 1].push_back(y - 1);
        transposedGraph[y - 1].push_back(x - 1);
    }

    // Perform DFS on the original graph
    vector<int> finish = dfs(graph);
    
    // Perform DFS on the transposed graph and find the longest path
    int longestPath = dfs_transposed(transposedGraph, finish);

    printf("%d\n", longestPath);

    return 0;
}

vector<int> dfs(vector<vector<int>>& graph) {
    int n = graph.size();
    int time = 0;
    vector<int> finish(n, 0);
    vector<int> color(n, 0); // 0: white, 1: gray, 2: black
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            time = dfs_visit(i, graph, color, finish, time);
        }
    }
    return finish;
}

int dfs_visit(int v, vector<vector<int>>& graph, vector<int>& color, vector<int>& finish, int time) {
    stack<int> s;
    s.push(v);

    while (!s.empty()) {
        int u = s.top();
        if (color[u] == 0) {
            color[u] = 1; 
            time++;
        }

        bool allAdjacentVisited = true;
        for (int adj : graph[u]) {
            if (color[adj] == 0) {
                s.push(adj);
                allAdjacentVisited = false;
                break;
            }
        }

        if (allAdjacentVisited) {
            s.pop();
            color[u] = 2; 
            finish[u] = time++;
        }
    }

    return time;
}

int dfs_transposed(vector<vector<int>>& transposedGraph, vector<int>& finish) {
    int n = transposedGraph.size();
    vector<int> color(n, 0);
    vector<int> pathLength(n, 0);
    vector<int> order(n);
    ids.resize(n, 0);
    iota(order.begin(), order.end(), 0);

    // Sorting vertices by finish time in descending order
    sort(order.begin(), order.end(), [&finish](int i, int j) { return finish[i] > finish[j]; });

    for (int i : order) {
        if (color[i] == 0) {
            dfs_visit_transposed(i, transposedGraph, color, pathLength);
            id++;
        }
    }

    return *max_element(pathLength.begin(), pathLength.end());
}

void dfs_visit_transposed(int v, vector<vector<int>>& transposedGraph, vector<int>& color, vector<int>& pathLength) {
    stack<int> s;
    s.push(v);
    
    while (!s.empty()) {
        int u = s.top();
        if (color[u] == 0) {
            color[u] = 1;
            ids[u] = id;
        }

        bool allAdjacentVisited = true;
        for (int adj : transposedGraph[u]) {
            if (color[adj] == 0) {
                s.push(adj);
                color[adj] = 1;
                ids[adj] = id;
                allAdjacentVisited = false;
                break;
            }
 
            if (ids[u] != ids[adj]) {
                pathLength[u] = max(pathLength[u], pathLength[adj] + 1);
            } else {
                pathLength[u] = max(pathLength[u], pathLength[adj]);
            }
        }

        if (allAdjacentVisited) {
            s.pop();
            color[u] = 2;
        }
    }
}
