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
  void SetSize(int size);
  void SetTiles(std::vector<std::vector<Tile>> tiles);
  static bool IsInsideBoard(int ship_width, Orientation orientation, Coordinates starting_position);
  bool OverlapsOtherShip(int ship_width, Orientation orientation, Coordinates &first_cell);
  bool ReceiveAttack(Coordinates target);
  std::vector<Tile> ScanSurroundings(Coordinates coordinates, int range = 1);
  void MarkTile(Coordinates target, OccupationType newType);
  bool MoveShip(Coordinates origin, Coordinates target, int width, Orientation orientation);
  friend std::ostream &operator<<(std::ostream &os, GameBoard board); //DEBUG Only
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
