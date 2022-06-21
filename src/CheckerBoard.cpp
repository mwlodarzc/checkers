#include "CheckerBoard.hh"

/**
 * Non parameter constructor
 */
CheckerBoard::CheckerBoard(bool whitePov) : m_gridSize(10), m_grid(), m_whiteTurn(true), m_whitePerspective(whitePov)
{
    set_board();
}

/**
 * Copy constructor
 */
CheckerBoard::CheckerBoard(CheckerBoard &c)
{
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            m_grid[i][j] = c.m_grid[i][j];
    m_whiteTurn = c.m_whiteTurn;
    m_whitePerspective = c.m_whitePerspective;
}

CheckerBoard::CheckerBoard(const CheckerBoard &c)
{
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            m_grid[i][j] = c.m_grid[i][j];
    m_whiteTurn = c.m_whiteTurn;
    m_whitePerspective = c.m_whitePerspective;
}

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
                    m_grid[i][j].placePiece(std::make_shared<Piece>(!m_whitePerspective, false));
                if (j > 5)
                    m_grid[i][j].placePiece(std::make_shared<Piece>(m_whitePerspective, false));
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
    for (int i = 0; i < m_gridSize * m_gridSize; i++)
        m_grid[i]->removePiece();
    set_board();
}
/**
 * Spagetti code for checking paths
 */

bool CheckerBoard::move(std::pair<int, int> coordsChosen, std::pair<int, int> coordsDest)
{
    std::vector<std::shared_ptr<Square>> moves = check_paths(coordsChosen);
    if (m_whiteTurn == m_grid[coordsChosen.first][coordsChosen.second].getPiece().isLightColoured() && (coordsDest.first + coordsDest.second) % 2 && (coordsChosen.first + coordsChosen.second) % 2)
    {
        while (!moves.empty())
        {
            if (moves.back()->getCoords() == coordsDest)
            {
                if (std::abs(coordsChosen.first - coordsDest.first) == 2 && std::abs(coordsChosen.second - coordsDest.second) == 2 && !m_grid[coordsChosen.first + (coordsDest.first - coordsChosen.first) / 2][coordsChosen.second + (coordsDest.second - coordsChosen.second) / 2].isEmpty())
                    m_grid[coordsChosen.first + (coordsDest.first - coordsChosen.first) / 2][coordsChosen.second + (coordsDest.second - coordsChosen.second) / 2].removePiece();
                m_grid[coordsDest.first][coordsDest.second].placePiece(std::make_shared<Piece>(m_grid[coordsChosen.first][coordsChosen.second].getPiece()));
                m_grid[coordsChosen.first][coordsChosen.second].removePiece();
                if (((coordsDest.second == 9) && m_grid[coordsDest.first][coordsDest.second].getPiece().isLightColoured() == !m_whitePerspective) || (coordsDest.second == 0 && m_grid[coordsDest.first][coordsDest.second].getPiece().isLightColoured() == m_whitePerspective))
                    m_grid[coordsDest.first][coordsDest.second].promotePiece();
                turn_over();
                return true;
            }
            moves.pop_back();
        }
    }
    return false;
}
Square &CheckerBoard::getSquare(std::pair<int, int> coords)
{
    if (coords.first < 0 || coords.first > 9 || coords.second < 0 || coords.second > 9)
    {
        std::cerr << "Out of bounds!" << std::endl;
        exit(1);
    }
    return m_grid[coords.first][coords.second];
}

