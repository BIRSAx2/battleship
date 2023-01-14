#include "SupportShip.h"
#include <iostream>

std::set<Coordinates> SupportShip::GetProtectedCoordinates(Coordinates current_position) {
  // The protected Coordinates are the ones in a 3x3 square with current_position as center.
  // For performance reasons we use a pre-define vector of offsets.
  std::vector<std::pair<int, int>> offsets = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
  std::set<Coordinates> adjacent_coordinates;
  for (auto offset : offsets) {
	std::pair<int, int> generated = {current_position.GetRow() + offset.first, current_position.GetCol() + offset.second};
	if (Coordinates::IsValid(generated))
	  adjacent_coordinates.insert({generated.first, generated.second});
  }
  return adjacent_coordinates;
}

// TODO: Handle the repair ships nearby method.