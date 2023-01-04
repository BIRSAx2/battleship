#include "Battleship.h"
void Battleship::Shoot(FiringBoard &firing_board, GameBoard &opponentBoard, Coordinates target) {
  std::cout << "Shooting at target: " << target << std::endl;
  // TODO: Handle protected areas by support ship
  bool result = opponentBoard.ReceiveAttack(target);
  firing_board.MarkTile(target, result ? HIT : MISS);
}
Battleship::Battleship() : Ship("C", DEFAULT_SIZE, BATTLESHIP) {}
Battleship::Battleship(Orientation orientation) : Ship("C", DEFAULT_SIZE, BATTLESHIP) {
  orientation_ = orientation;
}
