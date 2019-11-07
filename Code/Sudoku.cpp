#include "Sudoku.hpp"

Sudoku::Sudoku(int square, int line, int column, int** table){
    Position** sudokuTable = new Position*[square];
    for(int i = 0; i < square; i++){
        sudokuTable[i] = new Position[square];
    }

    int pos = 0;
    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){
            sudokuTable[i][j].position = pos;
            sudokuTable[i][j].value = table[i][j];
            pos++;
        }
    }

    BuildGraph(square, line, column, sudokuTable);
}

void Sudoku::BuildGraph(int square, int line, int column, Position** table){
    this->V = square * square;
    this->adjList = vector<vector<int>>(V);

    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){            
            int k = (i < j) ? i+1 : j+1;
            int aux = k;
            for(; k < square; k++){
                if(k > i){
                    if(!existsEdge(table[i][j].position, table[k][j].position))
                        addEdge(table[i][j].position, table[k][j].position);
                }
                if(k > j)
                    if(!existsEdge(table[i][j].position, table[i][k].position))
                        addEdge(table[i][j].position, table[i][k].position);
                int maxLC = (line > column) ? line : column;
                //if(aux == k)
                for(int l = 0; l < square; l++){
                    if((int)i/line == (int)k/line && i != k){
                        if((int)j/column == (int)l/column && j != l){
                            if(!existsEdge(table[i][j].position, table[k][l].position))
                                addEdge(table[i][j].position, table[k][l].position);
                        }
                    }
                }
            }
        }
    }
}

void Sudoku::addEdge(int v1, int v2){
    this->adjList[v1].push_back(v2);
    this->adjList[v2].push_back(v1);
}

bool Sudoku::existsEdge(int v1, int v2){
    for(auto p : this->adjList[v1]){
        if(p == v2)
            return true;
    }

    return false;
}

void Sudoku::PrintGraph() { 
    for (int v = 0; v < this->V; v++){ 
        std::cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : this->adjList[v]) 
           std::cout << "-> " << x; 
        printf("\n"); 
    } 
}