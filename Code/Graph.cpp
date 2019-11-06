#include "Graph.hpp"

Graph::Graph(int square, int line, int column, int** table){
    this->V = square * square;
    this->adjList = vector<vector<int>>(V);

    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){            
            int aux = table[i][j];
            int k = (i < j) ? i+1 : j+1;
            for(; k < square; k++){
                if(k > i)
                    addEdge(aux, table[k][j]);
                if(k > j)
                    addEdge(aux, table[i][k]);
            }
        }
    }
}

void Graph::addEdge(int v1, int v2){
    this->adjList[v1].push_back(v2);
    this->adjList[v2].push_back(v1);
}

void Graph::PrintGraph() { 
    for (unsigned int v = 1; v < this->V; v++){ 
        std::cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : this->adjList[v]) 
           std::cout << "-> " << x; 
        printf("\n"); 
    } 
}