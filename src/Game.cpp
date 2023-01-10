#include "Game.h"
#include "Battleship.h"
Game::Game(GameMode mode) : player_a_(Player("Bot 1")), player_b_(Player("Bot 2")), game_mode_(mode) {

  if (mode == COMPUTER_VS_HUMAN) {
	player_a_ = Player("Bot");
	player_b_ = Player("Human");
  }
}
void Game::PlayGame() {
  if (game_mode_ == COMPUTER_VS_COMPUTER) PlayComputerVsComputerGame();
  else
	PlayComputerVsHumanGame();
}

void Game::PlayComputerVsComputerGame() {
  player_a_.PlaceShipsRandomly();
  player_b_.PlaceShipsRandomly();
  std::cout << player_a_ << std::endl;
  std::cout << player_b_ << std::endl;

  std::pair<Coordinates, Coordinates> move = player_a_.GenerateRandomMove();

  PlayMove(player_a_, player_b_, move);

  std::cout << move.first << " " << move.second << std::endl;
}
void Game::PlayComputerVsHumanGame() {
  std::cout << player_a_ << std::endl;
  std::cout << player_b_ << std::endl;
}

bool Game::PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move) {

  if (attacker.GetShipAt(move.first) == nullptr) throw std::invalid_argument(std::string("No ship at the specified location"));

  std::shared_ptr<Ship> ship = attacker.GetShipAt(move.first);

  if (ship->GetShipType() == BATTLESHIP) {
	// handle attack

  } else {
	// move ship
  }

  return false;
}