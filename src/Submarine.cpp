#include "Submarine.h"

bool Submarine::MoveShip(Coordinates target) {
  return false;
}
std::map<Coordinates, OccupationType> Submarine::ScanSurroundings(Player &opponent, Coordinates current_position) {

  std::vector<std::pair<int, int>> offsets = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};
  std::map<Coordinates, OccupationType> surroundings;

  for (int row = 0; row < 3; ++row) {
	for (int col = 0; col < 3; ++col) {

	  std::pair<int, int> after = {current_position.GetRow() + row, current_position.GetCol() + col};
	  if (Coordinates::IsValid(after)) {
		Coordinates a = Coordinates(after);
		surroundings.emplace(a, opponent.InquireState(a));
	  }

	  std::pair<int, int> before = {current_position.GetRow() - row, current_position.GetCol() - col};

	  if (Coordinates::IsValid(before)) {
		Coordinates b = Coordinates(before);
		surroundings.emplace(b, opponent.InquireState(b));
	  }
	}
  }

  return surroundings;
}
