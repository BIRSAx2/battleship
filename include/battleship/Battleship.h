#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_

#include "GameBoard.h"
#include "Ship.h"
#include "Utility.h"

class Battleship : public Ship {
 public:
  static const int DEFAULT_SIZE = 5;

  /// Create una Ship di tipo Battleship a partire da prua e poppa. Se la distanza tra prua e poppa non corrisponde alla dimensione della nave lancia un std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  Battleship(Coordinates bow, Coordinates stern);
  Battleship() : Ship('C', DEFAULT_SIZE, 127) {
	ship_type_ = BATTLESHIP;
  }
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_