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
    int m_gridSize = 5;
    std::vector<std::shared_ptr<Square>> m_grid;
    bool m_whiteTurn;
    bool m_whitePerspective;

private:
    std::vector<std::shared_ptr<Square>> check_paths_men(int index);
    std::vector<std::shared_ptr<Square>> check_paths_king(int index);
    bool can_attack_men(int index);
    bool can_attack_king(int index);

public:
    CheckerBoard();
    CheckerBoard(CheckerBoard &c);
    ~CheckerBoard();

public:
    bool can_attack(int index);
    std::vector<std::shared_ptr<Square>> check_paths(int index);

public:
    int gridize(int x, int y) const;
    std::tuple<int, int> gridize(int index) const;
    void set_board();
    void flip_board();
    void turn_over();
    void clear();
    bool move(int idChosen, int idDest);
    void promote(int index);
    bool game_over() const;
    Square &getSquare(int index);
    std::shared_ptr<Square> operator[](int index);
};

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed);

#endif