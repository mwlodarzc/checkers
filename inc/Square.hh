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
    Square(Square *p);
    Square(Square &p);
    Square(const Square &p);
    ~Square();
    void clear();
    void placePiece(std::shared_ptr<Piece> p);
    std::shared_ptr<Piece> getPiece();
    void removePiece();
    bool movePiece(Square &square);
    bool isEmpty() const;
    void setCoords(std::pair<int, int> Coords);
    std::pair<int, int> getCoords() const;
};

#endif
