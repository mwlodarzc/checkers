#ifndef CHECKER_BOARD_HH
#define CHECKER_BOARD_HH
#include <iostream>
#include <memory>
#include <vector>
#include "Square.hh"
class CheckerBoard
{
private:
    size_t m_gridSize = 10;
    Square *m_grid;
    bool m_whiteTurn;
    bool m_whitePerspective;
    std::vector<std::shared_ptr<Piece>> m_lightPieces;
    std::vector<std::shared_ptr<Piece>> m_darkPieces;
    int index(size_t xCoordinate, size_t yCoordinate) const;

public:
    CheckerBoard();
    CheckerBoard(CheckerBoard &c);
    ~CheckerBoard();

public:
    void set_board();
    void flip_board();
    void turn_over();
    std::vector<std::shared_ptr<Piece>> get_pieces();
    void clear();
    bool can_attack(std::shared_ptr<Piece> piece);
    std::vector<std::shared_ptr<Square>> check_paths(std::shared_ptr<Piece> piece);
    bool move(size_t xChosen, size_t yChosen, size_t xDest, size_t yDest);
    bool promote(size_t xChosen, size_t yChosen);
    bool game_over() const;
    Square &operator()(size_t xCoordinate, size_t yCoordinate);
};

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed);

#endif