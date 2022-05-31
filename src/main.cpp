#include <iostream>
#include "ChceckerBoard.hh"

int main()
{
    CheckerBoard board(8);
    std::cout << board << std::endl;
    board.flip_board();
    std::cout << board << std::endl;

    return EXIT_SUCCESS;
}