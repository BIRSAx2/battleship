#include "Ship.h"
#include "Submarine.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>

bool Ship::IsSunk() {
  return hit_locations_offset_.size() >= width_;
}
void Ship::HitLocation(Coordinates location) {
  int offset = bow_.CalculateOffsetTo(location);
  if (offset >= 0 && offset < width_) {
	hit_locations_offset_.insert(offset);
  }
}
std::vector<Coordinates> Ship::GetLocations() {
  return Coordinates::GetCoordinatesBetween(bow_, stern_);
}
int Ship::GetWidth() const {
  return width_;
}
void Ship::SetWidth(int width) {
  width_ = width;
}
ShipType Ship::GetShipType() const {
  return ship_type_;
}
const Coordinates &Ship::GetBow() const {
  return bow_;
}
void Ship::SetBow(const Coordinates &bow) {
  bow_ = bow;
}
const Coordinates &Ship::GetStern() const {
  return stern_;
}
void Ship::SetStern(const Coordinates &stern) {
  stern_ = stern;
}
std::ostream &operator<<(std::ostream &os, const Ship &ship) {
  os << "Icon: " << ship.GetIcon() << " Width: " << ship.GetWidth() << " Orientation: ";
  if (ship.IsHorizontal()) {
	os << "horizontal ";
  } else {
	os << "vertical ";
  }
  os << "Hits received: " << ship.GetHitLocationsOffset().size();
  return os;
}
bool Ship::IsHorizontal() const {
  return bow_.GetRow() == stern_.GetRow();
}
const std::string &Ship::GetIcon() const {
  return icon_;
}
void Ship::SetIcon(const std::string &icon) {
  icon_ = icon;
}
const std::string &Ship::GetHitIcon() const {
  return hit_icon_;
}
void Ship::SetHitIcon(const std::string &hit_icon) {
  hit_icon_ = hit_icon;
}
const std::set<int> &Ship::GetHitLocationsOffset() const {
  return hit_locations_offset_;
}
void Ship::SetHitLocationsOffset(const std::set<int> &hit_locations_offset) {
  hit_locations_offset_ = hit_locations_offset;
}
std::string Ship::ToString(Coordinates location) {
  if (std::find(hit_locations_offset_.begin(), hit_locations_offset_.end(), bow_.CalculateOffsetTo(location))
	  != hit_locations_offset_.end()) return ColourText256(hit_icon_, hit_icon_color_);
  return ColourText256(icon_, icon_color_);
}
Coordinates Ship::GetShipCenter() {
  auto locations = GetLocations();
  return locations.at(locations.size() / 2);
}
bool Ship::IsHit(Coordinates target) {
  int offset = bow_.CalculateOffsetTo(target);
  return hit_locations_offset_.count(offset) != 0;
}
void Ship::Repair() {
  hit_locations_offset_.clear();
}
