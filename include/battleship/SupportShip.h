// Antonio Tangaro 2043429

#ifndef SUPPORTBATTLESHIP_H
#define SUPPORTBATTLESHIP_H

#include "Ship.h"
#include "GameBoard.h"
#include "Coordinates.h"
#include <vector>

class SupportBattleship : public Ship {
 public:
  // Constructor
  SupportBattleship(Orientation orientation);

  // Move the support battleship to a destination
  void MoveTo(GameBoard board, Coordinates origin, Coordinates destination);

  // Get the tiles protected by the support battleship
  std::vector<Coordinates> GetProtectedTiles(GameBoard board, Coordinates currentPosition);
};

#endif  // SUPPORTBATTLESHIP_H
