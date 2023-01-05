#include "../include/battleship/Tile.h"
#include "Coordinates.cpp"

Tile::Tile(int row, int col){
    coords_ = Coordinates(row, col);
    occType_ = EMPTY;
}

bool Tile::IsOccupied() const{
    return (occType_ == SUBMARINE) || (occType_ == BATTLESHIP) || (occType_ == SUPPORT_BATTLESHIP); 
}





Tile& Tile::operator=(Tile t){
    coords_ = t.GetCoordinates();
    occType_ = t.GetOccupationType();

    return *this;
}

bool operator==(Tile t1, Tile t2){
    return (t1.GetCoordinates() == t2.GetCoordinates()) && (t1.GetOccupationType() == t2.GetOccupationType());
}

bool operator!=(Tile t1, Tile t2){
    return !(t1 == t2);
}

std::ostream &operator<<(std::ostream &os, const Tile &tile){
    return os << "Coordinate: " << tile.GetCoordinates() << std::endl << "Occupation Type: " << tile.GetOccupationType();
}