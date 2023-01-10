#include "Submarine.h"

bool Submarine::MoveShip(Coordinates target) {
  return false;
}
std::map<Coordinates, OccupationType> Submarine::ScanSurroundings(Player &opponent, Coordinates current_position) {

  std::vector<std::pair<int, int>> offsets = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
  std::map<Coordinates, OccupationType> surroundings;

  for (int i = 0; i < 3; ++i) {
	for (int j = 0; j < 3; ++j) {

	  if (Coordinates::IsValid(current_position.GetRow() + i, current_position.GetRow() + i)) {

		Coordinates a = {current_position.GetRow() + i, current_position.GetRow() + i};
		surroundings.emplace(a, opponent.InquireState(a));
	  }
	  if (Coordinates::IsValid(current_position.GetRow() - i, current_position.GetRow() - i)) {

		Coordinates b = {current_position.GetRow() - i, current_position.GetCol() - j};

		surroundings.emplace(b, opponent.InquireState(b));
	  }
	}
  }

  return surroundings;
}
