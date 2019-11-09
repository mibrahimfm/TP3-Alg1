#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <vector>

using std::vector;

struct Position{
    int position;
    int value;
    bool colored;
};

class Sudoku{
private:
    int V, square;
    Position** sudokuTable;
    void addEdge(Position*, Position*);
    bool existsEdge(Position, Position);
    vector<vector<Position*>> adjList;
public:
    Sudoku(int, int, int, int**);
    void BuildGraph(int, int, int);
    void PrintGraph();
    void FindSolution();
    void PrintSolution();
};

#endif