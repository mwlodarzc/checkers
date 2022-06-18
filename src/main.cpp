
#include <iostream>
#include "Game.hh"
int main()
{
    Game *checkers = new Game();
    checkers->init("Checkers game", 920, 0, 1000, 1000, 0);
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
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <iostream>

// int main(int argc, char *argv[])
// {

//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window *w = SDL_CreateWindow("Hi", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
//     SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

//     SDL_Texture *s = NULL;
//     SDL_Surface *srfc;
//     srfc = IMG_Load("images/white_king.png"); // LOADS A TEXTURE DIRECTLY FROM THE IMAGE
//     s = SDL_CreateTextureFromSurface(r, srfc);
//     if (s == NULL)
//     {
//         std::cout << "FAILED TO FIND THE IMAGE" << std::endl; // we did this to check if IMG_LoadTexture found the image, if it showed this message in the cmd window (the black system-like one) then it means that the image can't be found
//     }
//     SDL_Rect s_rect; // CREATES THE IMAGE'S SPECS
//     s_rect.x = 100;  // just like the window, the x and y values determine it's displacement from the origin which is the top left of your window
//     s_rect.y = 100;
//     s_rect.w = 640; // width of the texture
//     s_rect.h = 480; // height of the texture

//     // adds 2 seconds to the past time you got and waits for the present time to surpass that

//     SDL_RenderClear(r);
//     SDL_RenderCopy(r, s, NULL, &s_rect); // THE NULL IS THE AREA YOU COULD USE TO CROP THE IMAGE
//     SDL_RenderPresent(r);
//     SDL_Delay(10000);

//     SDL_DestroyTexture(s);
//     SDL_DestroyRenderer(r);
//     SDL_DestroyWindow(w);

//     return 0; // returns 0, closes the program.
// }