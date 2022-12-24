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
  std::vector<std::vector<Tile>> GetTiles();
  void SetTiles(std::vector<std::vector<Tile>> tiles);
  bool IsInsideBoard(Ship ship, Coordinates startingPositions);
  bool OverlapsShip(Ship ship, Coordinates startingPositions);
  bool ReceiveAttack(Coordinates target);
  std::vector<Tile> ScanSurroundings(Coordinates coordinates, int range = 1);
  void ChangeTileType(Coordinates target, OccupationType type);
  void MarkTile(Coordinates target, OccupationType newType);
  friend std::ostream &operator<<(std::ostream &os, const GameBoard &board);
  bool MoveShip(Coordinates origin, Coordinates target);
  std::vector<std::vector<Tile>> GetTiles() const;
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
