#include "Ship.h"

#include <utility>
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