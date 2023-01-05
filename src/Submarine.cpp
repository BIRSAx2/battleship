#include "Submarine.h"
Submarine::Submarine() : Ship(DEFAULT_SIZE, UNSET) {
}
Submarine::Submarine(Orientation orientation) {
  width_ = DEFAULT_SIZE;
  orientation_ = orientation;
}
