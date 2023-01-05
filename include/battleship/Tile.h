#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_

#include "Coordinates.h"
#include "OccupationType.h"
#include <ostream>
class Tile {
 private:
  OccupationType occupation_type_;

 public:
  Tile();
  Tile(int row, int column);
  bool IsOccupied() const;
  friend std::ostream &operator<<(std::ostream &os, const Tile &tile);
  OccupationType GetOccupationType() const;
  void SetOccupationType(OccupationType occupation_type);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_
