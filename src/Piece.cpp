#include "Piece.hh"
Piece::Piece() = default;
Piece::Piece(int x, int y, bool lightColoured, bool promoted)
    : xCoordinate(x), yCoordinate(y), isLightColour(lightColoured), isKing(promoted) {}
Piece::Piece(Piece &) = default;
Piece::~Piece() = default;
int Piece::getX() const { return xCoordinate; }
int Piece::getY() const { return yCoordinate; }
void Piece::setCoordinates(int x, int y)
{
    xCoordinate = x;
    yCoordinate = y;
}
void Piece::promotePiece() { isKing = true; }
bool Piece::isLightColoured() const { return isLightColour; }
bool Piece::isPromoted() const { return isKing; }