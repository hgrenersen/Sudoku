#include "solver.h"

Solver::Solver(vector<vector<int>> b) : gen(std::random_device()()), distribution(1, 9){
    board=b;
    for(int i=0; i<9; i++) {
        vector<bool> row;
        for(int j=0; j<9; j++){ 
            if(board.at(i).at(j)!=0){
                row.emplace_back(1);
            }
            else {row.emplace_back(0);}
        }
        fixed.emplace_back(row);
    }
};

int Solver::ri(vector<vector<int>> proposal,int rowIndex){
    vector<int> row = proposal.at(rowIndex);
    
    std::sort(row.begin(), row.end());

    int fncVal=0;
    /*
    for(int i=1; i<=9; i++) {
        if(abs(row.at(i-1)-i)>0){
            fncVal+=1;
        }
    }
    */
   for(int i=1; i<=9; i++) {
        fncVal+=abs(row.at(i-1)-i);
   }
    
    return fncVal;
};

int Solver::ci(vector<vector<int>> proposal,int colIndex) {
    vector <int> col(9, 0);

    for(int i=0; i<9; i++){
        col.at(i) = proposal.at(i).at(colIndex);
    }

    std::sort(col.begin(), col.end());

    int fncVal=0;
    /*
    for(int i=1; i<=9; i++) {
        if(abs(col.at(i-1)-i)>0){
            fncVal+=1;
        }
    }
    */
    for(int i=1; i<=9; i++) {
        fncVal+=abs(col.at(i-1)-i);
    }

    return fncVal;
};

int Solver::Q(vector<vector<int>> proposal) {
    int objVal = 0;
    for(int i=0; i<9; i++) {
        objVal+=(ri(proposal, i)+ci(proposal,i));
    }
    return objVal;
};

void Solver::initialize() {
    vector<int> integers = {1,2,3,4,5,6,7,8,9};

    for (int squareRow = 0; squareRow < 3; squareRow++) {
        for (int squareCol = 0; squareCol < 3; squareCol++) {

            vector<int> numbersInSquare;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int val = board.at(squareRow * 3 + i).at(squareCol * 3 + j);

                    if (val!=0) {
                        numbersInSquare.emplace_back(val);
                    }
                }
                
            }

            vector<int> numbersToPlace;
            for (int num : integers) {
                if (find(numbersInSquare.begin(), numbersInSquare.end(), num) == numbersInSquare.end()) {
                    numbersToPlace.push_back(num);
                }
            }
        
            std::shuffle(numbersToPlace.begin(), numbersToPlace.end(), gen);

            int index = 0;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int val = board.at(squareRow * 3 + i).at(squareCol * 3 + j);

                    if (val==0) {
                        board.at(squareRow * 3 + i).at(squareCol * 3 + j) =numbersToPlace.at(index);
                        index++;
                    }
                }
                
            }

            
        }
    }

    for(int i=0; i<9;i++) {
        for(int j=0; j<9; j++) {
            cout << board.at(i).at(j) << " ";
        }
        cout <<endl;
    }

};

int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
};

vector<vector<int>> Solver::swapNumbers(int square, vector<vector<int>> boardToConsider){
    int squareRow = (square - 1) / 3;
    int squareCol = (square - 1) % 3;
    
    std::vector<std::pair<int, int>> nonFixedPositions;

    // Collect non-fixed positions within the chosen subgrid
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int row = squareRow * 3 + i;
            int col = squareCol * 3 + j;
            if (!fixed.at(row).at(col)) {
                nonFixedPositions.emplace_back(row, col);
            }
        }
    }

    // Ensure there are at least two non-fixed positions for a swap
    if (nonFixedPositions.size() < 2) {
        int newSquare = getRandomNumber(1,9);
        while(newSquare == square) {
            newSquare = getRandomNumber(1,9);
        }
        return swapNumbers(newSquare, boardToConsider ); // Not enough non-fixed numbers for a swap
    }

    // Randomly choose two different positions within the non-fixed positions
    int index1 = getRandomNumber(0, nonFixedPositions.size() - 1);
    int index2;
    do {
        index2 = getRandomNumber(0, nonFixedPositions.size() - 1);
    } while (index1 == index2);

    // Get the coordinates of the positions to swap
    int row1 = nonFixedPositions.at(index1).first;
    int col1 = nonFixedPositions.at(index1).second;
    int row2 = nonFixedPositions.at(index2).first;
    int col2 = nonFixedPositions.at(index2).second;

    // Swap the numbers at the selected positions

    std::swap(boardToConsider.at(row1).at(col1), boardToConsider.at(row2).at(col2));
    return boardToConsider;

};

vector<vector<int>> Solver::newProposal() {
    vector<vector<int>> newProp = board ;

    int square =getRandomNumber(1, 9);

    return swapNumbers(square, newProp);
};

void Solver::nextBoard() {
    vector<vector<int>> candidate = newProposal();

    if (Q(candidate)<Q(board) ){

        cout << Q(candidate) << endl;
        board = candidate;
    }
    else{
        double p = min(1.0, f(board)/f(candidate));

        std::uniform_real_distribution<double> zeroToOne(0.0, 1.0);

        if (p < zeroToOne(gen)) {
            board = candidate;
        }
    }

};

void Solver::solve(){
    int qVal = Q(board);

    int numOfIterations = 0;

    while(qVal!=0) {
        nextBoard();
        qVal = Q(board);
        //cout << "I iterasjon " << ++numOfIterations << " er funksjonsverdien" << qVal << endl;
        
        
    }

    
};