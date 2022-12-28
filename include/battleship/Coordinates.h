#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include "Orientation.h"
#include "Utility.h"
#include <algorithm>
#include <ostream>
#include <map>

class Coordinates {
 private:
  int row_, col_;

 public:
  Coordinates(int row, int col);
  Coordinates();
  static std::pair<Coordinates, Coordinates> FromUserCoordinates(const std::string& user_coordinates);
  int GetRow() const;
  void SetRow(int row);
  int GetCol() const;
  void SetCol(int col);
  bool IsInBounds(int min, int max);
  static std::vector<Coordinates> GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count);
  bool operator==(const Coordinates &rhs) const;
  bool operator!=(const Coordinates &rhs) const;
  bool operator<(const Coordinates &rhs) const;
  bool operator>(const Coordinates &rhs) const;
  bool operator<=(const Coordinates &rhs) const;
  bool operator>=(const Coordinates &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);
  static Coordinates ParseCoordinate(std::string &coordinates);

};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
