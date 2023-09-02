#include "sudokuBoard.h"

SudokuBoard::SudokuBoard(int x, int y, int width, int height) :
 AnimationWindow{x, y, width*10, height*10, "Sudoku"}, width{width},
 height{height},  feedback{{cellSize*12, 7*cellSize}, 6*cellSize, 2*cellSize, ""} {
    
    //We start by filling up the matrix of tiles
    vector<shared_ptr<Tile>> row;
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {

            shared_ptr<Tile> newTile(new Tile(0,i, j));

            newTile->setCallback(std::bind(&SudokuBoard::cb_click, this)); /*Ensures that each 
            tile is possible to click and that values are updated when clicked*/

            add(*newTile); //Adds the tile to the window
            row.emplace_back(newTile); //Adds the tile to the matrix

            //Add tile to the Squares map:
            int square = newTile->getSquare();
            if (Squares.count(square)==0) { /*If we haven't come to one of the tiles in this
            square yet, we have to allocate memory for the vector containing the tiles of 
            the square*/
                vector<shared_ptr<Tile>> beginning;
                beginning.emplace_back(newTile);
                Squares.insert({square,beginning });
            }
            else{
                Squares.at(square).emplace_back(newTile); //Places the tile behind the previous
                //tiles from the same square
            }
        }
        Board.emplace_back(row); //Places the entire row into the matrix
        row.clear(); //Clears up the temporary row vector
    }

    //Drawing lines between squares
    for(int i=1; i<=2; i++) {
        this->draw_rectangle({(cellSize*3)*i-10, 0}, 10, 9*cellSize,
        TDT4102::Color::antique_white); //Vertical
        this->draw_rectangle({0, (cellSize*3)*i-10}, 9*cellSize, 10, 
        TDT4102::Color::antique_white); //Horizontal
    }

    //Placing buttons for filling the cells, to the right in the window
    int i=1;
    for(int j=1; j<=3; j++) {
        for(int k=1; k<=3; k++) {
            shared_ptr<TDT4102::Button> newBtn(new TDT4102::Button({cellSize*(10+2*k), 2*cellSize*(j-1)},
             2*cellSize, 2*cellSize, std::to_string(i)));

            newBtn->setCallback(std::bind(&SudokuBoard::cb_update_fill, this)); /*Ensures that the current
            fillValue is updated when we click the button*/

            fillButtons.emplace_back(newBtn);
            add(*newBtn); //Adds the button to the window
            i++;
        }
    }
    
    //Adds the button you click to check if you won
    checkButton.setCallback(std::bind(&SudokuBoard::cb_check, this));
    add(checkButton);

    //Adds the button to fix the fields
    fixButton.setCallback(std::bind(&SudokuBoard::cb_fix_or_reset, this));
    add(fixButton);


    //Adds the feedback field to the window
    feedback.setVisible(false);
    add(feedback);

    //Adds the button to solve the sudoku to the window

    add(solveButton);

    solveButton.setCallback(std::bind(&SudokuBoard::cb_solve, this));

   /*The rest of the function fills in a default, correctly solved board*/
   /*
   vector<int> numbers{8,2,7,1,5,4,3,9,6,
   9,6,5,3,2,7,1,4,8,
   3,4,1,6,8,9,7,5,2,
   5,9,3,4,6,8,2,7,1,
   4,7,2,5,1,3,6,8,9,
   6,1,8,9,7,2,4,3,5,
   7,8,6,2,3,5,9,1,4,
   1,5,4,7,9,6,8,2,3,
   2,3,9,8,4,1,5,6,7};

   int count=0;

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            changeValue(i, j, numbers.at(count));
            Board.at(i).at(j)->setLabel(std::to_string(numbers.at(count)));
            count+=1;
        }
    }
    cout <<"løk";
    */


};

void SudokuBoard::fix() {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(getValue(i, j)!=0) {
                Board.at(i).at(j)->setFixed(true);
            }
        }
    }
    fixButton.setLabel("Reset?");
};

