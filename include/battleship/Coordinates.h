#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include <ostream>
class Coordinates {
 private:
  int row_, col_;

 public:
  Coordinates(int row, int col);
  Coordinates();
  int GetRow() const;
  void SetRow(int row);
  int GetCol() const;
  void SetCol(int col);
  bool operator==(const Coordinates &rhs) const;
  bool operator!=(const Coordinates &rhs) const;
  bool operator<(const Coordinates &rhs) const;
  bool operator>(const Coordinates &rhs) const;
  bool operator<=(const Coordinates &rhs) const;
  bool operator>=(const Coordinates &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
