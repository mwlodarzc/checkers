#ifndef GAME_HH
#define GAME_HH
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "CheckerBoard.hh"

class Game
{
private:
    bool m_ongoing;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_pixelSize = 100;

private:
    CheckerBoard *m_board;
    std::vector<std::shared_ptr<Square>> m_moves;

private:
    SDL_Texture *white_king = NULL;
    SDL_Texture *white_men = NULL;
    SDL_Texture *dark_king = NULL;
    SDL_Texture *dark_men = NULL;

private:
    void loadTextures();

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