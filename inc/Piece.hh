#ifndef PIECE_HH
#define PIECE_HH
class Piece
{
private:
    int xCoordinate;
    int yCoordinate;
    bool isLightColour;
    bool isKing;

public:
    Piece();
    Piece(int x, int y, bool lightColoured, bool promoted);
    Piece(Piece &);
    ~Piece();
    int getX() const;
    int getY() const;
    void setCoordinates(int x, int y);
    void promotePiece();
    bool isLightColoured() const;
    bool isPromoted() const;
};

#endif
