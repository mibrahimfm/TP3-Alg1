#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::set;

struct Position{
    int position;
    int value;
    bool colored;
};

class Sudoku{

    private:
        int V, square, ammoLine, ammoCol;
        Position** sudokuTable;
        vector<vector<Position*>> adjList;
        void buildGraph(int, int, int);
        void addEdge(Position*, Position*);
        bool existsEdge(Position, Position);
        int nextNodeToColor(bool*);
        void assignValue(bool*, int);
        void checkSolved();
    public:
        Sudoku(int, int, int, int**);
        void PrintGraph();
        void FindSolution();    
        void PrintSolution();
    
};

#endif