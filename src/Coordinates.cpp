#include "Coordinates.h"

Coordinates::Coordinates() : row_(0), col_(0) {}
Coordinates::Coordinates(int row, int col) : row_(row), col_(col) {}
int Coordinates::GetRow() const {
  return row_;
}
void Coordinates::SetRow(int row) {
  row_ = row;
}
int Coordinates::GetCol() const {
  return col_;
}
void Coordinates::SetCol(int col) {
  col_ = col;
}
bool Coordinates::operator==(const Coordinates &rhs) const {
  return row_ == rhs.row_ && col_ == rhs.col_;
}
bool Coordinates::operator!=(const Coordinates &rhs) const {
  return !(rhs == *this);
}
bool Coordinates::operator<(const Coordinates &rhs) const {
  if (row_ < rhs.row_)
	return true;
  if (rhs.row_ < row_)
	return false;
  return col_ < rhs.col_;
}
bool Coordinates::operator>(const Coordinates &rhs) const {
  return rhs < *this;
}
bool Coordinates::operator<=(const Coordinates &rhs) const {
  return !(rhs < *this);
}
bool Coordinates::operator>=(const Coordinates &rhs) const {
  return !(*this < rhs);
}
std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
  os << "(" << coordinates.row_ << "," << coordinates.col_ << ")";
  return os;
}
