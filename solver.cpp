#include "solver.h"

Solver::Solver(vector<vector<int>> b){
    board=b;
    cout << "her kommer brettet";
    for(int i=0; i<9;i++) {
        for(int j=0; j<9; j++) {
            cout << board.at(i).at(j) << " ";

        }
        cout <<endl;
    }
};

int Solver::ri(int rowIndex){
    vector<int> row = board.at(rowIndex);
    
    std::sort(row.begin(), row.end());

    int fncVal=0;

    for(int i=1; i<=9; i++) {
        if(abs(row.at(i-1)-i)>0){
            fncVal+=1;
        }
    }
    
    return fncVal;
};

int Solver::ci(int colIndex) {
    vector <int> col(9, 0);

    for(int i=0; i<9; i++){
        col.at(i) = board.at(i).at(colIndex);
    }

    std::sort(col.begin(), col.end());

    int fncVal=0;

    for(int i=1; i<=9; i++) {
        if(abs(col.at(i-1)-i)>0){
            fncVal+=1;
        }
    }

    return fncVal;
   


};

int Solver::Q() {
    int objVal = 0;
    for(int i=0; i<9; i++) {
        objVal+=(ri(i)+ci(i));
    }
    return objVal;
}