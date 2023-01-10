#include "SupportShip.h"
#include <iostream>
bool SupportShip::MoveShip(Coordinates target) {
  return false;
}

// TODO: Handle the fact that a supportship cannot protect itself.
// Idea: There no need to keep track of which support ship protect which coordinates. Simply after generating the coordinates, before adding them to the protected coordinates, remove the one's that are occupied by the current ship.
std::set<Coordinates> SupportShip::GetProtectedCoordinates(Coordinates current_position) {
  // The protected Coordinates are the ones in a 3x3 square with current_position as center.
  // For performance reasons we use a pre-define vector of offsets.
  std::vector<std::pair<int, int>> offsets = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
  std::set<Coordinates> adjacent_coordinates;
  for (auto offset : offsets) {
	if (Coordinates::IsValid(current_position.GetRow() + offset.first, current_position.GetCol() + offset.second))
	  adjacent_coordinates.insert({current_position.GetRow() + offset.first, current_position.GetCol() + offset.second});
  }
  return adjacent_coordinates;
}
