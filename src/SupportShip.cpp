// Antonio Tangaro 2043429

#include "SupportBattleship.h"

// Constructor
SupportBattleship::SupportBattleship(Orientation orientation) : Ship("Support Battleship", 3, 3, orientation) {}

// Move the support battleship to a destination
void SupportBattleship::MoveTo(GameBoard board, Coordinates origin, Coordinates destination) {
  // Check if the destination is a valid square on the board
  if (board.IsValidSquare(destination)) {
    // Check if the destination square is occupied
    if (!board.IsOccupied(destination)) {
      // Move the support battleship to the destination
      board.MoveUnit(origin, destination);
    }
  }
}

// Get the tiles protected by the support battleship
std::vector<Coordinates> SupportBattleship::GetProtectedTiles(GameBoard board, Coordinates currentPosition) {
  std::vector<Coordinates> protectedTiles;

  // Iterate through the 3x3 area around the support battleship
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      Coordinates tile(currentPosition.GetX() + x, currentPosition.GetY() + y);
      // Check if the tile is within the board boundaries
      if (board.IsValidSquare(tile)) {
        protectedTiles.push_back(tile);
      }
    }
  }

  return protectedTiles;
}
