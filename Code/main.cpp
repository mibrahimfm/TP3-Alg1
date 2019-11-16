#include <iostream>
#include <fstream>
#include <string.h>
#include "Sudoku.hpp"
//#include <chrono>

//using namespace std::chrono;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;


int main(int argc, char** argv){
    if(argc > 1){ //Checks if the file name was passed as a program parameter

        string fileName = argv[1];
    
        ifstream input(fileName);

        int square, line, column;
        int **matrix;


        if(input.is_open()){
            input >> square  >> column >> line;

            matrix = new int*[square];
            for(int i = 0; i < square; i++){
                matrix[i] = new int[square];
            }
            
            for(int i = 0; i < square; i++){
                for(int j = 0; j < square; j++){
                    input >> matrix[i][j];
                }
            }

            Sudoku s(square, line, column, matrix);
            //s.PrintGraph();
            s.FindSolution();
            s.PrintSolution();
        }
        else{
            cout << "Couldn't open file " << fileName << 
                ", please check if the file name is correct and if it actually exists" << endl;;
        }
    }
    else{
        cout << "Please pass a file name as a parameter to the program" << endl;
    }
     
}