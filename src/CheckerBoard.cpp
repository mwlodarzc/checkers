#include "CheckerBoard.hh"

/**
 * Non parameter constructor
 */
CheckerBoard::CheckerBoard() : m_gridSize(10), m_grid()
{
    set_board();
    m_whiteTurn = true;
    m_whitePerspective = true;
}

/**
 * Copy constructor
 */
CheckerBoard::CheckerBoard(CheckerBoard &c) = default;

/**
 * Destructor
 */
CheckerBoard::~CheckerBoard() = default;
/**
 * Board default setting method
 */
void CheckerBoard::set_board()
{
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            if ((i + j) % 2)
            {
                if (j < 4)
                    m_grid[i][j].placePiece(std::make_shared<Piece>(true, false));
                if (j > 5)
                    m_grid[i][j].placePiece(std::make_shared<Piece>(false, false));
            }
}

/**
 * Non parameter constructor
 */
void CheckerBoard::flip_board()
{
    // m_whitePerspective = false;
    // auto tmp = m_grid.begin();
    // m_grid.begin() = m_grid.end();
    // m_grid.end() = tmp;
}
/**
 * Non parameter constructor
 */
void CheckerBoard::turn_over()
{
    m_whiteTurn ? m_whiteTurn = false : m_whiteTurn = true;
}
/**
 * Non parameter constructor
 */
void CheckerBoard::clear()
{
    for (int i = 0; i < 50; i++)
        m_grid[i]->removePiece();
    set_board();
}
/**
 * Spagetti code for checking paths
 */

// bool CheckerBoard::move(std::pair<int, int> coords)
// {
//     std::vector<std::shared_ptr<Square>> moves;
//     if (idChosen < 0 || idChosen >= 50 || idDest < 0 || idDest >= 50)
//     {
//         std::cerr << "out of bounds" << std::endl;
//         return false;
//     }
//     // PUT IN CHECK FOR DISTANCE (CAN BE DEPENDEND ON COLOUR IF EASIER)
//     moves = check_paths(idChosen);
//     while (!moves.empty())
//     {
//         if (moves.front()->getIndex() == idDest)
//             return m_grid[idChosen]->movePiece(*m_grid[idDest]);
//     }
//     return false;
// }
Square &CheckerBoard::getSquare(std::pair<int, int> coords)
{
    if (coords.first < 0 || coords.first > 9 || coords.second < 0 || coords.second > 9)
    {
        std::cerr << "Out of bounds!" << std::endl;
        exit(1);
    }
    return m_grid[coords.second][coords.first];
}

void CheckerBoard::promote(std::pair<int, int> coords) { m_grid[coords.first][coords.second].getPiece()->promotePiece(); }

std::vector<std::shared_ptr<Square>> CheckerBoard::check_paths(std::pair<int, int> coords)
{
    std::vector<std::shared_ptr<Square>> result;
    Square *current, *next;
    int start = 0, end = 4;
    int direction;
    std::shared_ptr<Piece> piece;
    int xVert[] = {-1, 1, 1, -1}, yVert[] = {1, 1, -1, -1};

    if (!m_grid[coords.first][coords.second].isEmpty())
    {
        piece = m_grid[coords.first][coords.second].getPiece();
        std::cout << "Coords: " << coords.first << "," << coords.second << std::endl;
        if (piece->isLightColoured() == m_whitePerspective)
            direction = 1;
        else
            direction = -1;
        if (!piece->isPromoted())
        {
            start = 0;
            end = 2;
        }
        for (int i = start; i < end; i++)
        {
            std::cout << "Current: " << coords.first + xVert[i] << "," << coords.second + yVert[i] * direction << std::endl;
            if ((coords.first + xVert[i]) >= 0 && (coords.first + xVert[i]) < m_gridSize && (coords.second + yVert[i] * direction) >= 0 && (coords.second + yVert[i] * direction) < m_gridSize)
            {
                current = &m_grid[coords.first + xVert[i]][coords.second + yVert[i] * direction];
                if (current->isEmpty())
                {
                    result.push_back(std::make_shared<Square>(current));
                    std::cout << "Added current!" << std::endl;
                }
                else
                {
                    std::cout << "Next: " << coords.first + 2 * xVert[i] << "," << coords.second + 2 * yVert[i] * direction * direction << std::endl;
                    if ((coords.first + 2 * xVert[i]) >= 0 && (coords.first + 2 * xVert[i]) < m_gridSize && (coords.second + 2 * yVert[i] * direction) >= 0 && (coords.second + 2 * yVert[i] * direction) < m_gridSize)
                    {
                        next = &m_grid[coords.first + 2 * xVert[i]][coords.second + 2 * yVert[i] * direction];
                        if (next->isEmpty())
                        {
                            result.push_back(std::make_shared<Square>(next));
                            std::cout << "Added next!" << std::endl;
                        }
                    }
                }
            }
        }
    }
    while (!result.empty())
    {
        std::cout << result.back()->getCoords().first << "," << result.back()->getCoords().second << std::endl;
        result.pop_back();
    }

    return result;
}

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed)
{
    strm << "############################################" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        strm << "#";
        for (size_t j = 0; j < 10; j++)
        {
            if (printed.getSquare(std::pair<int, int>(i, j)).isEmpty())
                strm << "   #";
            else
            {
                if (printed.getSquare(std::pair<int, int>(i, j)).getPiece()->isLightColoured())
                    strm << " + #";
                else
                    strm << " x #";
            }
        }
        strm << std::endl
             << "############################################";
        strm << std::endl;
    }
    return strm;
}