void SudokuBoard::reset() {
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++) {
            shared_ptr<Tile> currentTile = Board.at(i).at(j);
            if(not currentTile->getFixed()) {
                changeValue(i, j, 0);
                currentTile->setLabel("");
            }
        }
    }
    fixButton.setLabel("Fix");
}

void SudokuBoard::printBoard() {
    cout << "+-----------------------+" <<endl;
    for(int i=0; i<9; i++) {
        cout << "| ";
        for(int j=0; j<9; j++) {
            cout << Board.at(i).at(j)->getValue() << " ";
            if((j+1) % 3 == 0) {
                cout << "| ";
            }
        }
        cout << endl;
        if((i+1) % 3==0){
           cout << "+-----------------------+" <<endl; 
        }
    }
};

bool SudokuBoard::checkRow(int row) {
    if (row < 0 || row>8) {
        throw "The row index is not valid";
    }
    bool result = true;
    
    vector<shared_ptr<Tile>> currentRow = Board.at(row);
    vector<int> counts(9, 0); /*Vector to store the number of occurences for each
    integer. The count of 1s is stored at the first index and so on*/
    for (int i=0; i<9; i++) {
        int value = currentRow.at(i)->getValue();
        counts.at(value-1)+=1;
    }

    /*Below we decide what numbers there are too many of and which there are 
    too few of*/
    for(int i=0; i<9;i++){
        if (counts.at(i) > 1) {
            cout << "There are too many " << i +1 << " in this row" <<endl;
            result = false;
        }
        if (counts.at(i)<1) {
            cout << "There are not enough " << i +1  << " in this row"<<endl;
            result = false;
        }
    }
    return result;
};

bool SudokuBoard::checkCol(int col) {
    if (col < 0 || col>8) {
        throw "The column index is not valid";
    }
    bool result = true;

    vector<int> colVals(9, 0); /*Vector used to store the values of the column
    that is checked*/

    for (int i = 0; i<9; i++) {
        colVals.at(i) = Board.at(i).at(col)->getValue();
    }

    vector<int> counts(9, 0);
    
    for (int i=0; i<9; i++) {
        int value = colVals.at(i);
        counts.at(value-1)+=1;
    }    

    for(int i=0; i<9;i++){
        if (counts.at(i) > 1) {
            cout << "There are too many " << i +1 << " in this column" <<endl;
            result = false;
        }
        if (counts.at(i)<1) {
            cout << "There are not enough " << i +1  << " in this column"<<endl;
            result = false;
        }
    }

    return result;
};

bool SudokuBoard::checkSquare(int squareNum) {
    if(squareNum<1 || squareNum>9) {
        throw "This isn't a valid index for a square, only integers in the range 1-9 are accepted";
    }

    bool result = true;

    vector<shared_ptr<Tile>> square = Squares.at(squareNum);

    vector<int> values;

    for(int i=0; i<9; i++) {
        values.emplace_back(square.at(i)->getValue());
    }

    vector<int> counts(9, 0);
    
    for (int i=0; i<9; i++) {
        int value = values.at(i);
        counts.at(value-1)+=1;
    }

    for(int i=0; i<9;i++){
        if (counts.at(i) > 1) {
            cout << "There are too many " << i +1 << " in this square" <<endl;
            result = false;
        }
        if (counts.at(i)<1) {
            cout << "There are not enough " << i +1  << " in this square"<<endl;
            result = false;
        }
    }

    return result;
};


std::string SudokuBoard::checkBoard() {
    std::string result = "";
    for(int i=0; i<9; i++) {
        bool rowResult = checkRow(i);
        if (not rowResult) {
            result = "There's something wrong in row "+std::to_string(i+1)+ "\n";
            return result;
        }
        bool colResult = checkCol(i);
        if (not colResult) {
            result = "There's something wrong in column "+std::to_string(i+1)+ "\n";
            return result;
        }
        bool squareResult = checkSquare(i+1);
        if (not squareResult) {
            result = "There's something wrong in square "+std::to_string(i+1)+ "\n";
            return result;
        }
        
    }
    return result;
};

