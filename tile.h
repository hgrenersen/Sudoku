#pragma once

#include "std_lib_facilities.h"

#include "AnimationWindow.h"

#include "Widgets/Button.h"

class Tile : public TDT4102::Button{
    /*
    A class that represents a field on the Sudoku board which we want to fill
    with a value. The class inherits from the TDT4102 button class in order 
    to make it possible to interact with, i.e. we can fill in the numbers
    we know/hope belong in the field.
    */
    private:
        static constexpr int cellSize = 80; //The size of each tile

        int value; //The tile's value (int between 0 and 9, 0 if the cell is empty)
        int row; //The tile's row index, between 0 and 8
        int col; //The tile's column index, between 0 and 8

        int square; /*The number of the square the tile belongs to. Square 1 is in the top left 
        corner, 2 to the right of it, and 9 is in the bottom right corner. Initialized by 
        initialiseSquare()*/

        void initializeSquare(); /*Function to make sure the tile is marked as belonging to
        the correct square*/

        bool fixed = false; /*Variable to decide if the tile is fixed or not, i.e. if the
        player should be able to fill in a new value. If true, the value is not possible
        to change*/
        
    public:
        Tile(int v, int r, int c); 
        
        int getValue() {return value;};

        int getSquare() {return square;};

        bool getFixed() {return fixed;};

        void setValue(int v) {value=v;};

        void setFixed(bool f) {fixed=f;};

        
}; 
