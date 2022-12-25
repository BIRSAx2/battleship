// Antonio Tangaro 2043429

#include "Submarine.h"

// Constructor
Submarine::Submarine(Orientation orientation) : Ship("Submarine", 1, 1, orientation) {}

// Move the submarine to a destination
void Submarine::MoveTo(GameBoard board, Coordinates origin, Coordinates destination) {
  // Check if the destination is a valid square on the board
  if (board.IsValidSquare(destination)) {
    // Check if the destination square is occupied
    if (!board.IsOccupied(destination)) {
      // Move the submarine to the destination
      board.MoveUnit(origin, destination);
    }
  }
}

// Scan the surroundings for opposing units
// Scan the surroundings for opposing units
std::vector<Coordinates> Submarine::ScanSurroundings(Coordinates currentPosition, GameBoard opponentBoard) {
  std::vector<Coordinates> surroundingSquares;

  // Check the squares in a 5x5 area around the submarine
  for (int x = currentPosition.x - 2; x <= currentPosition.x + 2; x++) {
    for (int y = currentPosition.y - 2; y <= currentPosition.y + 2; y++) {
      Coordinates square{x, y};
      if (opponentBoard.IsValidSquare(square) && opponentBoard.IsOccupied(square)) {
        // Add the square to the list of surrounding squares
        surroundingSquares.push_back(square);
      }
    }
  }

  return surroundingSquares;
}

