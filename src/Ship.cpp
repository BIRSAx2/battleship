#include "Ship.h"
Ship::Ship(std::string name, int width, int hits, Orientation orientation) : name_(std::move(name)), width_(width), hits_(hits), orientation_(orientation) {}
const std::string &Ship::GetName() const {
  return name_;
}
void Ship::SetName(const std::string &name) {
  name_ = name;
}
int Ship::GetWidth() const {
  return width_;
}
void Ship::SetWidth(int width) {
  width_ = width;
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
void Ship::SetOrientation(Orientation orientation) {
  orientation_ = orientation;
}
bool Ship::IsSunk() const {
  return hits_ >= width_;
}
Ship::Ship(std::string name, int width, int hits) : name_(std::move(name)), width_(width), hits_(hits) {
  orientation_ = UNSET;
}
Ship::Ship(int width) : width_(width), name_("/"), hits_(0) {
  orientation_ = UNSET;
}
Ship::Ship(std::string name, int width) : name_(std::move(name)), width_(width) {
  orientation_ = UNSET;
}
Ship::Ship(std::string name, int width, OccupationType occupation_type) : name_(std::move(name)), width_(width),
																		  occupation_type_(occupation_type) {
  orientation_ = UNSET;
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
int Ship::GetShipWidth(OccupationType occupation_type) {
  switch (occupation_type) {
	case SUBMARINE:
	  return 1;
	case BATTLESHIP:
	  return 5;
	case SUPPORT_SHIP:
	  return 3;

	default:
	  return 0;
  }
}
