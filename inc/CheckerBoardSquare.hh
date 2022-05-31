#ifndef CHECKER_HH
#define CHECKER_HH
class CheckerBoardSquare
{
private:
    bool piecePlaced;
    bool pieceLightColoured;

public:
    CheckerBoardSquare();
    CheckerBoardSquare(bool placed, bool lightColoured);
    CheckerBoardSquare(CheckerBoardSquare &);
    ~CheckerBoardSquare();
    void operator=(CheckerBoardSquare &square);
    void placePiece(bool placeWhite);
    void removePiece();
    bool isEmpty();
    bool holdsWhite();
};

#endif
