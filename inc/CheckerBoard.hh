#ifndef CHECKER_BOARD_HH
#define CHECKER_BOARD_HH
#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include <tuple>
#include "Square.hh"
class CheckerBoard
{
private:
    int m_gridSize = 10;
    Square m_grid[10][10];
    bool m_whiteTurn;
    bool m_whitePerspective;

private:
    // std::vector<std::shared_ptr<Square>> check_paths_men(std::pair<int, int> coords);
    // std::vector<std::shared_ptr<Square>> check_paths_king(std::pair<int, int> coords);
    // bool can_attack_men(std::pair<int, int> coords);
    // bool can_attack_king(std::pair<int, int> coords);
    void promote(std::pair<int, int> coords);

public:
    CheckerBoard();
    CheckerBoard(CheckerBoard &c);
    ~CheckerBoard();

public:
    // bool can_attack(std::pair<int, int> coords);
    std::vector<std::shared_ptr<Square>> check_paths(std::pair<int, int> coords);

public:
    void set_board();
    void flip_board();
    void turn_over();
    void clear();
    bool move(std::pair<int, int> coordsChosen, std::pair<int, int> coordsDest);
    bool game_over() const;
    Square &getSquare(std::pair<int, int> coords);
    std::shared_ptr<Square> operator[](std::pair<int, int> coords);
};

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed);

#endif