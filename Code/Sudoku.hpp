#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <vector>

using std::vector;

struct Position{
    int position;
    int value;
};

class Sudoku{
private:
    int V;
    void addEdge(int, int);
    vector<vector<int>> adjList;
public:
    Sudoku(int, int, int, int**);
    void BuildGraph(int, int, int, Position**);
    void PrintGraph();
};

#endif