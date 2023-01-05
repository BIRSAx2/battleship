#include "Ship.h"
Ship::Ship(int width, Orientation orientation) : width_(width), hits_(0), orientation_(orientation), occupation_type_{static_cast<OccupationType>(UNSET)} {}
int Ship::GetWidth() const {
  return width_;
}
int Ship::GetHits() const {
  return hits_;
}
void Ship::SetHits(int hits) {
  hits_ = hits;
}
Orientation Ship::GetOrientation() const {
  return orientation_;
}
bool Ship::IsSunk() const {
  return hits_ >= width_;
}
OccupationType Ship::GetOccupationType() const {
  return occupation_type_;
}
void Ship::SetOccupationType(OccupationType occupation_type) {
  occupation_type_ = occupation_type;
}
void Ship::IncreaseHits() {
  hits_++;
}
std::ostream &operator<<(std::ostream &os, const Ship &ship) {
  os << ship.GetOccupationType() << " " << ship.GetOrientation() << " width: " << ship.GetWidth() << " hits: " << ship.GetHits();
  return os;
}
Ship::Ship() : width_(0), hits_(0), orientation_(UNSET), occupation_type_(EMPTY), name_("-") {
}
