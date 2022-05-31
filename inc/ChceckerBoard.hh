#ifndef CHECKER_BOARD_HH
#define CHECKER_BOARD_HH
#include <iostream>
#include "CheckerBoardSquare.hh"
class CheckerBoard
{
private:
    size_t gridSize;
    CheckerBoardSquare *grid;
    int index(size_t xCoordinate, size_t yCoordinate);

public:
    CheckerBoard(int size);
    CheckerBoard(CheckerBoard &c);
    ~CheckerBoard();

    // game methods
    size_t size();
    CheckerBoardSquare *operator[](size_t i);
    CheckerBoardSquare &operator()(size_t x, size_t y);
    void set_board();
    void flip_board();
    bool move(size_t xCoordinate, size_t yCoordinate);
};

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed);

#endif