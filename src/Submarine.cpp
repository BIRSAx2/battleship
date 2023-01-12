#include "Submarine.h"

std::map<Coordinates, OccupationType> Submarine::ScanSurroundings(Player &opponent, Coordinates current_position) {
  std::map<Coordinates, OccupationType> coordinates_with_ships;
  for (int x = current_position.GetRow() - 2; x <= current_position.GetRow() + 2; x++) {
	for (int y = current_position.GetCol() - 2; y <= current_position.GetCol() + 2; y++) {
	  Coordinates coordinates(x, y);
	  OccupationType state = opponent.InquireState(coordinates);
	  if (state == OCCUPIED || state == HIT) {
		coordinates_with_ships[coordinates] = state;
	  }
	}
  }
  return coordinates_with_ships;
}
