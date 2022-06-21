#include "Square.hh"
Square::Square(std::pair<int, int> Coords) : coords(std::make_pair(Coords.first, Coords.second)), piece(nullptr)
{
}
Square::~Square() = default;
void Square::clear()
{
    piece->~Piece();
    piece = nullptr;
}
void Square::placePiece(std::shared_ptr<Piece> p)
{
    removePiece();
    piece = p;
}
Piece &Square::getPiece()
{
    return *piece;
}
void Square::removePiece()
{
    piece = nullptr;
}
bool Square::isEmpty() const { return piece == nullptr; }
void Square::setCoords(std::pair<int, int> Coords) { coords = Coords; }
std::pair<int, int> Square::getCoords() const { return coords; }
void Square::promotePiece() { piece->promotePiece(); }