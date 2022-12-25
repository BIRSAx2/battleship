// Antonio Tangaro 2043429

#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "Ship.h"
#include "GameBoard.h"
#include "Coordinates.h"
#include <vector>

class Submarine : public Ship {
 public:
  // Constructor
  Submarine(Orientation orientation);

  // Move the submarine to a destination
  void MoveTo(GameBoard board, Coordinates origin, Coordinates destination);

  // Scan the surroundings for opposing units
  std::vector<Coordinates> ScanSurroundings(Coordinates currentPosition, GameBoard opponentBoard);
};

#endif  // SUBMARINE_H
