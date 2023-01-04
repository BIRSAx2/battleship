#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include "Orientation.h"
#include "Utility.h"
#include <algorithm>
#include <map>
#include <ostream>

class Coordinates {
 private:
  int row_, col_;

 public:
  Coordinates(int row, int col);
  Coordinates();
  static std::pair<Coordinates, Coordinates> FromUserCoordinates(const std::string &user_coordinates);
  int GetRow() const;
  void SetRow(int row);
  int GetCol() const;
  void SetCol(int col);
  bool IsInBounds(int min, int max) const;
  // Restituisce le count coordinate immediatamente affianco a start in vertical/orizzontale (orientation)
  static std::vector<Coordinates> GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count);
  // Restituisce le coordinate delle celle sopra, sotto, a destra e a sinistra. (A stella)
  static std::vector<Coordinates> GetAdjacentStarCoordinates(Coordinates starting);
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
