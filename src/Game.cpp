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
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if (m_renderer)
            std::cout << "Renderer created!" << std::endl;
        if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
            std::cout << "Image initialized!" << std::endl;
        loadTextures();
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
    case SDL_MOUSEBUTTONDOWN:
        int x, y;
        SDL_GetMouseState(&x, &y);
        x = std::floor(x / m_pixelSize);
        y = std::floor(y / m_pixelSize);
        std::cout << "x,y : " << x << "," << y << std::endl;
        if (x % 2 == y % 2)
            break;
        std::cout << "black " << m_board->gridize(x, y) << std::endl;
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
        SDL_SetRenderDrawColor(m_renderer, 150, 0, 150, 255);

        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 50, 0, 50, 255);

        for (int i = 0, index = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (i % 2 != j % 2)
                {
                    SDL_Rect r = {j * m_pixelSize, i * m_pixelSize, m_pixelSize, m_pixelSize};
                    SDL_RenderFillRect(m_renderer, &r);
                    if (!m_board->getSquare(index).isEmpty())
                    {
                        if (m_board->getSquare(index).getPiece()->isLightColoured())

                            if (m_board->getSquare(index).getPiece()->isPromoted())
                                SDL_RenderCopy(m_renderer, white_king, NULL, &r);

                            else
                                SDL_RenderCopy(m_renderer, white_men, NULL, &r);

                        else
                        {
                            if (m_board->getSquare(index).getPiece()->isPromoted())
                                SDL_RenderCopy(m_renderer, dark_king, NULL, &r);

                            else

                                SDL_RenderCopy(m_renderer, dark_men, NULL, &r);
                        }
                    }
                    index++;
                }
    }
    SDL_RenderPresent(m_renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(white_king);
    SDL_DestroyTexture(white_men);
    SDL_DestroyTexture(dark_king);
    SDL_DestroyTexture(dark_men);

    SDL_Quit();
    IMG_Quit();
    std::cout << "Cleaned" << std::endl;
}
void Game::loadTextures()
{
    SDL_Surface *srfc;
    srfc = IMG_Load("images/white_king.png");
    if (srfc == NULL)
    {
        std::cerr << "No such file exists!" << std::endl;
        exit(1);
    }
    white_king = SDL_CreateTextureFromSurface(m_renderer, srfc);
    if (white_king == NULL)
        std::cerr << "Error while creating surface from file!" << std::endl;
    srfc = IMG_Load("images/white_men.png");
    if (srfc == NULL)
    {
        std::cerr << "No such file exists!" << std::endl;
        exit(1);
    }
    white_men = SDL_CreateTextureFromSurface(m_renderer, srfc);
    if (white_men == NULL)
        std::cerr << "Error while creating surface from file!" << std::endl;
    srfc = IMG_Load("images/dark_king.png");
    if (srfc == NULL)
    {
        std::cerr << "No such file exists!" << std::endl;
        exit(1);
    }
    dark_king = SDL_CreateTextureFromSurface(m_renderer, srfc);
    if (dark_king == NULL)
        std::cerr << "Error while creating surface from file!" << std::endl;
    srfc = IMG_Load("images/dark_men.png");
    if (srfc == NULL)
    {
        std::cerr << "No such file exists!" << std::endl;
        exit(1);
    }
    dark_men = SDL_CreateTextureFromSurface(m_renderer, srfc);
    if (dark_men == NULL)
        std::cerr << "Error while creating surface from file!" << std::endl;
    SDL_FreeSurface(srfc);
}
