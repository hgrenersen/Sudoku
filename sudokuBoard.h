#pragma once

#include "std_lib_facilities.h"

#include "AnimationWindow.h"
#include "widgets/TextInput.h"

#include "tile.h"

#include "solver.h"

class SudokuBoard : public AnimationWindow {
    /*
    A class used to represent a sudoku board. The class has a number
    of tiles, which together form the board. The class also inherits from
    AnimationWindow and has several GUI elements in order to make the
    game (marginally) more aesthetically pleasing to play.
    */
    private:
        vector<vector<shared_ptr<Tile>>> Board; /*A vector of vectors (matrix) that 
        contains pointers to the tiles on the board.*/

        std::map<int, vector<shared_ptr<Tile>>> Squares; /*A map that stores a vector
        of pointers to all tiles that belong to a given square. Keys range from 1 to 9*/

        vector<shared_ptr<TDT4102::Button>> fillButtons; /*A vector of pointers to 
        the buttons on the right side of the window, used to choose which value 
        we should fill the fields we click on with
        */

        int currentFillValue = 0; /*The current value which we want to fill a cell with
        which is decided by the buttons to the right*/

        TDT4102::Button checkButton=TDT4102::Button({cellSize*(12), 6*cellSize},
        6*cellSize, cellSize, "Check?");//Button used to check the player's solution

        const int width; //The width of the window
        const int height; //The height of the window

        static constexpr int cellSize = 80;

        TextInput feedback; //A TextInput widget used to give feedback on the player's solution

        TDT4102::Button fixButton = TDT4102::Button({0, 9*cellSize}, cellSize*9, cellSize*3/2, "Fix");

        bool fixButtonPressed = false; /*Bool to determine if we're in the "fill first cells" mode,
        or "let's solve this" mode*/

        TDT4102::Button solveButton = TDT4102::Button({9*cellSize, 9*cellSize}, 
        cellSize*3, cellSize*3/2, "Solve?");

    public:
        SudokuBoard(int x, int y, int width, int height);

        void cb_fix_or_reset() {
            if (fixButtonPressed) {
                fixButtonPressed=false;
                this->reset();
            }
            else {
                fixButtonPressed = true;
                this->fix();
            }};

        void fix(); /*Function that ensures that cells that were filled out
        before the fix button was pressed, become fixed*/

        void reset(); /*Resets the board to only the fixed values*/

        void printBoard(); //Prints the board, used for testing

        bool checkRow(int row); /*Checks that the row on index row contains all digits from
        1 to 9*/

        bool checkCol(int col); /*Checks that the column on index col contains all 
        digits from 1 to 9*/

        bool checkSquare(int squareNum); /*Checks that the square with index squareNum contains
        all digits from 1 to 9*/

        std::string checkBoard(); /*Combines checkRow(), checkCol() and checkSquare() to verify
        the solution, and gives a feedback about whether the game is won, for which the result is
        "", and otherwise returns a string describing where the first violation of the rules is 
        found*/

        int getValue(int row, int col) {return Board.at(row).at(col)->getValue();};
        //Returns the value at indices row and col in the matrix of tiles

        void changeValue(int row, int col, int newValue); /*Sets the value of the tile at indices
        row and col to have the value newValue*/

        void changeLabelTile(int row, int col); /*Updates the label of a tile with the new
        fill value*/

        void cb_click() {this->click();};
        
        void click(); /*Uses setLabelTile() and changeValue() to update a tile that
        is clicked on so that it matches with the selected value*/

        void cb_update_fill() {this->update_fill();};

        void update_fill(); /*Function that updates the color of the buttons on the 
        right hand side, so that it's easier to see the selected button*/

        void gameWon(); /*Function to check whether the player has won the game
        and update the feedback accordingly. This function also checks that all fields
        are filled, and makes use of checkBoard()*/
        
        void cb_check() {gameWon();};

        void solve() ;

        void cb_solve() {solve();};
};