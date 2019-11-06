#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using std::vector;

class Graph{
private:
    int V;
    void addEdge(int, int);
    vector<vector<int>> adjList;
public:
    Graph(int, int, int, int**);
    void PrintGraph();
};


#endif