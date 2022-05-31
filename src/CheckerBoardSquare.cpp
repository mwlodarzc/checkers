#include "CheckerBoardSquare.hh"
CheckerBoardSquare::CheckerBoardSquare() : piecePlaced(false), pieceLightColoured(false) {}

CheckerBoardSquare::CheckerBoardSquare(bool placed, bool lightColoured)
    : piecePlaced(placed), pieceLightColoured(lightColoured) {}

CheckerBoardSquare::CheckerBoardSquare(CheckerBoardSquare &) = default;

CheckerBoardSquare::~CheckerBoardSquare() = default;

void CheckerBoardSquare::operator=(CheckerBoardSquare &square)
{
    piecePlaced = square.piecePlaced;
    pieceLightColoured = square.pieceLightColoured;
}

void CheckerBoardSquare::placePiece(bool placeWhite)
{
    piecePlaced = true;
    pieceLightColoured = placeWhite;
}
void CheckerBoardSquare::removePiece() { piecePlaced = false; }

bool CheckerBoardSquare::isEmpty() { return !piecePlaced; }

bool CheckerBoardSquare::holdsWhite() { return pieceLightColoured; }