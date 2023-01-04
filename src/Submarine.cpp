#include "Submarine.h"
void Submarine::MoveTo(GameBoard board, Coordinates origin, Coordinates destination) {
//  board.MoveShip(origin, destination);
}
std::vector<Tile> Submarine::ScanSurroundings(Coordinates currentPosition, GameBoard opponentBoard) {

  return opponentBoard.ScanSurroundings(currentPosition);
}
Submarine::Submarine() : Ship("E", DEFAULT_SIZE, SUBMARINE) {
}
Submarine::Submarine(Orientation orientation) : Ship("E", DEFAULT_SIZE, SUBMARINE) {
  orientation_ = orientation;
}
