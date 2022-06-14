#include "Square.hh"
Square::Square(int id) : index(id), piece(nullptr) {}
Square::Square(Square *p)
{
    index = p->index;
    piece = p->piece;
}
Square::Square(Square &p)
{
    index = p.index;
    piece = p.piece;
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
std::shared_ptr<Piece> Square::getPiece() { return piece; }
void Square::removePiece()
{
    if (piece != nullptr)
    {
        piece.~shared_ptr();
        piece = nullptr;
    }
}
bool Square::movePiece(Square &square)
{
    if (!square.isEmpty() || isEmpty())
    {
        std::cerr << "fail1" << std::endl;
        return false;
    }
    square.piece = piece;
    piece = nullptr;
    return true;
}
bool Square::isEmpty() const { return piece == nullptr; }
void Square::setIndex(int i) { index = i; }
int Square::getIndex() const { return index; }