#include "ChceckerBoard.hh"
CheckerBoard::CheckerBoard(int size, bool whitePiece) : gridSize(size), grid(new CheckerBoardSquare[size * size]), whitePiecePerspective(whitePiece) { set_board(); }
CheckerBoard::CheckerBoard(CheckerBoard &c) = default;
CheckerBoard::~CheckerBoard() { delete[] grid; }

size_t CheckerBoard::size() const { return gridSize; }

int CheckerBoard::index(size_t xCoordinate, size_t yCoordinate) const
{
    if (xCoordinate < 0 || xCoordinate >= gridSize || yCoordinate < 0 || yCoordinate >= gridSize)
    {
        std::cerr << "Coordinates exceed board size!" << std::endl;
        exit(1);
    }
    return xCoordinate + gridSize * yCoordinate;
}

bool CheckerBoard::can_attack(CheckerBoardSquare &square) const
{
    CheckerBoardSquare attacked, landing;
    int xCoordinates[] = {1, 1, -1, -1}, yCoordinates[] = {1, -1, -1, 1};

    if (square.isEmpty())
        return false;
    if (!square.isKing())
        for (size_t i = 0; i < 4; i++)
        {
            if ((square.getX() + 2 * xCoordinates[i] < gridSize) && (square.getX() + 2 * xCoordinates[i] >= 0) && (square.getY() + 2 * yCoordinates[i] < gridSize) && (square.getY() + 2 * yCoordinates[i] >= 0))
            {
                attacked = grid[index(square.getX() + xCoordinates[i], square.getY() + yCoordinates[i])];
                landing = grid[index(square.getX() + 2 * xCoordinates[i], square.getY() + 2 * yCoordinates[i])];
                if (!attacked.isEmpty())
                    if (whitePiecePerspective != attacked.holdsWhite())
                        if (landing.isEmpty())
                            return true;
            }
        }
    else
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 1; (square.getX() + j * xCoordinates[i] < gridSize) && (square.getX() + j * xCoordinates[i] >= 0) && (square.getY() + j * yCoordinates[i] < gridSize) && (square.getY() + j * yCoordinates[i] >= 0) && (j <= gridSize); j++)
            {
                attacked = grid[index(square.getX() + j * xCoordinates[i], square.getY() + j * yCoordinates[i])];
                landing = grid[index(square.getX() + (j + 1) * xCoordinates[i], square.getY() + (j + 1) * yCoordinates[i])];
                if (!attacked.isEmpty())
                    if (whitePiecePerspective != attacked.holdsWhite())
                        if (landing.isEmpty())
                            return true;
            }
        }
    }
    return false;
}

bool CheckerBoard::attack(CheckerBoardSquare &square, CheckerBoardSquare &attacked)
{
    if (!can_attack(square))
        return false;
}

void CheckerBoard::flip_board()
{
    CheckerBoardSquare tmp;
    // 180 deg rotation
    for (size_t i = 0; i < gridSize / 2; i++)
        for (size_t j = 0; j < gridSize; j++)
        {
            tmp = grid[index(gridSize - (1 + i), j)];
            grid[index(gridSize - (1 + i), j)] = grid[index(i, gridSize - (1 + j))];
            grid[index(i, gridSize - (1 + j))] = tmp;
        }
}

void CheckerBoard::set_board()
{
    size_t blackBox;
    for (size_t i = 0; i < gridSize; i++)
    {
        if (i % 2 == 0)
            blackBox = 1;
        else
            blackBox = 0;

        for (size_t j = 0; j < gridSize; j++)
        {
            if (j % 2 == blackBox)
            {
                if (i < (gridSize - 1) / 2)
                    grid[index(i, j)].placePiece(whitePiecePerspective);
                else if (i > (gridSize + 1) / 2)
                    grid[index(i, j)].placePiece(!whitePiecePerspective);
            }
        }
    }
}
bool CheckerBoard::immobilized(CheckerBoardSquare &square) const
{
    if (square.isEmpty())
        return false;
    // else
    // {
    //     if (whitePiecePerspective == square.holdsWhite())
    //     {
    //         if ((square.getX() + 1) < 8 && (square.getX() - 1) > 0 && (square.getY() + 1) < 8)
    //         {
    //             if (grid[index(square.getX() + 1, square.getY() + 1)].isEmpty() || grid[index(square.getX() - 1, square.getY() + 1)].isEmpty())
    //                 return false;
    //         }
    //     }
    //     else
    //     {
    //         if ((square.getX() + 1) < 8 && (square.getX() - 1) > 0 && (square.getY() + 1) < 8)
    //             if (grid[index(square.getX() + 1, square.getY() + 1)].isEmpty() || grid[index(square.getX() - 1, square.getY() + 1)].isEmpty())
    //                 return false;
    //     }
    //     if (grid[index(square.getX(), square.getY())].isKing())
    //     {
    //         /* code */
    //     }
    // }
}

bool CheckerBoard::game_over() const {}

// CheckerBoardSquare *CheckerBoard::operator[](size_t i)
// {
//     if (i >= gridSize)
//     {
//         std::cerr << "Coordinates exceed board size!" << std::endl;
//         exit(1);
//     }
//     return &grid[i];
// }

CheckerBoardSquare &CheckerBoard::operator()(size_t xCoordinate, size_t yCoordinate) { return grid[index(xCoordinate, yCoordinate)]; }

bool CheckerBoard::move(CheckerBoardSquare &square, CheckerBoardSquare &destination)
{
    // check if king

    return true;
}

std::ostream &operator<<(std::ostream &strm, CheckerBoard &printed)
{
    size_t size = printed.size();
    strm << "#################################" << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        strm << "#";
        for (size_t j = 0; j < size; j++)
        {
            if (printed(i, j).isEmpty())
                strm << "   #";
            else
            {
                if (printed(i, j).holdsWhite())
                    strm << " + #";
                else
                    strm << " x #";
            }
        }
        strm << std::endl
             << "#################################";
        strm << std::endl;
    }
    return strm;
}
