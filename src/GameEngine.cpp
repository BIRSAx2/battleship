#include "GameEngine.h"
#include "Utility.h"

Coordinates GameEngine::GetNextMove(OccupationType occupation_type) {
  if (occupation_type == BATTLESHIP) return GetNextTarget();
  return GetRandomTarget();
}

GameEngine::GameEngine(GameBoard &game_board) : game_board_(game_board) {}

void GameEngine::AddTargets(const std::vector<Coordinates> &new_targets) {
  for (auto target : new_targets) {
	// TODO: Add check if the target is already present, but we can move ships so this might not be necessary
	if (std::find(targets_.begin(), targets_.end(), target) != targets_.end()) continue;
	targets_.emplace_back(target);
  }
}
Coordinates GameEngine::GetRandomShipPlacement() {
  return Coordinates();
}

Coordinates GameEngine::GetRandomTarget() {
  return {random_int_in_range(0, game_board_.GetSize() - 1), random_int_in_range(0, game_board_.GetSize() - 1)};
}
Coordinates GameEngine::GetNextTarget() {

  if (targets_.empty()) return GetRandomTarget();

  Coordinates target = targets_.at(targets_.size() - 1);
  targets_.pop_back();
  return target;
}
