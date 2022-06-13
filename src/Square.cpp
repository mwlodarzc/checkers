#include "Square.hh"
Square::Square() : piece(nullptr) {}
Square::Square(std::shared_ptr<Piece> p) : piece(p) {}
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
Square::Square(Piece &p) { piece = std::make_shared<Piece>(p); }
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