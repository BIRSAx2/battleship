#include "SupportShip.h"
#include <iostream>
bool SupportShip::MoveShip(Coordinates target) {
  return false;
}

//std::string SupportShip::ToString(Coordinates location) {
//  if (std::find(hit_locations_offset_.begin(), hit_locations_offset_.end(), bow_.CalculateOffsetTo(location)) != hit_locations_offset_.end()) return ColourText256(hit_icon_, 1);
//  return ColourText256(icon_, 106);
//}
std::vector<Coordinates> SupportShip::GetProtectedCoordinates() {
  return std::vector<Coordinates>();
}
