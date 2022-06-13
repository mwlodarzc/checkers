
#include <iostream>
#include "CheckerBoard.hh"
int main()
{
    int x, y, z, k;
    CheckerBoard board;
    board.set_board();
    std::cout << board << std::endl;
    board.flip_board();
    std::cout << board << std::endl;
    while (1)
    {
        std::cin >> x >> y >> z >> k;
        if (!board.move(x, y, z, k))
            std::cerr << "fault!" << std::endl;
        if (board.can_attack(board(z, k).getPiece()))
            std::cout << "Attack" << std::endl;
        std::cout << board << std::endl;
    }
    return EXIT_SUCCESS;
}