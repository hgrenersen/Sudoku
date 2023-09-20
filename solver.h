#pragma once

#include "std_lib_facilities.h"

#include "sudokuBoard.h"

class Solver {
    private:
        vector<vector<int>> board;

        vector<vector<int>> solution;

        std::vector<std::vector<bool>> fixed;

        float k = 1;

        float lambda = 0.75;

        std::mt19937 gen;
        std::uniform_int_distribution<int> distribution;
    public:
        Solver(vector<vector<int>> b);

        int Q(vector<vector<int>> proposal);

        int ri(vector<vector<int>> proposal, int rowIndex);

        int ci(vector<vector<int>> proposal,int colIndex);

        double f(vector<vector<int>> proposal) {return 1/k*exp(-lambda*Q(proposal));}

        void initialize();

        vector<vector<int>> newProposal();

        vector<vector<int>> swapNumbers(int square, vector<vector<int>> boardToConsider);

        void nextBoard();

        void solve();

};