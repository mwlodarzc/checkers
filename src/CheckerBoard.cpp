#include "ChceckerBoard.hh"
int CheckerBoard::index(size_t xCoordinate, size_t yCoordinate)
{
    if (xCoordinate < 0 || xCoordinate >= gridSize || yCoordinate < 0 || yCoordinate >= gridSize)
    {
        std::cerr << "Coordinates exceed board size!" << std::endl;
        exit(1);
    }
    return xCoordinate + gridSize * yCoordinate;
}

void CheckerBoard::flip_board()
{
    CheckerBoardSquare tmp;
    for (size_t i = 0; i < gridSize; i++)
        for (size_t j = 0; j < gridSize; j++)
        {
            tmp = grid[index(gridSize - (1 + i), j)];
            grid[index(gridSize - (1 + i), j)] = grid[index(i, j)];
            grid[index(i, j)] = tmp;
        }
}

void CheckerBoard::set_board()
{
    size_t blackBox;
    for (size_t i = 0; i < gridSize; i++)
    {
        if (i % 2 == 0)
            blackBox = 0;
        else
            blackBox = 1;

        for (size_t j = 0; j < gridSize; j++)
        {
            if (j % 2 == blackBox)
            {
                if (i < (gridSize - 1) / 2)
                    grid[index(i, j)].placePiece(true);
                else if (i > (gridSize + 1) / 2)
                    grid[index(i, j)].placePiece(false);
            }
        }
    }
}

CheckerBoardSquare *CheckerBoard::operator[](size_t i)
{
    if (i >= gridSize)
    {
        std::cerr << "Coordinates exceed board size!" << std::endl;
        exit(1);
    }
    return &grid[i];
}
CheckerBoardSquare &CheckerBoard::operator()(size_t x, size_t y) { return grid[index(x, y)]; }

size_t CheckerBoard::size() { return gridSize; }
CheckerBoard::CheckerBoard(int size) : gridSize(size), grid(new CheckerBoardSquare[size * size]) { set_board(); }

bool CheckerBoard::move(size_t xCoordinate, size_t yCoordinate)
{
    if (xCoordinate < 0 || xCoordinate >= gridSize || yCoordinate < 0 || yCoordinate >= gridSize)
    {
        std::cerr << "Coordinates exceed board size!" << std::endl;
        exit(1);
    }
    return true;
}

CheckerBoard::~CheckerBoard() { delete[] grid; }

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
