#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMEENGINE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMEENGINE_H_

#include "Coordinates.h"
#include "GameBoard.h"
#include "Ship.h"
#include <stack>
#include <vector>

//  A simple implementation of this refined strategy is to create a stack of potential targets.
//  Initially, the computer is in Hunt mode, firing at random. Once a ship has been 'winged' then
//  the computer switches to Target mode. After a hit, the four surrounding grid squares are added
//  to a stack of 'potential' targets (or less than four if the cell was on an edge/corner).
//
//  Cells are only added if they have not already been visited (there is no point in re-visiting a
//  cell if we already know that it is a Hit or Miss).
//
//  Once in Target mode the computer pops off the next potential target off the stack, fires a salvo
//  at this location, acts on this (either adding more potential targets to the stack, or popping
//  the next target location off the stack), until either all ships have been sunk, or there are
//  no more potential targets on the stack, at which point it returns to Hunt mode and starts
//  firing at random again looking for another ship.
class GameEngine {
 private:
  std::vector<Coordinates> targets_{};
  std::vector<Coordinates> visited_;
  GameBoard& game_board_;

 public:
  GameEngine(GameBoard& game_board);
  Coordinates GetNextMove(OccupationType occupation_type);
  void AddTargets(const std::vector<Coordinates> &new_targets);

 private:
  Coordinates GetRandomShipPlacement();
  Coordinates GetNextTarget();
  Coordinates GetRandomTarget();
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEENGINE_H_
