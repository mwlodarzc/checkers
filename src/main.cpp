
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hh"
int main()
{
    Game *checkers = new Game();
    checkers->init("Checkers game", 0, 0, 1000, 1000, 0);
    while (checkers->running())
    {
        checkers->handleEvents();
        checkers->update();
        checkers->renderer();
    }
    checkers->clean();
    // int indexChosen = 0, indexDest = 0;
    // std::vector<std::shared_ptr<Square>> moves;
    // CheckerBoard board;
    // board.set_board();
    // std::cout << board << std::endl;
    // board.turn_over();
    // while (1)
    // {
    //     std::cout << "Index: " << std::endl;
    //     std::cin >> indexChosen;
    //     std::cout << indexChosen << std::endl;

    //     moves = board.check_paths(indexChosen);
    //     while (!moves.empty())
    //     {
    //         std::cout << "move (id): (" << moves.back()->getIndex() << ")" << std::endl;
    //         moves.pop_back();
    //     }
    //     // std::cout << "Destination: ";
    //     // std::cin >> z >> k;
    //     // if (!board.move(x, y, z, k))
    //     //     std::cerr << "fault!" << std::endl;
    //     // std::cout << board << std::endl;
    // }
    return EXIT_SUCCESS;
}