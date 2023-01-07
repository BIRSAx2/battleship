#include "Battleship.h"

// Questo metodo si occupa solo di segnare il risultato dell'attacco sulle griglie di gioco
bool Battleship::Shoot(FiringBoard &attacker, GameBoard &opponent, Coordinates target) {
  if (!target.IsInBounds(0, 12)) throw std::invalid_argument("Target outside the board's bounds");
  std::cout << "Shooting at target: " << target << std::endl;
  // TODO: Handle protected areas by support ship
  bool result = opponent.ReceiveAttack(target);

  Tile &target_tile = opponent.GetTiles().at(target.GetRow()).at(target.GetCol());

  if (target_tile.IsOccupied() || target_tile.GetOccupationType() == HIT) {
	result = true;
	target_tile.SetOccupationType(HIT);
	opponent.MarkTile(target, HIT);
  }
  attacker.MarkTile(target, result ? HIT : MISS);
  return result;
}
Battleship::Battleship() : Ship("C", DEFAULT_SIZE, BATTLESHIP) {}
Battleship::Battleship(Orientation orientation) : Ship("C", DEFAULT_SIZE, BATTLESHIP) {
  orientation_ = orientation;
}
