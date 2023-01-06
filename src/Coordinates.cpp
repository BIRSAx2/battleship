#include "Coordinates.h"
#include <sstream>

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
  return row_ < rhs.row_ || (row_ == rhs.row_ && col_ < rhs.col_);
}
bool Coordinates::operator>(const Coordinates &rhs) const {
  return rhs < *this;
}
//bool Coordinates::operator<=(const Coordinates &rhs) const {
//  return !(rhs < *this);
//}
//bool Coordinates::operator>=(const Coordinates &rhs) const {
//  return !(*this < rhs);
//}
std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
  os << "(" << coordinates.row_ << "," << coordinates.col_ << ")";
  return os;
}
bool Coordinates::IsInBounds(int min, int max) const {
  return row_ >= min and row_ < max and col_ >= min and col_ < max;
}

std::vector<Coordinates> Coordinates::GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count) {
  if (!starting.IsInBounds(0, 12)) throw std::invalid_argument("Invalid adjacent coordinate: The starting point is outside the board's bounds.");

  std::vector<Coordinates> adjacentCoordinates = std::vector<Coordinates>();

  if (orientation == HORIZONTAL) {
	// loop over the cols
	for (int i = starting.GetCol(); i < starting.GetCol() + count; i++) {
	  if (!Coordinates(starting.GetRow(), i).IsInBounds()) throw std::invalid_argument("Cannot generate the next adjacent coordinates because they are outside the board's bounds");
	  adjacentCoordinates.emplace_back(starting.GetRow(), i);
	}
  } else {
	// loop over the rows
	for (int i = starting.GetRow(); i < starting.GetRow() + count; i++) {
	  if (!Coordinates(i, starting.GetCol()).IsInBounds()) throw std::invalid_argument("Cannot generate the next adjacent coordinates because they are outside the board's bounds");
	  adjacentCoordinates.emplace_back(i, starting.GetCol());
	}
  }

  return adjacentCoordinates;
}
std::pair<Coordinates, Coordinates> Coordinates::FromUserCoordinates(const std::string &user_coordinates) {
  std::vector<std::string> tokens = split(user_coordinates, ' ');

  if (tokens.size() != 2) throw std::invalid_argument("Invalid coordinates format.\nThe coordinates should be in the format XYorigin XYtarget, where the X is a letter from A to N, and Y is a number from 1 to 12");

  Coordinates from = ParseCoordinate(tokens.at(0));
  Coordinates to = ParseCoordinate(tokens.at(1));

  return std::make_pair(from, to);
}

std::pair<Coordinates, Coordinates> Coordinates::ParsePlacementCoordinates(std::string bow_stern) {
  std::vector<std::string> coordinate_pair = split(bow_stern, ' ');

  std::cout << coordinate_pair.at(0) << std::endl;
  std::cout << coordinate_pair.at(1) << std::endl;
  return std::make_pair(ParseCoordinate(coordinate_pair.at(0)), ParseCoordinate(coordinate_pair.at(1)));
}
Coordinates Coordinates::ParseCoordinate(std::string &origin) {
  std::map<char, int> map{{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'L', 9}, {'M', 10}, {'N', 11}};

  char x;

  x = toupper(origin.at(0));

  if (x < 'A' || x > 'N') throw std::invalid_argument(std::string("The X coordinate must be between A and N inclusive, got: ") + x);

  int row = map.at(x);

  std::string y = origin.substr(1);

  if (y.empty() || !std::all_of(y.begin(), y.end(), ::isdigit)) throw std::invalid_argument(std::string("The Y coordinate must be a number between 1 and 12 inclusive, got:") + y);

  int col = std::stoi(y);
  return {row, col - 1};
}
std::vector<Coordinates> Coordinates::GetAdjacentStarCoordinates(Coordinates starting) {

  // Restituisce le delle celle immediatamente adiacenti a starting. Sopra, sotto. ai lati ma non in diagonale.
  std::pair<int, int> offsets[] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
  std::vector<Coordinates> coordinates;
  for (auto offset : offsets) {
	Coordinates tmp = {starting.GetRow() + offset.first, starting.GetCol() + offset.second};
	if (tmp.IsInBounds()) {
	  coordinates.push_back(tmp);
	}
  }
  return coordinates;
}

size_t CoordinatesHashFunction::operator()(const Coordinates &point) const {
  size_t row_hash = std::hash<int>()(point.GetRow());
  size_t col_hash = std::hash<int>()(point.GetCol()) << 1;
  return row_hash ^ col_hash;
}
bool CoordinatesComparator::operator()(const Coordinates &point, const Coordinates &other) const {
  return point == other;
}
