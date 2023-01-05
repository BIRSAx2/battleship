#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_

#include "OccupationType.h"
#include "Orientation.h"
#include "Utility.h"
#include <ostream>
#include <string>

class Ship {
 protected:
  std::string name_;
  int width_, hits_ = 0;
  Orientation orientation_;
  OccupationType occupation_type_;

 public:
  Ship();
  Ship(int width, Orientation orientation);
  bool IsSunk() const;
  int GetWidth() const;
  int GetHits() const;
  void IncreaseHits();
  void SetHits(int hits);
  Orientation GetOrientation() const;
  OccupationType GetOccupationType() const;
  void SetOccupationType(OccupationType occupation_type);
  friend std::ostream &operator<<(std::ostream &os, const Ship &ship);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
