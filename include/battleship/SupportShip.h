#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_

#include "Coordinates.h"
#include "GameBoard.h"
#include "Tile.h"
#include <vector>

class SupportShip : public Ship {
 public:
  SupportShip();
  void MoveTo(GameBoard board, Coordinates origin, Coordinates destination);
  std::vector<Tile> GetProctectedTiles(GameBoard board, Coordinates currentPosition);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
