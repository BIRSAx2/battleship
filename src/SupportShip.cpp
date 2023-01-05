#include "SupportShip.h"
//void SupportShip::MoveTo(GameBoard board, Coordinates origin, Coordinates destination) {
//}
SupportShip::SupportShip() : Ship(DEFAULT_SIZE, UNSET) {
}
SupportShip::SupportShip(Orientation orientation) {
  orientation_ = orientation;
}