std::vector<std::shared_ptr<Square>> CheckerBoard::check_paths(std::pair<int, int> coords)
{
    std::vector<std::shared_ptr<Square>> result;
    int start = 0, end = 4;
    int direction = 1;
    int xVert[] = {-1, 1, 1, -1}, yVert[] = {1, 1, -1, -1};
    if (!m_grid[coords.first][coords.second].isEmpty())
    {
        if (!m_grid[coords.first][coords.second].getPiece().isPromoted())
        {
            if (m_grid[coords.first][coords.second].getPiece().isLightColoured() == m_whitePerspective)
            {
                start = 2;
                end = 4;
            }
            else
            {
                start = 0;
                end = 2;
            }
        }
        for (int i = start; i < end; i++)
        {
            if ((coords.first + xVert[i]) >= 0 && (coords.first + xVert[i]) < m_gridSize && (coords.second + yVert[i] * direction) >= 0 && (coords.second + yVert[i] * direction) < m_gridSize)
            {
                if (m_grid[coords.first + xVert[i]][coords.second + yVert[i] * direction].isEmpty())
                    result.push_back(std::make_shared<Square>(std::pair<int, int>(coords.first + xVert[i], coords.second + yVert[i] * direction)));
                else
                {
                    if ((coords.first + 2 * xVert[i]) >= 0 && (coords.first + 2 * xVert[i]) < m_gridSize && (coords.second + 2 * yVert[i] * direction) >= 0 && (coords.second + 2 * yVert[i] * direction) < m_gridSize)
                        if (m_grid[coords.first + 2 * xVert[i]][coords.second + 2 * yVert[i] * direction].isEmpty() && m_grid[coords.first][coords.second].getPiece().isLightColoured() != m_grid[coords.first + xVert[i]][coords.second + yVert[i] * direction].getPiece().isLightColoured())
                            result.push_back(std::make_shared<Square>(std::make_pair(coords.first + 2 * xVert[i], coords.second + 2 * yVert[i] * direction)));
                }
            }
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}
const Square &CheckerBoard::getConstSquare(std::pair<int, int> coords) const
{
    if (coords.first < 0 || coords.first > 9 || coords.second < 0 || coords.second > 9)
    {
        std::cerr << "Out of bounds!" << std::endl;
        exit(1);
    }
    return m_grid[coords.first][coords.second];
}

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed)
{
    for (size_t j = 0; j < 10; j++)
    {
        for (size_t i = 0; i < 10; i++)
        {
            if (printed.getConstSquare(std::make_pair<int, int>(i, j)).isEmpty())
                strm << "   ";
            else
            {
                if (!printed.getSquare(std::pair<int, int>(i, j)).getPiece().isLightColoured())
                {
                    if (printed.getSquare(std::make_pair<int, int>(i, j)).getPiece().isPromoted())
                        strm << " + ";
                    else
                        strm << " * ";
                }
                else
                {
                    if (printed.getSquare(std::make_pair<int, int>(i, j)).getPiece().isPromoted())
                        strm << " x ";

                    else
                        strm << " & ";
                }
            }
        }
        strm << std::endl;
    }
    return strm;
}
std::vector<CheckerBoard> CheckerBoard::get_all_settings()
{
    std::vector<CheckerBoard> settings;
    std::vector<std::shared_ptr<Square>> moves;
    CheckerBoard board(*this);
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            if ((i + j) % 2)
                if (!m_grid[i][j].isEmpty())
                    if (m_grid[i][j].getPiece().isLightColoured() == m_whiteTurn)
                    {
                        moves = this->check_paths(std::make_pair(i, j));
                        while (!moves.empty())
                        {
                            board = *this;
                            board.move(std::make_pair(i, j), moves.back()->getCoords());
                            moves.pop_back();
                            settings.push_back(board);
                        }
                    }
    std::reverse(settings.begin(), settings.end());
    return settings;
}
int CheckerBoard::get_score()
{
    int count = 0;
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            if ((i + j) % 2 && !m_grid[i][j].isEmpty())
                (m_grid[i][j].getPiece().isLightColoured()) ? (m_grid[i][j].getPiece().isPromoted() ? count += 2 : count++) : (m_grid[i][j].getPiece().isPromoted() ? count -= 2 : count--);
    return count;
}

bool CheckerBoard::get_turn() { return m_whiteTurn; }
bool CheckerBoard::game_over()
{
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            if (!m_grid[i][j].isEmpty())
                if (m_grid[i][j].getPiece().isLightColoured() == m_whiteTurn)
                    if (check_paths(std::make_pair(i, j)).size() > 0)
                        return false;
    return true;
}
CheckerBoard &CheckerBoard::operator=(const CheckerBoard &c)
{
    for (int i = 0; i < m_gridSize; i++)
        for (int j = 0; j < m_gridSize; j++)
            m_grid[i][j] = c.m_grid[i][j];
    m_whiteTurn = c.m_whiteTurn;
    return *this;
}
