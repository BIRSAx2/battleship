#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_

#include "Orientation.h"
#include <string>

class Ship {
 protected:
  Ship(std::string name, int width);
  std::string name_;
  int width_, hits_ = 0;
  Orientation orientation_;

 public:
  Ship(std::string name, int width, int hits, Orientation orientation);
  Ship(std::string name, int width, int hits);
  explicit Ship(int width);
  bool IsSunk() const;
  const std::string &GetName() const;
  void SetName(const std::string &name);
  int GetWidth() const;
  void SetWidth(int width);
  int GetHits() const;
  void SetHits(int hits);
  Orientation GetOrientation() const;
  void SetOrientation(Orientation orientation);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
