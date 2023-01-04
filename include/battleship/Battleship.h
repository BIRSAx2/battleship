#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_

#include "Coordinates.h"
#include "FiringBoard.h"
#include "GameBoard.h"
#include "Player.h"
class Battleship : public Ship {
 public:
  static const int DEFAULT_SIZE = 5;
  Battleship();
  explicit Battleship(Orientation orientation);
  //
  static bool Shoot(GameBoard &attacker, FiringBoard &opponent, Coordinates target);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
