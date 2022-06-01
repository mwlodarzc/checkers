#ifndef PIECE_HH
#define PIECE_HH
class Piece
{
private:
    int xCoordinate;
    int yCoordinate;

    bool pieceLightColoured;
    bool pieceIsKing;

public:
    CheckerBoardSquare();
    CheckerBoardSquare(int x, int y, bool placed, bool lightColoured, bool isKing);
    CheckerBoardSquare(CheckerBoardSquare &);
    ~CheckerBoardSquare();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    void clear();
    void placePiece(bool placeWhite);
    void removePiece();
    void promotePiece();
    bool isEmpty() const;
    bool holdsWhite() const;
    bool isKing() const;
};

#endif
