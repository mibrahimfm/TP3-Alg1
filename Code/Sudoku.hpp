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
    void addEdge(Position*, Position*);
    bool existsEdge(Position, Position);
    vector<vector<Position*>> adjList;
public:
    Sudoku(int, int, int, int**);
    void BuildGraph(int, int, int);
    void PrintGraph();
    void FindSolution();
    int NextNodeToColor(bool*);
    void PrintSolution();
    void AssignValue(bool*, int);
    void checkSolved();
};

#endif