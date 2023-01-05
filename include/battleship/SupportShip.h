#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_

#include "Coordinates.h"
#include "GameBoard.h"
#include "Tile.h"
#include <vector>

class SupportShip : public Ship {
 public:
  static const int DEFAULT_SIZE = 3;
  SupportShip();
  explicit SupportShip(Orientation orientation);
  std::vector<Tile> GetProtectedTiles(GameBoard &board, Coordinates bow);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
