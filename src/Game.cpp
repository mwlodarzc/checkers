#include "Game.hh"
Game::Game(bool playsWhite, int botDepth) : m_board(playsWhite), m_botDepth(botDepth)
{
    m_board.set_board();
    if (!playsWhite)
        Bot::make_best_move(m_board, m_botDepth, !playsWhite);
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
        m_window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
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
        if ((x + y) % 2)
        {
            if (m_board.getSquare(std::make_pair(x, y)).isEmpty() && m_pieceSelected && std::make_pair(x, y) != m_pickedCoords)
            {
                if (m_board.move(m_pickedCoords, std::make_pair(x, y)))
                {
                    m_moves.clear();
                    m_pieceSelected = false;
                    if (!m_board.game_over())
                        Bot::make_best_move(m_board, m_botDepth, !m_playsWhite);
                }
            }
            else
            {
                m_pickedCoords = std::make_pair(x, y);
                m_moves = m_board.check_paths(std::make_pair(x, y));
                m_pieceSelected = true;
            }
        }
        break;
    default:
        break;
    }
}
void Game::update()
{
    if (m_board.game_over())
        m_ongoing = false;
}
void Game::renderer()
{
    if (m_ongoing)
    {
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 150, 0, 150, 255);

        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 50, 0, 50, 255);

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (i % 2 != j % 2)
                {
                    SDL_Rect r = {i * m_pixelSize, j * m_pixelSize, m_pixelSize, m_pixelSize};
                    SDL_RenderFillRect(m_renderer, &r);
                    if (!m_board.getSquare(std::make_pair(i, j)).isEmpty())
                    {
                        if (m_board.getSquare(std::make_pair(i, j)).getPiece().isLightColoured())
                        {
                            if (m_board.getSquare(std::make_pair(i, j)).getPiece().isPromoted())
                                SDL_RenderCopy(m_renderer, white_king, NULL, &r);
                            else
                                SDL_RenderCopy(m_renderer, white_men, NULL, &r);
                        }
                        else
                        {
                            if (m_board.getSquare(std::make_pair(i, j)).getPiece().isPromoted())
                                SDL_RenderCopy(m_renderer, dark_king, NULL, &r);
                            else
                                SDL_RenderCopy(m_renderer, dark_men, NULL, &r);
                        }
                    }
                }
        if (!m_moves.empty())
            for (uint i = 0; i < m_moves.size(); i++)
            {
                std::pair<int, int> p = std::make_pair(m_moves[i]->getCoords().first, m_moves[i]->getCoords().second);
                SDL_Rect d = {p.first * m_pixelSize, p.second * m_pixelSize, m_pixelSize, m_pixelSize};
                SDL_RenderCopy(m_renderer, possible_move, NULL, &d);
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
    if (m_board.get_score() == 0)
        std::cout << "Tie!" << std::endl;
    else if (m_board.get_score() > 0)
        std::cout << "White wins!" << std::endl;
    else
        std::cout << "Black wins!" << std::endl;

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
    srfc = IMG_Load("images/possible_move.png");
    if (srfc == NULL)
    {
        std::cerr << "No such file exists!" << std::endl;
        exit(1);
    }
    possible_move = SDL_CreateTextureFromSurface(m_renderer, srfc);
    if (possible_move == NULL)
        std::cerr << "Error while creating surface from file!" << std::endl;
    SDL_SetTextureAlphaMod(possible_move, 100);
    SDL_FreeSurface(srfc);
}
