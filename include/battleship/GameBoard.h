#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_

#include <ostream>
#include <vector>

#include "Coordinates.h"
#include "OccupationType.h"
#include "Ship.h"
#include "Tile.h"
class GameBoard {
 protected:
  std::vector<std::vector<Tile>> tiles_;
  int size_;

 public:
  static const int DEFAULT_BOARD_SIZE = 12;
  GameBoard();
  explicit GameBoard(int size);
  std::vector<std::vector<Tile>> &GetTiles();
  int GetSize() const;
  static bool IsInsideBoard(Coordinates bow, Coordinates stern);
  static bool IsInsideBoard(Coordinates point);
  bool OverlapsOtherShip(Coordinates bow, Coordinates stern);
  std::vector<Tile> ScanSurroundings(Coordinates coordinates, int range = 1);
  void MarkTile(Coordinates target, OccupationType newType);
  bool MoveShip(Coordinates current_bow, Coordinates current_stern, Coordinates bow, Coordinates stern);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
