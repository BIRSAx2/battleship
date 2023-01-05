#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_

#include "Coordinates.h"
#include "OccupationType.h"

class Tile {
public:
    Tile(int row, int col);
    
    Tile(): occType_{EMPTY}, coords_{Coordinates()} {};

    Tile(Coordinates coords): occType_{EMPTY}, coords_{coords} {};

    Coordinates GetCoordinates() const { return coords_; };

    OccupationType GetOccupationType() const { return occType_; };
    
    void SetCoordinates(const Coordinates coords) { coords_ = coords; };

    void SetOccupationType(const OccupationType occType) { occType_ = occType; };

    bool IsOccupied() const;

    // bool IsRandomlyAvailable() const;
    
    Tile& operator=(Tile t);


private:
    OccupationType occType_;
    Coordinates coords_;
};

bool operator==(Tile t1, Tile t2);

bool operator!=(Tile t1, Tile t2);

std::ostream &operator<<(std::ostream &os, const Tile &tile);

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_

