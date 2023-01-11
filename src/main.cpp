#include "Game.h"
int main() {

  Print256ColoursTxt();
  std::cout << std::endl;
  Print256ColoursBackground();
  std::cout << std::endl;
  Game game = Game();
  game.PlayGame();
  return 0;
}
