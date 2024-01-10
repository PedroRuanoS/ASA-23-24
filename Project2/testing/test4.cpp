#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph {
    int V; // Number of vertices
    list<int> *adj; // Adjacency list
    list<int> *transposeAdj; // Transposed adjacency list

    void DFSUtil(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited, Stack);
        Stack.push(v);
    }

    void fillOrder(int v, vector<bool> &visited, stack<int> &Stack) {
        visited[v] = true;
        for (auto i = transposeAdj[v].begin(); i != transposeAdj[v].end(); ++i)
            if (!visited[*i])
                fillOrder(*i, visited, Stack);

        Stack.push(v);
    }

    void transpose() {
        transposeAdj = new list<int>[V];
        for (int v = 0; v < V; v++)
            for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
                transposeAdj[*i].push_back(v);
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    ~Graph() {
        delete[] adj;
        delete[] transposeAdj;
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    int findSCCs() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                DFSUtil(i, visited, Stack);

        transpose();

        fill(visited.begin(), visited.end(), false);
        int maxPath = 0;
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                stack<int> componentStack;
                fillOrder(v, visited, componentStack);
                int componentSize = componentStack.size();
                maxPath = max(maxPath, componentSize);
            }
        }

        return maxPath;
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

    cout << g.findSCCs() << endl;
    return 0;
}
