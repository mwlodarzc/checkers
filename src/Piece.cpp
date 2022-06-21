#include "Piece.hh"
Piece::Piece() = default;
Piece::Piece(bool lightColoured, bool promoted)
    : isLightColour(lightColoured), isKing(promoted) {}
Piece::Piece(Piece &p)
{
    isLightColour = p.isLightColour;
    isKing = p.isKing;
}
Piece::Piece(const Piece &p)
{
    isLightColour = p.isLightColour;
    isKing = p.isKing;
}

Piece::~Piece() = default;
void Piece::promotePiece() { isKing = true; }
bool Piece::isLightColoured() const { return isLightColour; }
bool Piece::isPromoted() const { return isKing; }