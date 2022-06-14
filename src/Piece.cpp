#include "Piece.hh"
Piece::Piece() = default;
Piece::Piece(bool lightColoured, bool promoted)
    : isLightColour(lightColoured), isKing(promoted) {}
Piece::Piece(Piece &) = default;
Piece::~Piece() = default;
void Piece::promotePiece() { isKing = true; }
bool Piece::isLightColoured() const { return isLightColour; }
bool Piece::isPromoted() const { return isKing; }