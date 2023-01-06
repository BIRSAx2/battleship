#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_

#include <vector>

#include "Coordinates.h"
#include "GameBoard.h"
#include "Ship.h"
#include "Tile.h"

class Submarine : public Ship {
 public:
  static const int DEFAULT_SIZE = 1;
  Submarine();
  Submarine(Orientation orientation);
  static void MoveTo(GameBoard board, Coordinates origin, Coordinates destination);
  static std::vector<Tile> ScanSurroundings(Coordinates currentPosition, GameBoard opponentBoard);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
