#include <list>
#include <vector>
#include <iostream>

using namespace std;

list<int>* _graph;
list<int>* _graphT;
int _V, _E;

void readGraph() {
    cin >> _V;
    cin.ignore();
    cin >> _E;
    _graph = new list<int>[_V];
    _graphT = new list<int>[_V];
    for (int i=0; i < _E; i++) {
        int u, v;
        cin >> u;
        cin >> v;
        _graph[u-1].push_front(v-1);
        _graphT = new list<int>[_V];
    }
}

void showHistogram(list<int>* graph, int V) {
    for (int i=0; i < V; i++) {
        int counter = 0;
        for (int j=0; j < V; j++) {
            if (graph[j].size() == i)
                counter++;
        }
        cout << counter << endl;
    }
}

void showHistogramOtherImplementation(list<int>* graph, int V) {
    vector<int> histogram;
    histogram.resize(V);
    for (int i=0; i < V; i++)
        histogram[i] = 0;
    for (int i=0; i < V; i++) 
        histogram[graph[i].size()]++;
    for (int i=0; i < V; i++)
        cout << histogram[i] << endl;
}

void commonFriends() {
    for (int i=0; i < _V; i++) {
        for (int j=0; i < _V; j++) {
            int counter = 0;
            for (list<int>::iterator it_i = _graph[i].begin();
                it_i != _graph[i].end(); it_i++) {
                for (list<int>::iterator it_j = _graph[j].begin();
                    it_j != _graph[j].end(); it_j++) {
                    if (*it_i == *it_j)
                        counter++;
                }
            }
            cout << counter << " ";
        }
        cout << endl;
    }
}

int main() {
    readGraph();
    cout << "Histograma 1" << endl;
    showHistogram(_graph, _V);
    cout << "Histograma 2" << endl;
    showHistogram(_graphT, _V);
    commonFriends();
    return 0;
}