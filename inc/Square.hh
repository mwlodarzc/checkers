#ifndef SQUARE_HH
#define SQUARE_HH
#include <memory>
#include "Piece.hh"
#include <iostream>
class Square
{
private:
    std::pair<int, int> coords;
    std::shared_ptr<Piece> piece;

public:
    Square() = default;
    Square(std::pair<int, int> Coords);
    ~Square();
    void clear();
    void placePiece(std::shared_ptr<Piece> p);
    Piece &getPiece();
    void promotePiece();
    void removePiece();
    bool isEmpty() const;
    void setCoords(std::pair<int, int> Coords);
    std::pair<int, int> getCoords() const;
};

#endif
