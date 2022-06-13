#ifndef SQUARE_HH
#define SQUARE_HH
#include <memory>
#include "Piece.hh"
#include <iostream>
class Square
{
private:
    std::shared_ptr<Piece> piece;

public:
    Square();
    Square(std::shared_ptr<Piece> p);
    Square(Piece &p);
    ~Square();
    void clear();
    void placePiece(std::shared_ptr<Piece> p);
    std::shared_ptr<Piece> getPiece();
    void removePiece();
    bool movePiece(Square &square);
    bool isEmpty() const;
};

#endif
