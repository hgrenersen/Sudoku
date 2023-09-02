#pragma once

#include "std_lib_facilities.h"

#include "sudokuBoard.h"

class Solver {
    private:
        vector<vector<int>> board;

        vector<vector<int>> solution;
    public:
        Solver(vector<vector<int>> b);

        int Q();

        int ri(int rowIndex);

        int ci(int colIndex);


};