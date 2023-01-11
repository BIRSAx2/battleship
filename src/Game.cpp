#include "Game.h"
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

void Game::PlayComputerVsComputerGame() {}
void Game::PlayComputerVsHumanGame() {
  std::cout << player_a_ << std::endl;
  std::cout << player_b_ << std::endl;
}