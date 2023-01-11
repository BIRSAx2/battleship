#include "Battleship.h"

bool Battleship::ShootAt(GameBoard opponent_board, Coordinates target) {
  return false;
}
Battleship::Battleship(Coordinates bow, Coordinates stern) : Ship('C', 5, 127) {
  if (bow.CalculateOffsetTo(stern) + 1 != 5) throw std::invalid_argument("Invalid bow and stern");
  ship_type_ = BATTLESHIP;
  bow_ = bow;
  stern_ = stern;
}
