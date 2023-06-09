#ifndef PIECE_HH
#define PIECE_HH
class Piece
{
private:
    bool isLightColour;
    bool isKing;

public:
    Piece();
    Piece(bool lightColoured, bool promoted);
    Piece(Piece &p);
    Piece(const Piece &p);
    ~Piece();
    void promotePiece();
    bool isLightColoured() const;
    bool isPromoted() const;
};

#endif
