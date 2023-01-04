#include <iostream>

#include "Game.h"

int main() {

  Game game = Game();
//  game.PlayRandomGame();

  std::vector<Coordinates> coordinate = Coordinates::GetAdjacentStarCoordinates({0,0});
  return 0;
}
