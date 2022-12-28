#include "Tile.h"
#include "Utility.h"
#include <iostream>
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
	  os << colour_text_256("~", 87);
	  break;
	case HIT:
	  os << colour_text_256("X",1);
	  break;
	case MISS:
	  os << colour_text_256("O", 220);
	  break;
	case SUBMARINE:
	  os << colour_text_256("E", 100);
	  break;
	case BATTLESHIP:
	  os << colour_text_256("C", 127);
	  break;
	case SUPPORT_BATTLESHIP:
	  os << colour_text_256("S", 106);
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
