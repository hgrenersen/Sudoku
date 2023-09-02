#include "std_lib_facilities.h"

#include "tile.h"

#include "sudokuBoard.h"

int main() {

    constexpr int width = 750;
	constexpr int height = 500;

	Point startPoint{ 40,40 };

    TDT4102::Button lok{startPoint, 100, 100, ""};

    //void setButtonColorDefault() {buttonColor = nk_rgba(50,50,50,255);}

    SudokuBoard sw{startPoint.x, startPoint.y, width, height};

    sw.wait_for_close();

    return 0;
}