#include "Sudoku.hpp"

Sudoku::Sudoku(int square, int line, int column, int** table){
    this->sudokuTable = new Position*[square];
    for(int i = 0; i < square; i++){
        this->sudokuTable[i] = new Position[square];
    }

    int pos = 0;
    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){
            sudokuTable[i][j].position = pos;
            sudokuTable[i][j].value = table[i][j];
            sudokuTable[i][j].colored = sudokuTable[i][j].value != 0 ? true : false;
            pos++;
        }
    }

    BuildGraph(square, line, column);
}

void Sudoku::BuildGraph(int square, int line, int column){
    this->V = square * square;
    this->square = square;
    this->adjList = vector<vector<Position*>>(V);

    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){            
            int k = (i < j) ? i+1 : j+1;
            for(; k < square; k++){
                if(k > i){
                    if(!existsEdge(this->sudokuTable[i][j], this->sudokuTable[k][j]))
                        addEdge(&this->sudokuTable[i][j], &this->sudokuTable[k][j]);
                }
                if(k > j)
                    if(!existsEdge(this->sudokuTable[i][j], this->sudokuTable[i][k]))
                        addEdge(&this->sudokuTable[i][j], &this->sudokuTable[i][k]);
                for(int l = 0; l < square; l++){
                    if((int)i/line == (int)k/line && i != k){
                        if((int)j/column == (int)l/column && j != l){
                            if(!existsEdge(this->sudokuTable[i][j], this->sudokuTable[k][l]))
                                addEdge(&this->sudokuTable[i][j], &this->sudokuTable[k][l]);
                        }
                    }
                }
            }
        }
    }
}

void Sudoku::addEdge(Position* p1, Position* p2){
    this->adjList[p1->position].push_back(p2);
    this->adjList[p2->position].push_back(p1);
}

bool Sudoku::existsEdge(Position p1, Position p2){
    for(auto p : this->adjList[p1.position]){
        if(p->position == p2.position)
            return true;
    }
    return false;
}

void Sudoku::PrintGraph() { 
    for (int v = 0; v < this->V; v++){ 
        std::cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : this->adjList[v]) 
           std::cout << "-> " << x->position; 
        printf("\n"); 
    } 
}

void Sudoku::FindSolution(){
    

    bool available[this->square+1];
    for(int i = 0;i <= square; i++){
        available[i] = true;
    }

    for(int it = 0; it < this->V; it++){
        int indexMax = this->NextNodeToColor();
        

        for(auto p : this->adjList[indexMax]){
            if(p->colored){            
                available[p->value] = false;
            }
        }

        for(int i = square; i > 0; i--){
            if(available[i]){
                int line = indexMax / this->square;
                int column = indexMax % this->square;
                this->sudokuTable[line][column].value = i;
                this->sudokuTable[line][column].colored = true;
                break;
            }
        }

        for(int i = 0;i <= square; i++){
            available[i] = true;
        }
    }
}

int Sudoku::NextNodeToColor(){
    int ammoColored, maxColored = 0, indexMax = 0;

    for(int v = 0; v < this->V; v++){
        int auxLine = v / this->square;
        int auxColumn = v % this->square;
        ammoColored = 0;
        if(!this->sudokuTable[auxLine][auxColumn].colored){
            for(auto p : this->adjList[v]){
                if(p->colored){
                    ammoColored++;
                }
            }
            if(ammoColored > maxColored){
                maxColored = ammoColored;
                indexMax = v;
            }
        }

    }

    return indexMax;
}

void Sudoku::PrintSolution(){
    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){
            std::cout << this->sudokuTable[i][j].value << " ";
        }
        std::cout << std::endl;
    }
}