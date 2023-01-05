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
  void ClearSuccessfulShots();
  void ClearUnsuccessfulShots();
  void ClearSonarSightings();
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
