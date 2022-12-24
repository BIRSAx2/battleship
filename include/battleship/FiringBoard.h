#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_

#include "GameBoard.h"
#include "OccupationType.h"
#include "Tile.h"
#include <ostream>
#include <vector>
class FiringBoard : public GameBoard {
 public:
  FiringBoard();
  explicit FiringBoard(int size);
  std::vector<Tile> GetOpenRandomTiles();
//  friend std::ostream &operator<<(std::ostream &os, const FiringBoard &board);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
