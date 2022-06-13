#include "CheckerBoard.hh"

/**
 * Non parameter constructor
 */
CheckerBoard::CheckerBoard() : m_gridSize(10), m_grid(new Square[m_gridSize * m_gridSize])
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
CheckerBoard::~CheckerBoard() { delete[] m_grid; }

/**
 * Indexing method
 */
int CheckerBoard::index(size_t xCoordinate, size_t yCoordinate) const
{
    if (xCoordinate < 0 || xCoordinate >= m_gridSize || yCoordinate < 0 || yCoordinate >= m_gridSize)
    {
        std::cerr << "Coordinates exceed board size!" << std::endl;
        exit(1);
    }
    return xCoordinate + m_gridSize * yCoordinate;
}

/**
 * Board default setting method
 */
void CheckerBoard::set_board()
{
    std::shared_ptr<Piece> tmp;
    for (size_t i = 0; i < m_gridSize; i++)
    {
        for (size_t j = 0; j < m_gridSize; j++)
        {
            if (i % 2 != j % 2)
            {
                if (i < (m_gridSize - 1) / 2)
                {
                    tmp = std::make_shared<Piece>(i, j, true, false);
                    m_grid[index(i, j)].placePiece(tmp);
                    m_lightPieces.push_back(tmp);
                }
                else if (i > (m_gridSize + 1) / 2)
                {
                    tmp = std::make_shared<Piece>(i, j, false, false);
                    m_grid[index(i, j)].placePiece(tmp);
                    m_darkPieces.push_back(tmp);
                }
            }
        }
    }
}

/**
 * Non parameter constructor
 */
