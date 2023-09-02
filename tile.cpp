#include "tile.h"

//Below is a map used to convert from row and column indices
//to square index
std::map<std::pair<int, int>, int> toSquareMap = {{std::pair<int, int>(0,0), 1},
{std::pair<int, int>(0,1), 2}, 
{std::pair<int, int>(0,2), 3},
{std::pair<int, int>(1,0), 4},
{std::pair<int, int>(1,1), 5},
{std::pair<int, int>(1,2), 6},
{std::pair<int, int>(2,0), 7},
{std::pair<int, int>(2,1), 8},
{std::pair<int, int>(2,2), 9}};

void Tile::initializeSquare() {
    square = toSquareMap.at(std::pair<int, int>(row/3, col/3));
}

Tile::Tile(int v, int r, int c) : Button({cellSize*c, cellSize*r}, cellSize, cellSize, "") {
    value=v;
    row = r;
    col = c;
    initializeSquare();
}