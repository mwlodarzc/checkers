#ifndef SQUARE_HH
#define SQUARE_HH
#include <memory>
#include "Piece.hh"
#include <iostream>
class Square
{
private:
    int index;
    std::shared_ptr<Piece> piece;

public:
    Square() = default;
    Square(int id);
    Square(Square *p);
    Square(Square &p);
    ~Square();
    void clear();
    void placePiece(std::shared_ptr<Piece> p);
    std::shared_ptr<Piece> getPiece();
    void removePiece();
    bool movePiece(Square &square);
    bool isEmpty() const;
    void setIndex(int i);
    int getIndex() const;
};

#endif
