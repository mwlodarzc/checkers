#include "CheckerBoardSquare.hh"
CheckerBoardSquare::CheckerBoardSquare() : xCoordinate(0), yCoordinate(0), piecePlaced(false), pieceLightColoured(false), pieceIsKing(false) {}
CheckerBoardSquare::CheckerBoardSquare(int x, int y, bool placed, bool lightColoured, bool isKing)
    : xCoordinate(x), yCoordinate(y), piecePlaced(placed), pieceLightColoured(lightColoured), pieceIsKing(isKing) {}
CheckerBoardSquare::CheckerBoardSquare(CheckerBoardSquare &) = default;
CheckerBoardSquare::~CheckerBoardSquare() = default;
int CheckerBoardSquare::getX() const { return xCoordinate; }
int CheckerBoardSquare::getY() const { return yCoordinate; }
void CheckerBoardSquare::setX(int x) { xCoordinate = x; }
void CheckerBoardSquare::setY(int y) { yCoordinate = y; }
void CheckerBoardSquare::clear()
{
    piecePlaced = false;
    // pieceLightColoured = false;
    pieceIsKing = false;
}
void CheckerBoardSquare::placePiece(bool placeWhite)
{
    piecePlaced = true;
    pieceLightColoured = placeWhite;
}
void CheckerBoardSquare::removePiece() { piecePlaced = false; }
void CheckerBoardSquare::promotePiece() { pieceIsKing = true; }
bool CheckerBoardSquare::isEmpty() const { return !piecePlaced; }
bool CheckerBoardSquare::holdsWhite() const { return pieceLightColoured; }
bool CheckerBoardSquare::isKing() const { return pieceIsKing; }
