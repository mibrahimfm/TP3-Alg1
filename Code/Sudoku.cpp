#include "Sudoku.hpp"

Sudoku::Sudoku(int square, int line, int column, int** table){

    this->sudokuTable = new Position*[square];
    for(int i = 0; i < square; i++){
        this->sudokuTable[i] = new Position[square];
    }

    int pos = 0;
    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){
            this->sudokuTable[i][j].position = pos;
            this->sudokuTable[i][j].value = table[i][j];
            this->sudokuTable[i][j].colored = sudokuTable[i][j].value != 0 ? true : false;
            pos++;
        }
    }

    this->buildGraph(square, line, column);
}

void Sudoku::buildGraph(int square, int line, int column){
    this->V = square * square;
    this->square = square;
    this->adjList = vector<vector<Position*>>(V);

    for(int i = 0; i < square; i++){
        for(int j = 0; j < square; j++){            
            int k = (i < j) ? i+1 : j+1;
            for(; k < square; k++){
                if(k > i){
                    if(!existsEdge(this->sudokuTable[i][j], this->sudokuTable[k][j]))
                        addEdge(&this->sudokuTable[i][j], &this->sudokuTable[k][j]); //Add edges to vertexes in same column
                }
                if(k > j)
                    if(!existsEdge(this->sudokuTable[i][j], this->sudokuTable[i][k]))
                        addEdge(&this->sudokuTable[i][j], &this->sudokuTable[i][k]); //Add edges to vertexes in same line
                for(int l = 0; l < square; l++){
                    if((int)i/line == (int)k/line && i != k){
                        if((int)j/column == (int)l/column && j != l){
                            if(!existsEdge(this->sudokuTable[i][j], this->sudokuTable[k][l]))
                                addEdge(&this->sudokuTable[i][j], &this->sudokuTable[k][l]); //Add edges to vertexes in same box
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

void Sudoku::FindSolution(){
    
    int indexMax = -1, formerIndexMax;

    bool available[this->square+1];
    for(int i = 0;i <= this->square; i++){
        available[i] = true;
    }

    for(int it = 0; it < this->V; it++){

        formerIndexMax = indexMax;   
        indexMax = this->nextNodeToColor(available);

        if(indexMax == formerIndexMax) //either a solution was found or it won't be found
            return;

        for(auto p : this->adjList[indexMax]){
            if(p->colored){            
                available[p->value] = false;
            }
        }

        this->assignValue(available, indexMax);

        for(int i = 0;i <= this->square; i++){
            available[i] = true;
        }
    }
}

int Sudoku::nextNodeToColor(bool* available){
    int ammountColored, maxColored = 0, indexMax = 0;

    for(int v = 0; v < this->V; v++){
        int auxLine = v / this->square;
        int auxColumn = v % this->square;
        ammountColored = 0;

        if(!this->sudokuTable[auxLine][auxColumn].colored){

            for(auto p : this->adjList[v]){
                if(p->colored){
                    if(available[p->value]){
                        ammountColored++;
                        available[p->value] = false;
                    }
                }
            }

            if(ammountColored > maxColored){
                maxColored = ammountColored;
                indexMax = v;
            }

        }

        for(int i = 0;i <= square; i++){
            available[i] = true;
        }

    }

    return indexMax;
}

void Sudoku::assignValue(bool* available, int indexMax){
            for(int i = 1; i <= this->square; i++){
            if(available[i]){
                int line = indexMax / this->square;
                int column = indexMax % this->square;
                this->sudokuTable[line][column].value = i;
                this->sudokuTable[line][column].colored = true;
                break;
            }
        }
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

void Sudoku::PrintSolution(){

    checkSolved();

    for(int i = 0; i < this->square; i++){
        for(int j = 0; j < this->square; j++){
            std::cout << this->sudokuTable[i][j].value << " ";
        }
        std::cout << std::endl;
    }

}

//The algorithm naturally will not create a conflict, nor will it put values greater than the available ones
//So it only needs to check if there is a 0 value on the table
void Sudoku::checkSolved(){ 
    for(int i = 0; i < this->square; i++){
        for(int j = 0; j < this->square; j++){
            if(this->sudokuTable[i][j].value == 0){
                std::cout << "Sem solucao" << std::endl;
                return;
            }
        }
    }

    std::cout << "solucao" << std::endl;
}