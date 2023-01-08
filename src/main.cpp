#include "Battleship.h"
#include "Game.h"
#include "GameBoard.h"
#include "SupportShip.h"
#include <iostream>
int main() {
  Game game = Game(COMPUTER_VS_HUMAN);
  game.PlayGame();
  return 0;
}
