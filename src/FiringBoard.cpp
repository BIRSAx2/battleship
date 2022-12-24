#include "FiringBoard.h"
#include <algorithm>
std::vector<Tile> FiringBoard::GetOpenRandomTiles() {
  std::vector<Tile> openTiles;

  for (auto row : tiles_) {
	std::copy_if(row.begin(), row.end(), std::back_inserter(openTiles), [](Tile tile) { return tile.IsRandomlyAvailable(); });
  }

  return openTiles;
}
//std::ostream &operator<<(std::ostream &os, const FiringBoard &board) {
//
//  return os ;
//}
FiringBoard::FiringBoard() : GameBoard(){};
FiringBoard::FiringBoard(int size) : GameBoard(size){};
