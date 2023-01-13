#include "Battleship.h"

Battleship::Battleship(Coordinates bow, Coordinates stern) : Ship('C', DEFAULT_SIZE, 127) {
  if (bow.CalculateOffsetTo(stern) + 1 != DEFAULT_SIZE) throw std::invalid_argument("Invalid bow and stern");
  ship_type_ = BATTLESHIP;
  bow_ = bow;
  stern_ = stern;
}