void SudokuBoard::click() {
    Point coords{this->get_mouse_coordinates()};

    int col = coords.x/cellSize;
    int row = coords.y/cellSize;

    changeValue(row, col, currentFillValue);

    changeLabelTile(row, col);

};

void SudokuBoard::changeValue(int row, int col, int newValue) {
    if (newValue>9 || newValue<0) {
        throw "This value cannot be used in Sudoku";
    }
    else if (row < 0 || row>8) {
        throw "The row index is not valid";
    }
    else if (col < 0 || col>8) {
        throw "The column index is not valid";
    }
    else {
        if (not Board.at(row).at(col)->getFixed()) {
            Board.at(row).at(col)->setValue(newValue);
        }
    }
};

void SudokuBoard::changeLabelTile(int row, int col) {
    if(not fixButtonPressed) {
        string newLabel="";
        if (currentFillValue!=0) {
            newLabel=std::to_string(currentFillValue);
        }
        Board.at(row).at(col)->setLabel(newLabel);
        Board.at(row).at(col)->setLabelColor(TDT4102::Color::blue);
    }
    else{
        if (not Board.at(row).at(col)->getFixed()) {
            string newLabel="";
            if (currentFillValue!=0) {
                newLabel=std::to_string(currentFillValue);
                
            }
            Board.at(row).at(col)->setLabel(newLabel);
            Board.at(row).at(col)->setLabelColor(TDT4102::Color::white);
        }
    }

};

/*The map below is used to decide which new fill value the player wants
depending on where they clicked*/
std::map<std::pair<int, int>, int> fillMap = {{std::pair<int, int>(1,0), 1},
{std::pair<int, int>(2,0), 2}, 
{std::pair<int, int>(3,0), 3},
{std::pair<int, int>(1,1), 4},
{std::pair<int, int>(2,1), 5},
{std::pair<int, int>(3,1), 6},
{std::pair<int, int>(1,2), 7},
{std::pair<int, int>(2,2), 8},
{std::pair<int, int>(3,2), 9}};

void SudokuBoard::update_fill() {
    Point coords{this->get_mouse_coordinates()};

    int x = (coords.x-10*cellSize)/(2*cellSize);
    int y = coords.y/(2*cellSize);

    int newFillValue = fillMap.at(std::pair<int, int>(x, y));

    shared_ptr<TDT4102::Button> currentButton = fillButtons.at(newFillValue-1);
    
    if (newFillValue==currentFillValue) {
        currentFillValue=0;
        currentButton->setButtonColorDefault();
    }
    else {
        if (currentFillValue!=0) {
             fillButtons.at(currentFillValue-1)->setButtonColorDefault(); /*Sets the color of the 
             last button to the default color because it's now inactive*/
        }
        
        currentFillValue=newFillValue;
        currentButton->setButtonColor(TDT4102::Color::chocolate); /*Gives the active button
        chocolate colour*/
    }
};

void SudokuBoard::gameWon() {
    bool enoughTiles = true;
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(getValue(i, j)==0) {
                enoughTiles = false;
                feedback.setText("You haven't filled out all the cells");;
            };
        }
    }
    if (enoughTiles) {
        std::string result = checkBoard();
    
        if (result=="") {
            feedback.setText("YOU WON");
        }
        else {
            feedback.setText(result);
        }
    }
    feedback.setVisible(true);
};

void SudokuBoard::solve() {
    vector<vector<int>> board(9, vector<int>(9));

    for(int i=0; i<9; i++ ){
        for(int j=0; j<9; j++) {
            board.at(i).at(j) = this->getValue(i, j);
            cout << board.at(i).at(j) << " ";
        }
        cout <<endl;
    }
    
    Solver result = Solver(board);
    
    cout << "Dette er objektiv-funksjonen" << result.Q() <<endl;
};