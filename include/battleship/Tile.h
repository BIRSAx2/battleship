#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_

#include "Coordinates.h"
#include "OccupationType.h"
#include <ostream>
class Tile {
 private:
  OccupationType occupation_type_;
  Coordinates coordinates_;

 public:
  Tile();
  Tile(int row, int column);
  Tile(Coordinates coordinates);
  OccupationType GetStatus() const;
  bool IsOccupied() const;
  bool IsRandomlyAvailable() const;
  friend std::ostream &operator<<(std::ostream &os, const Tile &tile);
  OccupationType GetOccupationType() const;
  void SetOccupationType(OccupationType occupation_type);
  const Coordinates &GetCoordinates() const;
  void SetCoordinates(const Coordinates &coordinates);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_TILE_H_
