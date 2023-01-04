#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_

#include "OccupationType.h"
#include "Orientation.h"
#include "Utility.h"
#include <ostream>
#include <string>

class Ship {
 protected:
  Ship(std::string name, int width);
  Ship(std::string name, int width, OccupationType occupation_type);
  std::string name_;
  int width_, hits_ = 0;
  Orientation orientation_;
  OccupationType occupation_type_;

 public:
  Ship();
  Ship(std::string name, int width, int hits, Orientation orientation);
  Ship(std::string name, int width, int hits);
  explicit Ship(int width);
  bool IsSunk() const;
  const std::string &GetName() const;
  void SetName(const std::string &name);
  int GetWidth() const;
  void SetWidth(int width);
  int GetHits() const;
  void IncreaseHits();
  void SetHits(int hits);
  Orientation GetOrientation() const;
  void SetOrientation(Orientation orientation);
  OccupationType GetOccupationType() const;
  void SetOccupationType(OccupationType occupation_type);
  friend std::ostream &operator<<(std::ostream &os, const Ship &ship);
  static int GetShipWidth(OccupationType occupation_type);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
