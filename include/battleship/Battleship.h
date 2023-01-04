#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_

#include "Coordinates.h"
#include "FiringBoard.h"
#include "GameBoard.h"
class Battleship : public Ship {
 public:
  static const int DEFAULT_SIZE = 5;
  static bool Shoot(FiringBoard &firing_board, GameBoard &opponent_board, Coordinates target);
  Battleship();
  explicit Battleship(Orientation orientation);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
