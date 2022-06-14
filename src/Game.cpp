#include "Game.hh"

Game::Game()
{
    m_board = new CheckerBoard;
    m_board->set_board();
}
Game::~Game() {}
void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Initialised SDL!" << std::endl;
        m_window = SDL_CreateWindow("title", xpos, ypos, width, height, flags);
        if (m_window)
            std::cout << "Window created!" << std::endl;
        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if (m_renderer)
            std::cout << "Renderer created!" << std::endl;

        m_ongoing = true;
    }
    else
        m_ongoing = false;
}
bool Game::running() { return m_ongoing; }

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        m_ongoing = false;
        break;

    default:
        break;
    }
}
void Game::update() {}
void Game::renderer()
{
    if (m_ongoing)
    {
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 51, 0, 51, 255);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 200, 0, 200, 255);
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (i % 2 == j % 2)
                {
                    SDL_Rect r = {i * m_pixelSize, j * m_pixelSize, m_pixelSize, m_pixelSize};
                    SDL_RenderFillRect(m_renderer, &r);
                }
        for (int i = 0; i < 50; i++)
        {
            // if (m_board[i]->getIndex())
            //     if (p.front()->isPromoted())
            //         SDL_Texture *t = loadTexture("/images/white_king.png");
            //     else
            //         SDL_Texture *t = loadTexture("/images/white_men.png");
            // else
            // {
            //     if (p.front()->isPromoted())
            //         SDL_Texture *t = loadTexture("/images/dark_king.png");
            //     else
            //         SDL_Texture *t = loadTexture("/images/dark_men.png");
            // }
            // SDL_Rect r = { p.front() }
        }

        SDL_RenderPresent(m_renderer);
    }
}
void Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "Cleaned" << std::endl;
}
SDL_Texture *Game::loadTexture(std::string path)
{
    SDL_Texture *result;
    SDL_Surface *srfc;
    if (srfc = IMG_Load(path.c_str()))
        std::cerr << "No such file exists!" << std::endl;
    else
    {
        if (result = SDL_CreateTextureFromSurface(m_renderer, srfc))
            std::cerr << "Error while creating surface from file!" << std::endl;
        SDL_FreeSurface(srfc);
    }
    return result;
}
