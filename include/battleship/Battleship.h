#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_

#include "GameBoard.h"
#include "Ship.h"
#include "Utility.h"
#include <string>

class Battleship : public Ship {
 public:
  static const int DEFAULT_SIZE = 5;

  /// Creates a Ship of type BATTLESHIP starting from the bow and stern. If the bow to stern distance does not match the vessel size, throw a std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow The bow of the ship
  /// \param stern The stern of the ship
  Battleship(Coordinates bow, Coordinates stern);
  Battleship() : Ship('C', DEFAULT_SIZE, 127) {
	ship_type_ = BATTLESHIP;
  }
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_