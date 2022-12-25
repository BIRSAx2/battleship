// Antonio Tangaro 2043429

#include "BattleShip.h"

// Constructor
BattleShip::BattleShip(Orientation orientation) : Ship("BattleShip", 5, 5, orientation) {}

// Fire on a target
void BattleShip::Shoot(FiringBoard firingBoard, GameBoard opponentBoard, Coordinates target) {
  // Check if the target is a valid square on the opponent's board
  if (opponentBoard.IsValidSquare(target)) {
    // Check if the target square is occupied
    if (opponentBoard.IsOccupied(target)) {
      // Hit the target
      opponentBoard.Hit(target);

      // Check if the unit at the target square is sunk
      Ship* targetUnit = opponentBoard.GetUnitAt(target);
      if (targetUnit->IsSunk()) {
        // Sink the unit
        opponentBoard.Sink(target);
      }
    } else {
      // Miss the target
      opponentBoard.Miss(target);
    }

    // Update the firing board with the result of the shot
    firingBoard.Update(target, opponentBoard.GetSquareStatus(target));
  }
}
