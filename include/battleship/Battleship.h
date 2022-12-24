#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_

#include "Coordinates.h"
#include "FiringBoard.h"
#include "GameBoard.h"
class Battleship : public Ship {
 public:
  static void Shoot(FiringBoard, GameBoard opponentBoard, Coordinates target);
  Battleship();
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
