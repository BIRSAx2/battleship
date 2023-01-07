#include <iostream>

#include "Game.h"

int main() {

  GameBoard game_board = GameBoard();

  SupportShip support_ship = SupportShip(HORIZONTAL);

  game_board.PlaceShip(support_ship, Coordinates::ParseCoordinate("D6"), Coordinates::ParseCoordinate("D9"));

  game_board.ReceiveAttack(Coordinates::ParseCoordinate("D6"));
  game_board.ReceiveAttack(Coordinates::ParseCoordinate("D7"));
  game_board.ReceiveAttack(Coordinates::ParseCoordinate("D8"));

  std::cout << game_board << std::endl;
  game_board.MoveShip(Coordinates::ParseCoordinate("D6"), Coordinates::ParseCoordinate("c6"));

  std::cout << game_board << std::endl;
  // Ship placement
  // Ship movement
  // Ship actions
  return 1;
}
