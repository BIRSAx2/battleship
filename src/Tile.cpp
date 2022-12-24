#include "Tile.h"
Tile::Tile(int row, int column) {
  coordinates_ = Coordinates(row, column);
  occupation_type_ = EMPTY;
}
Tile::Tile(Coordinates coordinates) {
  coordinates_ = coordinates;
  occupation_type_ = EMPTY;
}

Tile::Tile() {
  occupation_type_ = EMPTY;
}

OccupationType Tile::GetStatus() const {
  return occupation_type_;
}
bool Tile::IsOccupied() const {
  return occupation_type_ != EMPTY && occupation_type_ != HIT && occupation_type_ != MISS;
}
bool Tile::IsRandomlyAvailable() const {
  // TODO: change this to target only non adjacent squares
  return true;
}
std::ostream &operator<<(std::ostream &os, const Tile &tile) {
  switch (tile.GetOccupationType()) {
	case EMPTY:
	  os << "_";
	  break;
	case HIT:
	  os << "X";
	  break;
	case MISS:
	  os << "O";
	  break;
	case SUBMARINE:
	  os << "E";
	  break;
	case BATTLESHIP:
	  os << "C";
	  break;
	case SUPPORT_BATTLESHIP:
	  os << "S";
	  break;
  }
  return os;
}
OccupationType Tile::GetOccupationType() const {
  return occupation_type_;
}
void Tile::SetOccupationType(OccupationType occupation_type) {
  occupation_type_ = occupation_type;
}
const Coordinates &Tile::GetCoordinates() const {
  return coordinates_;
}
void Tile::SetCoordinates(const Coordinates &coordinates) {
  coordinates_ = coordinates;
}
