// Author: Antonio Tangaro

#include "SupportShip.h"
#include <iostream>

void SupportShip::RepairNearbyShips(Player &player, Coordinates current_position) {
  std::vector<std::pair<int, int>> offsets = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
  for (auto offset : offsets) {
	std::pair<int, int> generated = {current_position.GetRow() + offset.first, current_position.GetCol() + offset.second};
	if (Coordinates::IsValid(generated)) {
	  player.RepairShipAt({generated.first, generated.second});
	}
  }
}