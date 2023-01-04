#include "GameEngine.h"
#include "Utility.h"

void GameEngine::AddNearTargets(Coordinates target) {
  std::vector<Coordinates> new_targets = Coordinates::GetAdjacentStarCoordinates(target);

  for (Coordinates item : new_targets) {

	if (std::find(targets_.begin(), targets_.end(), item) != targets_.end()) continue;
	if (std::find(already_shot_.begin(), already_shot_.end(), item) != already_shot_.end()) continue;
	targets_.emplace_back(item);
  }

  for (auto t : targets_) {
	std::cout << t << ' ';
  }
}
std::pair<Coordinates, Orientation> GameEngine::GetRandomShipPlacement(GameBoard game_board, int ship_width) {

  // TODO: Refactor this to use a more deterministic approach, first generate a list of available positions and the choose randomly between it's elements
  Orientation orientation;
  Coordinates coordinates{0, 0};
  Ship ship;
  do {
	coordinates = {random_int_in_range(0, game_board.GetSize()), random_int_in_range(0, game_board.GetSize())};
	orientation = static_cast<Orientation>(random_int_in_range(0, 1));
  } while (!GameBoard::IsInsideBoard(ship_width, orientation, coordinates) || game_board.OverlapsOtherShip(ship_width, orientation, coordinates));
  return std::make_pair(coordinates, orientation);
}

Coordinates GameEngine::GetRandomTarget(int board_size) {

  Coordinates coordinates;
  do {
	coordinates = {random_int_in_range(0, board_size - 1), random_int_in_range(0, board_size - 1)};
  } while (std::find(already_shot_.begin(), already_shot_.end(), coordinates) != already_shot_.end());
  already_shot_.push_back(coordinates);
  return coordinates;
}

Coordinates GameEngine::GetNextTarget(int board_size) {

  std::cout << "Targets size: " << targets_.size() << std::endl;

  std::cout << std::endl;
  if (targets_.empty()) return GetRandomTarget(board_size);

  Coordinates target = targets_.at(0);
  std::remove(targets_.begin(), targets_.end(), target);
  return target;
}

Coordinates GameEngine::GetRandomShip(const std::map<Coordinates, Ship> &ships) {
  std::vector<Coordinates> keys;
  for (const auto &pair : ships) {
	if (pair.second.GetHits() == 0) keys.emplace_back(pair.first);
  }
  Ship ship;

  return keys.at(random_int_in_range(0, (int)keys.size() - 1));
}

std::pair<Coordinates, Coordinates> GameEngine::GetRandomMove(GameBoard &game_board, const std::map<Coordinates, Ship> &ships) {

  // A random move is generated in two steps:
  // First chose a ship randomly between the user's ships
  // If the ship if a battleship then find a target for it
  // Otherwise find a new placement for the ship

  Coordinates origin = GetRandomShip(ships);

  Ship &ship = const_cast<Ship &>(ships.at(origin));
  do {
	origin = GetRandomShip(ships);
	ship = ships.at(origin);
  } while (ship.GetOccupationType() != BATTLESHIP);

  if (ship.GetOccupationType() == BATTLESHIP) return std::make_pair(origin, GetNextTarget());

  Coordinates placement = GetRandomShipPlacement(game_board, ship);
  return std::make_pair(origin, placement);
}

Coordinates GameEngine::GetRandomShipPlacement(GameBoard &game_board, const Ship &ship) {
  Orientation orientation = ship.GetOrientation();
  Coordinates placement{0, 0};
  do {
	placement = {random_int_in_range(0, game_board.GetSize() - ship.GetWidth() / 2), random_int_in_range(0, game_board.GetSize() - ship.GetWidth() / 2)};
  } while (!GameBoard::IsInsideBoard(ship.GetWidth(), orientation, placement) || game_board.OverlapsOtherShip(ship.GetWidth(), orientation, placement));
  return placement;
}
GameEngine::GameEngine() = default;
