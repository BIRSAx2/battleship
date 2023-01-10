#include "Coordinates.h"
Coordinates::Coordinates(std::string &user_coordinates) {
  Coordinates parsed = ParseCoordinates(user_coordinates);
  SetRow(parsed.GetRow());
  SetCol(parsed.GetCol());
}
Coordinates::Coordinates(int row, int col) {
  if (!IsValid(row, col)) throw std::invalid_argument("Invalid coordinates");
  row_col_.first = row;
  row_col_.second = col;
}

void Coordinates::SetRow(int row) {

  if (!IsValid(row, row_col_.second)) throw std::invalid_argument("Invalid coordinates");
  row_col_.first = row;
}

void Coordinates::SetCol(int col) {
  if (!IsValid(row_col_.first, col)) throw std::invalid_argument("Invalid coordinates");
  row_col_.second = col;
}
int Coordinates::GetRow() const {
  return row_col_.first;
}
int Coordinates::GetCol() const {
  return row_col_.second;
}
bool Coordinates::IsValid(int row, int col) {
  return row >= 0 && row < 12 && col >= 0 && col < 12;
}
bool Coordinates::operator==(const Coordinates &rhs) const {
  return row_col_ == rhs.row_col_;
}
bool Coordinates::operator!=(const Coordinates &rhs) const {
  return !(rhs == *this);
}
bool Coordinates::operator<(const Coordinates &rhs) const {
  return row_col_ < rhs.row_col_;
}

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
  os << "(" << coordinates.row_col_.first << "," << coordinates.row_col_.second << ")";
  return os;
}
int Coordinates::CalculateOffsetTo(Coordinates coordinates) {
  if (GetRow() != coordinates.GetRow() && GetCol() != coordinates.GetCol()) throw std::invalid_argument("Cannot calculate offset. The two coordinates need to be either in the same row or in the same col");

  // TODO: add check for this to work $coordinates must be after $this
  // horizontal => the offset is the difference between columns
  if (coordinates.GetRow() == GetRow()) {

	return coordinates.GetCol() - GetCol();
  } else {
	// vertical => the offset is the difference between rows
	return coordinates.GetRow() - GetRow();
  }
}

Coordinates Coordinates::ParseCoordinates(std::string &coordinates) {
  int row = GetNumberFromLetter(coordinates[0]);
  int col = 0;

  if (coordinates.size() == 3)
	col = 10 + (coordinates[2] - '0');
  else
	col = coordinates[1] - '0';

  // col - 1 because the string range is 1 - 12, but we use 0 - 11
  return Coordinates(row, col - 1);
}
std::vector<Coordinates> Coordinates::GetCoordinatesBetween(Coordinates start, Coordinates end) {
  if (start.GetCol() != end.GetCol() && start.GetRow() != end.GetRow()) throw std::invalid_argument("Cannot generate in between coordinate if end and start are not on the same row/col");

  std::vector<Coordinates> locations;
  // Same row => get the horizontal coordinates in between start and end
  if (start.GetRow() == end.GetRow()) {
	for (int i = start.GetCol(); i <= end.GetCol(); ++i) {
	  locations.emplace_back(Coordinates(start.GetRow(), i));
	}
	return locations;
  }

  // Same col => get the horizontal coordinates in between start and end
  for (int i = start.GetRow(); i <= end.GetRow(); ++i) {
	locations.emplace_back(Coordinates(i, start.GetCol()));
  }
  return locations;
}
Coordinates Coordinates::GetRandomCoordinates() {
  return {
	  RandomIntInRange(0, 12),
	  RandomIntInRange(0, 12)};
}
