#ifndef CHECKER_BOARD_HH
#define CHECKER_BOARD_HH
#include <iostream>
#include <memory>
#include <algorithm>
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

public:
    CheckerBoard(bool whitePov);
    CheckerBoard(CheckerBoard &c);
    CheckerBoard(const CheckerBoard &c);
    ~CheckerBoard();
    CheckerBoard &operator=(const CheckerBoard &c);

public:
    void set_board();
    void flip_board();
    void turn_over();
    void clear();
    std::vector<std::shared_ptr<Square>> check_paths(std::pair<int, int> coords);
    bool move(std::pair<int, int> coordsChosen, std::pair<int, int> coordsDest);
    bool game_over();
    Square &getSquare(std::pair<int, int> coords);
    std::vector<CheckerBoard> get_all_settings();
    int get_score();
    bool get_turn();
    const Square &getConstSquare(std::pair<int, int> coords) const;
};

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed);

#endif