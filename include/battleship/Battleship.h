// Antonio Tangaro 2043429

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Ship.h"
#include "FiringBoard.h"
#include "GameBoard.h"
#include "Coordinates.h"

class BattleShip : public Ship {
 public:
  // Constructor
  BattleShip(Orientation orientation);

  // Fire on a target
  void Shoot(FiringBoard firingBoard, GameBoard opponentBoard, Coordinates target);
};

#endif  // BATTLESHIP_H
