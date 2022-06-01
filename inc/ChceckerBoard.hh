#ifndef CHECKER_HH
#define CHECKER_HH
#include <iostream>
#include <memory>
#include "CheckerBoardSquare.hh"
class Checker
{
private:
    size_t gridSize;
    CheckerBoardSquare *grid;
    std::shared_ptr<CheckerBoardSquare>();
    bool whitePiecePerspective;

private:
    int index(size_t xCoordinate, size_t yCoordinate) const;

public:
    CheckerBoard(int size, bool whitePiece);
    CheckerBoard(CheckerBoard &c);
    ~CheckerBoard();

    size_t size() const;
    // CheckerBoardSquare *operator[](size_t i);
    CheckerBoardSquare &operator()(size_t xCoordinate, size_t yCoordinate);
    void set_board();
    void flip_board();
    bool immobilized(CheckerBoardSquare &square) const;
    bool can_attack(CheckerBoardSquare &square) const;
    bool attack(CheckerBoardSquare &square, CheckerBoardSquare &attacked);
    bool move(CheckerBoardSquare &square, CheckerBoardSquare &destination);
    bool game_over() const;
};

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed);

#endif