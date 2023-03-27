#include "Battleship.h"

Battleship::Battleship(Coordinates bow, Coordinates stern) : Ship('C', DEFAULT_SIZE, 127) {
  if (bow.CalculateOffsetTo(stern) + 1 != DEFAULT_SIZE)
	throw std::invalid_argument("The units between bow and stern must contain exactly the ship. Ship width: "
								+ std::to_string(DEFAULT_SIZE) + ", space between bow and stern: "
								+ std::to_string(bow.CalculateOffsetTo(stern) + 1));
  ship_type_ = BATTLESHIP;
  bow_ = bow;
  stern_ = stern;
}
