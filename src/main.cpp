
#include <iostream>
#include <string>

#include "Game.hh"
int main(int argc, char *argv[])
{
    int botDepth = 3;
    bool playsWhite = true;
    std::string black("black");
    Game *checkers;
    if (argc > 1)
    {
        if (argv[1] == black)
            playsWhite = false;
    }
    if (argc > 2)
        botDepth = std::atoi(argv[2]);
    checkers = new Game(playsWhite, botDepth);
    checkers->init("Checkers game", 920, 0, 1000, 1000, 0);
    while (checkers->running())
    {
        checkers->handleEvents();
        checkers->update();
        checkers->renderer();
    }
    checkers->clean();
    return EXIT_SUCCESS;
}