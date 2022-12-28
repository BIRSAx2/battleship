#include <iostream>

#include "Battleship.h"
#include "FiringBoard.h"
#include "Game.h"
#include "GameBoard.h"
#include "Player.h"

#include "Utility.h"

void print_8_colours() {
  for (int i = 0; i < 108; i++) {
	if (i % 9 == 0 && i != 0)
	  std::cout << std::endl;
	printf("\033[%dm %3d\033[m", i, i);
  }
}
void print_256_colours_txt() {
  for (int i = 0; i < 256; i++) {
	if (i % 16 == 0 && i != 0)
	  std::cout << std::endl;
	printf("\033[38;5;%dm %3d\033[m", i, i);
  }
}
void print_256_colours_background() {
  for (int i = 0; i < 256; i++) {
	if (i % 16 == 0 && i != 0)
	  std::cout << std::endl;
	printf("\033[48;5;%dm %3d\033[m", i, i);
  }
}
int main() {

  Game game = Game();
  game.PlayRandomGame();
  std::cout << game << std::endl;
  return 0;
}
