#include "SupportShip.h"
void SupportShip::MoveTo(GameBoard board, Coordinates origin, Coordinates destination) {
}
std::vector<Tile> SupportShip::GetProctectedTiles(GameBoard board, Coordinates currentPosition) {
  return std::vector<Tile>();
}
SupportShip::SupportShip() : Ship("S", DEFAULT_SIZE, SUPPORT_BATTLESHIP) {
}
SupportShip::SupportShip(Orientation orientation) : Ship("S", DEFAULT_SIZE, SUPPORT_BATTLESHIP) {
  orientation_ = orientation;
}
