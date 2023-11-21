/*************************************
 * ASA 2022/2023 - Pedro T. Monteiro *
 *       projecto exemplo - P0       *
 *************************************/
#include <iostream>
#include <list>
#include <vector>

// Objectives:
// . how to read input
// . how to print output
// . how to use c++ containers
// . how to use an iterator

// using namespace std; // not using this explicitly pedagogically

unsigned int _V, _E;
std::list<int>* _fwrAdjList;
std::list<int>* _revAdjList;

//---------------------------------------------------------------
void readGraph() {
	//scanf("%d,%d", &_V, &_E);
	std::cin >> _V; std::cin.ignore(); std::cin >> _E;
	_fwrAdjList = new std::list<int>[_V];
	_revAdjList = new std::list<int>[_V];
	for (size_t i = 0; i < _E; i++) {
		int u, v;
		//scanf("%d %d", &u, &v);
		std::cin >> u >> v;
		_fwrAdjList[u-1].push_front(v-1);
		_revAdjList[v-1].push_front(u-1);
	}
}

//---------------------------------------------------------------
void computeDegrees(std::list<int>* _adjList) {
	std::vector<int> _hist;
	_hist.resize(_V);
	for (size_t i = 0; i < _V; i++) _hist[i] = 0;
	for (size_t i = 0; i < _V; i++) {
		_hist[_adjList[i].size()]++;
	}
	for (size_t i = 0; i < _V; i++) {
		std::cout << _hist[i] << std::endl;
	}
}

//---------------------------------------------------------------
void commonFriends() {
	for (size_t i = 0; i < _V; i++) {
		for (size_t j = 0; j < _V; j++) {
			// Alternative to the iterators would be to use set<int> intersects
			int c = 0;
			for (std::list<int>::iterator it_i = _fwrAdjList[i].begin(); it_i != _fwrAdjList[i].end(); it_i++) {
				for (std::list<int>::iterator it_j = _fwrAdjList[j].begin(); it_j != _fwrAdjList[j].end(); it_j++) {
					if ((*it_i)==(*it_j)) c++;
				}
			}
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
}

//---------------------------------------------------------------
int main() {
	// Read the graph
	readGraph();

	// First output
	std::cout << "Histograma 1" << std::endl;
	computeDegrees(_fwrAdjList);
	std::cout << "Histograma 2" << std::endl;
	computeDegrees(_revAdjList);

	// Second output
	commonFriends();

	return 0;
}