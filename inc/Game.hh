#ifndef GAME_HH
#define GAME_HH
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "CheckerBoard.hh"

class Game
{
private:
    bool m_ongoing;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_pixelSize = 100;
    CheckerBoard *m_board;

private:
    SDL_Texture *loadTexture(std::string path);

public:
    Game();
    ~Game();
    bool running();
    void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void renderer();
    void clean();
};

#endif