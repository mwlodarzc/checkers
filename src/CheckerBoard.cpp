#include "CheckerBoard.hh"

/**
 * Non parameter constructor
 */
CheckerBoard::CheckerBoard() : m_gridSize(10), m_grid()
{
    for (int i = 0; i < 50; i++)
    {
        m_grid.push_back(std::make_shared<Square>(i));
    }
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
    for (int i = 0; i < 20; i++)
    {
        m_grid[i]->placePiece(std::make_shared<Piece>(true, false));
    }
    for (int i = 30; i < 50; i++)
    {
        m_grid[i]->placePiece(std::make_shared<Piece>(false, false));
    }
}

/**
 * Non parameter constructor
 */
void CheckerBoard::flip_board()
{
    auto tmp = m_grid.begin();
    m_grid.begin() = m_grid.end();
    m_grid.end() = tmp;
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
        m_grid[i]->clear();
    set_board();
}
/**
 * Spagetti code for checking paths
 */

bool CheckerBoard::move(int idChosen, int idDest)
{
    std::vector<std::shared_ptr<Square>> moves;
    if (idChosen < 0 || idChosen >= 50 || idDest < 0 || idDest >= 50)
    {
        std::cerr << "out of bounds" << std::endl;
        return false;
    }
    // PUT IN CHECK FOR DISTANCE (CAN BE DEPENDEND ON COLOUR IF EASIER)
    moves = check_paths(idChosen);
    while (!moves.empty())
    {
        if (moves.front()->getIndex() == idDest)
            return m_grid[idChosen]->movePiece(*m_grid[idDest]);
    }
    return false;
}
std::shared_ptr<Square> CheckerBoard::operator[](int index) { return m_grid[index]; }

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed)
{
    int index = 0;
    strm << "#########################################" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        strm << "#";
        for (int j = 0; j < 5; j++, index++)
        {
            if (printed[index]->isEmpty())
                strm << "   #";
            else
            {
                if (printed[index]->getPiece()->isLightColoured())
                    strm << " * #";
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

void CheckerBoard::promote(int index) { m_grid[index]->getPiece()->promotePiece(); }

bool CheckerBoard::can_attack(int index)
{
    return m_grid[index]->getPiece()->isPromoted() ? can_attack_king(index) : can_attack_men(index);
}
bool CheckerBoard::can_attack_king(int index)
{
    std::shared_ptr<Piece> piece = m_grid[index]->getPiece();
    int denom = 0;
    if (piece != nullptr)
        if (piece->isPromoted())
            if (index % 5 > 0 && index % 5 < 4)
            {
                if (index - ((index / 10) * 10) >= 5 && index - ((index / 10) * 10) < 10)
                    denom = 1;
                if (index < 40)
                {
                    // TL
                    if (!m_grid[index + 5 - denom]->isEmpty() && m_grid[index + 5 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index + 10 - 1]->isEmpty())
                        return true;
                    // TR
                    if (!m_grid[index + 5 + 1 - denom]->isEmpty() && m_grid[index + 5 + 1 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index + 10 + 1]->isEmpty())
                        return true;
                }
                if (index > 9)
                {
                    // TL
                    if (!m_grid[index - 5 - denom]->isEmpty() && m_grid[index - 5 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index - 10 - 1]->isEmpty())
                        return true;
                    // TR
                    if (!m_grid[index - 5 + 1 - denom]->isEmpty() && m_grid[index - 5 + 1 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index - 10 + 1]->isEmpty())
                        return true;
                }
            }
    return false;
}
std::vector<std::shared_ptr<Square>> CheckerBoard::check_paths_king(int index)
{
    std::vector<std::shared_ptr<Square>> result;
    std::vector<std::shared_ptr<Square>> tmp;
    int denom = 0;

    std::shared_ptr<Piece> piece = m_grid[index]->getPiece();
    if (piece != nullptr)
    {
        if (piece->isPromoted())
        {
            if (index - ((index / 10) * 10) >= 5 && index - ((index / 10) * 10) < 10)
                denom = 1;
            if (can_attack_king(index))
            {
                if (index % 5 > 0 && index % 5 < 4)
                {
                    if (index < 40)
                    {
                        // TL
                        if (!m_grid[index + 5 - denom]->isEmpty() && m_grid[index + 5 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index + 10 - 1]->isEmpty())
                        {
                            result.push_back(m_grid[index + 10 - 1]);
                            if (can_attack_king(index + 10 - 1))
                                tmp = check_paths_king(index + 10 - 1);
                            if (tmp.size() > result.size())
                                result = tmp;
                        }
                        // TR
                        if (!m_grid[index + 5 + 1 - denom]->isEmpty() && m_grid[index + 5 + 1 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index + 10 + 1]->isEmpty())
                        {
                            result.push_back(m_grid[index + 10 + 1]);
                            if (can_attack_king(index + 10 + 1))
                                tmp = check_paths_king(index + 10 + 1);
                            if (tmp.size() > result.size())
                                result = tmp;
                        }
                    }
                    if (index > 9)
                    {
                        // TL
                        if (!m_grid[index - 5 - denom]->isEmpty() && m_grid[index - 5 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index - 10 - 1]->isEmpty())
                        {
                            result.push_back(m_grid[index - 10 + 1]);
                            if (can_attack_king(index - 10 + 1))
                                tmp = check_paths_king(index - 10 + 1);
                            if (tmp.size() > result.size())
                                result = tmp;
                        }
                        // TR
                        if (!m_grid[index - 5 + 1 - denom]->isEmpty() && m_grid[index - 5 + 1 - denom]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[index - 10 + 1]->isEmpty())
                        {
                            result.push_back(m_grid[index - 10 - 1]);
                            if (can_attack_king(index - 10 - 1))
                                tmp = check_paths_king(index - 10 - 1);
                            if (tmp.size() > result.size())
                                result = tmp;
                        }
                    }
                }
            }
            else
            {
                if (index < 45)
                {
                    // TL
                    if (m_grid[index + 5 - denom]->isEmpty())
                        result.push_back(m_grid[index + 5 - denom]);

                    // TR
                    if (m_grid[index + 5 + 1 - denom]->isEmpty())
                        result.push_back(m_grid[index + 5 + 1 - denom]);
                }
                if (index > 4)
                {
                    // TL
                    if (m_grid[index - 5 - denom]->isEmpty())
                        result.push_back(m_grid[index - 5 - denom]);

                    // TR
                    if (!m_grid[index - 5 + 1 - denom]->isEmpty())
                        result.push_back(m_grid[index - 5 + 1 - denom]);
                }
            }
        }
    }
    return result;
}
// WORKING!
bool CheckerBoard::can_attack_men(int index)
{
    int idCur, idNext;
    bool second = false;
    int direction = 0;
    std::shared_ptr<Piece> piece = m_grid[index]->getPiece();
    if (piece != nullptr)
        if (!piece->isPromoted())
        {
            if (piece->isLightColoured() == m_whitePerspective)
                direction = 1;
            else
                direction = -1;
            std::cout << "Attack check men" << std::endl;
            if ((direction == 1 && index < 40) || (direction == -1 && index > 9))
            {
                // DR
                if (second)
                {
                    if (index % 5 < 4)
                    {
                        idCur = index + direction * (5 + direction);
                        idNext = idCur + direction * 5;
                        std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                        if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                            return true;
                    }
                }
                else
                {
                    idCur = index + direction * 5;
                    idNext = idCur + direction * (5 + direction);
                    std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                    if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                        return true;
                }
                // DL
                if (second)
                {
                    idCur = index + direction * 5;
                    idNext = idCur + direction * (5 - direction);
                    std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                    if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                        return true;
                }
                else
                {
                    if (index % 5 > 0)
                    {
                        idCur = index + direction * (5 - direction);
                        idNext = idCur + direction * 5;
                        std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                        if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                            return true;
                    }
                }
            }
        }
    return false;
}
std::vector<std::shared_ptr<Square>> CheckerBoard::check_paths_men(int index)
{
    std::vector<std::shared_ptr<Square>> result;
    int idCur, idNext;
    bool second = false;
    int direction = 0;
    std::shared_ptr<Piece> piece = m_grid[index]->getPiece();

    if (piece != nullptr)
    {
        if (!piece->isPromoted())
        {
            if (index - ((index / 10) * 10) >= 5 && index - ((index / 10) * 10) < 10)
                second = true;
            if (piece->isLightColoured() == m_whitePerspective)
                direction = 1;
            else
                direction = -1;
            if (can_attack_men(index))
            {
                std::cout << "Attack paths men" << std::endl;
                if ((direction == 1 && index < 40) || (direction == -1 && index > 9))
                {
                    // DR
                    if (second)
                    {
                        if (index % 5 < 4)
                        {
                            idCur = index + direction * (5 + direction);
                            idNext = idCur + direction * 5;
                            std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                            if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                                result.push_back(m_grid[idNext]);
                        }
                    }
                    else
                    {
                        idCur = index + direction * 5;
                        idNext = idCur + direction * (5 + direction);
                        std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                        if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                            result.push_back(m_grid[idNext]);
                    }
                    // DL
                    if (second)
                    {
                        idCur = index + direction * 5;
                        idNext = idCur + direction * (5 - direction);
                        std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                        if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                            result.push_back(m_grid[idNext]);
                    }
                    else
                    {
                        if (index % 5 > 0)
                        {
                            idCur = index + direction * (5 - direction);
                            idNext = idCur + direction * 5;
                            std::cout << "check DR " << idCur << " next: " << idNext << std::endl;
                            if (!m_grid[idCur]->isEmpty() && m_grid[idCur]->getPiece()->isLightColoured() != piece->isLightColoured() && m_grid[idNext]->isEmpty())
                                result.push_back(m_grid[idNext]);
                        }
                    }
                }
            }
            else
            {
                std::cout << "Neutral paths men" << std::endl;
                if ((direction == 1 && index < 45) || (direction == -1 && index > 4))
                {
                    // DR
                    if (second)
                    {
                        if (index % 5 < 4)
                        {
                            std::cout << "check DR " << index + direction * (5 + direction) << std::endl;
                            if (m_grid[index + direction * (5 + direction)]->isEmpty())
                                result.push_back(m_grid[index + direction * (5 + direction)]);
                        }
                    }
                    else
                    {
                        std::cout << "check DR " << index + direction * 5 << std::endl;
                        if (m_grid[index + direction * 5]->isEmpty())
                            result.push_back(m_grid[index + direction * 5]);
                    }
                    // DL
                    if (second)
                    {
                        std::cout << "check DL " << index + direction * 5 << std::endl;
                        if (m_grid[index + direction * 5]->isEmpty())
                            result.push_back(m_grid[index + direction * 5]);
                    }
                    else
                    {
                        if (index % 5 > 0)
                        {
                            std::cout << "check DL " << index + direction * (5 - direction) << std::endl;
                            if (m_grid[index + direction * (5 - direction)]->isEmpty())
                                result.push_back(m_grid[index + direction * (5 - direction)]);
                        }
                    }
                }
            }
        }
    }
    return result;
}

std::vector<std::shared_ptr<Square>> CheckerBoard::check_paths(int index)
{
    if (m_grid[index]->getPiece() == nullptr)
    {
        std::cerr << "Piece doesnt exist!" << std::endl;
        return std::vector<std::shared_ptr<Square>>();
    }
    return m_grid[index]->getPiece()->isPromoted() ? check_paths_king(index) : check_paths_men(index);
}