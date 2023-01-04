#include "Battleship.h"
bool Battleship::Shoot(GameBoard &attacker, FiringBoard &opponent, Coordinates target) {
  std::cout << "Shooting at target: " << target << std::endl;
  // TODO: Handle protected areas by support ship
  bool result = opponent.ReceiveAttack(target);
  attacker.MarkTile(target, result ? HIT : MISS);
  return result;
}
Battleship::Battleship() : Ship("C", DEFAULT_SIZE, BATTLESHIP) {}
Battleship::Battleship(Orientation orientation) : Ship("C", DEFAULT_SIZE, BATTLESHIP) {
  orientation_ = orientation;
}