void CheckerBoard::flip_board()
{
    Square tmp;
    // 180 deg rotation
    for (size_t i = 0; i < m_gridSize / 2; i++)
        for (size_t j = 0; j < m_gridSize; j++)
        {
            tmp = m_grid[index(m_gridSize - (1 + i), j)];
            m_grid[index(m_gridSize - (1 + i), j)] = m_grid[index(i, m_gridSize - (1 + j))];
            m_grid[index(i, m_gridSize - (1 + j))] = tmp;
        }
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
std::vector<std::shared_ptr<Piece>> CheckerBoard::get_pieces()
{
    if (m_whiteTurn)
        return m_lightPieces;
    return m_darkPieces;
}
/**
 * Non parameter constructor
 */
void CheckerBoard::clear()
{
    for (size_t i = 0; i < m_gridSize * m_gridSize; i++)
        m_grid->clear();
    set_board();
}
/**
 * Non parameter constructor
 */
bool CheckerBoard::can_attack(std::shared_ptr<Piece> piece)
{
    Square *current, *next;
    int xVert[] = {1, 1, -1, -1}, yVert[] = {1, -1, -1, 1};
    bool stop = false;
    if (piece != nullptr)
        for (size_t i = 0; i < 4; i++)
        {
            current = &m_grid[index(piece->getX() + xVert[i], piece->getY() + yVert[i])];
            next = &m_grid[index(piece->getX() + 2 * xVert[i], piece->getY() + 2 * yVert[i])];
            if (piece->isPromoted())
            {
                for (int j = 1; piece->getX() + j * xVert[i] >= 0 && piece->getX() + j * xVert[i] < 10 && piece->getY() + j * yVert[i] >= 0 && piece->getY() + j * yVert[i] < 10 && !stop; j++)
                {
                    if (!current->isEmpty() && next->isEmpty() && current->getPiece()->isLightColoured() != piece->isLightColoured())
                        return true;
                    if (!current->isEmpty() && next->isEmpty() && current->getPiece()->isLightColoured() == piece->isLightColoured())
                        stop = true;
                }
                stop = false;
            }
            else
            {
                if (piece->getX() + 2 * xVert[i] >= 0 && piece->getX() + 2 * xVert[i] < 10 && piece->getY() + 2 * yVert[i] >= 0 && piece->getY() + 2 * yVert[i] < 10)
                {
                    if (!current->isEmpty() && next->isEmpty() && current->getPiece()->isLightColoured() != piece->isLightColoured())
                        return true;
                }
            }
        }
    return false;
}
/**
 * Spagetti code for checking paths
 */
// std::vector<std::shared_ptr<Square>> CheckerBoard::check_paths(std::shared_ptr<Piece> piece)
// {
//     std::vector<std::shared_ptr<Square>> result;
//     std::vector<std::shared_ptr<Square>> tmp;
//     bool attacks = false;
//     Square *current, *next, *attacked;
//     Piece removed;
//     int xVert[] = {1, 1, -1, -1}, yVert[] = {1, -1, -1, 1};
//     if (can_attack(piece)) // calculate the most effective route
//         for (size_t i = 0; i < 4; i++)
//         {
//             attacks = false;
//             attacked = NULL;
//             current = &m_grid[index(piece->getX() + xVert[i], piece->getY() + yVert[i])];
//             next = &m_grid[index(piece->getX() + 2 * xVert[i], piece->getY() + 2 * yVert[i])];
//             if (piece->isPromoted())
//             {
//                 for (int j = 2; piece->getX() + j * xVert[i] >= 0 && piece->getX() + j * xVert[i] < 10 && piece->getY() + j * yVert[i] >= 0 && piece->getY() + j * yVert[i] < 10 && (!current->isEmpty() && current->getPiece()->isLightColoured() == piece->isLightColoured()); j++)
//                 {
//                     if (attacked != NULL)
//                     {
//                         if (attacks)
//                         {
//                             removed = *attacked->getPiece();
//                             attacked->removePiece();
//                             if (can_attack(current->getPiece()))
//                             {
//                                 tmp = check_paths(current->getPiece());
//                                 if (tmp.size() > result.size())
//                                     result = tmp;
//                             }
//                             attacked->placePiece(std::make_shared<Piece>(removed));
//                         }
//                         else
//                             result.push_back(std::make_shared<Square>(current));
//                     }
//                     if (!current->isEmpty() && attacked != NULL)
//                     {
//                         attacked = current;
//                         for (int l = j + 1; piece->getX() + l * xVert[i] >= 0 && piece->getX() + l * xVert[i] < 10 && piece->getY() + l * yVert[i] >= 0 && piece->getY() + l * yVert[i] < 10 && (current->isEmpty() || current->getPiece()->isLightColoured() == piece->isLightColoured()); l++)
//                         {
//                             removed = *attacked->getPiece();
//                             attacked->removePiece();
//                             if (can_attack(m_grid[index(piece->getX() + l * xVert[i], piece->getY() + l * yVert[i])].getPiece()))
//                                 attacks = true;
//                         }
//                         attacked->placePiece(std::make_shared<Piece>(removed));
//                     }
//                     if (current->isEmpty() && attacked != NULL)
//                     {
//                         attacked = NULL;
//                     }
//                     current = &m_grid[index(piece->getX() + j * xVert[i], piece->getY() + j * yVert[i])];
//                     next = &m_grid[index(piece->getX() + (j + 1) * xVert[i], piece->getY() + (j + 1) * yVert[i])];
//                 }
//             }
//             else
//             {
//                 if (!current->isEmpty() & next->isEmpty())
//                     result.push_back(std::make_shared<Square>(current));
//             }
//         }
//     else
//     {
//         for (size_t i = 0; i < 4; i++)
//         {
//             current = &m_grid[index(piece->getX() + xVert[i], piece->getY() + yVert[i])];
//             if (piece->isPromoted())
//                 for (int j = 2; piece->getX() + j * xVert[i] >= 0 && piece->getX() + j * xVert[i] < 10 && piece->getY() + j * yVert[i] >= 0 && piece->getY() + j * yVert[i] < 10 && current->isEmpty(); j++)
//                 {
//                     result.push_back(std::make_shared<Square>(m_grid[index(piece->getX() + j * xVert[i], piece->getY() + j * yVert[i])]));
//                     current = &m_grid[index(piece->getX() + j * xVert[i], piece->getY() + j * yVert[i])];
//                 }
//             else
//             {
//                 if (piece->getX() + xVert[i] >= 0 && piece->getX() + xVert[i] < 10 && piece->getY() + yVert[i] >= 0 && piece->getY() + yVert[i] < 10 && current->isEmpty())
//                     result.push_back(std::make_shared<Square>(current));
//             }
//         }
//     }
//     return result;
// }

bool CheckerBoard::move(size_t xChosen, size_t yChosen, size_t xDest, size_t yDest)
{
    // if (xDest % 2 == yDest % 2 || xChosen % 2 == yChosen % 2)
    // {
    //     std::cerr << "first" << std::endl;
    //     return false;
    // }
    // if (!m_grid[index(yChosen, xChosen)].getPiece()->isPromoted())
    // {
    // }

    return m_grid[index(yChosen, xChosen)].movePiece(m_grid[index(yDest, xDest)]);
}
Square &CheckerBoard::operator()(size_t xCoordinate, size_t yCoordinate) { return m_grid[index(xCoordinate, yCoordinate)]; }

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed)
{
    strm << "#########################################" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        strm << "#";
        for (size_t j = 0; j < 10; j++)
        {
            if (printed(i, j).isEmpty())
                strm << "   #";
            else
            {
                if (printed(i, j).getPiece()->isLightColoured())
                    strm << " + #";
                else
                    strm << " x #";
            }
        }
        strm << std::endl
             << "#########################################";
        strm << std::endl;
    }
    return strm;
}
