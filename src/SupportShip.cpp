#include "SupportShip.h"
void SupportShip::MoveTo(GameBoard board, Coordinates origin, Coordinates destination) {
}
std::vector<Tile> SupportShip::GetProctectedTiles(GameBoard board, Coordinates currentPosition) {
  return std::vector<Tile>();
}
SupportShip::SupportShip() : Ship("S", 3) {
}
