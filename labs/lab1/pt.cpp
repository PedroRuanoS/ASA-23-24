#include <iostream>
#include <list>
#include <vector>

using namespace std;

list<int>* _graph;
vector<int> in_degree;
vector<int> out_degree;
int _V, _E;

void readGraph() {
    char comma;
    cin >> _V >> comma >> _E;  // Reading N and M separated by a comma
    _graph = new list<int>[_V];
    in_degree.resize(_V, 0);
    out_degree.resize(_V, 0);

    for (int i = 0; i < _E; i++) {
        int u, v;
        cin >> u >> v;
        _graph[u - 1].push_back(v - 1);
        out_degree[u - 1]++;
        in_degree[v - 1]++;
    }
}

void showHistogram(const vector<int>& degree) {
    vector<int> histogram(_V + 1, 0);
    for (int deg : degree) {
        histogram[deg]++;
    }
    for (int i = 0; i <= _V; i++) {
        if (histogram[i] > 0) {
            cout << i << ": " << histogram[i] << endl;
        }
    }
}

int main() {
    readGraph();

    // Showing histograms for out-degree and in-degree
    cout << "Histogram of friends:" << endl;
    showHistogram(out_degree);

    cout << "Histogram of being friend:" << endl;
    showHistogram(in_degree);

    delete[] _graph;
    return 0;
}
