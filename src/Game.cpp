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

  bool player_a_turn = RandomIntInRange(0, 1);
  for (int i = 0; i < 500; ++i) {
	std::cout << "---------------------------Turn " << i << "---------------------------------" << std::endl;
	Player &current_player = player_a_turn ? player_a_ : player_b_;
	Player &opponent = player_a_turn ? player_b_ : player_a_;
	std::cout << "Current player: " << current_player.GetName() << std::endl;

	std::pair<Coordinates, Coordinates> move = current_player.GenerateRandomMove();
	std::cout << "Playing move: " << move.first.ToUserCoordinates() << "-" << move.second.ToUserCoordinates() << std::endl;
	PlayMove(current_player, opponent, move);
	std::cout << current_player << std::endl;

	player_a_turn = !player_a_turn;
  }
}
void Game::PlayComputerVsHumanGame() {
  std::cout << player_a_ << std::endl;
  std::cout << player_b_ << std::endl;
}

bool Game::PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move) {

  if (attacker.GetShipAt(move.first) == nullptr) throw std::invalid_argument(std::string("No ship at the specified location"));

  std::shared_ptr<Ship> ship = attacker.GetShipAt(move.first);

  if (ship->GetShipType() == BATTLESHIP) {
	std::cout << "Attacking " << std::endl;
	// handle attack
	bool result = opponent.ReceiveAttack(move.second);
	attacker.MarkAttack(move.second, result);
	if (result) attacker.AddNextTargets(move.second);
	return true;
  }
  // move ship
  std::cout << "Moving a ship " << std::endl;

  bool ship_moved = attacker.MoveShip(move.first, move.second);
  if (!ship_moved) {
	std::cout << "Could not move this ship" << std::endl;
	return false;
  };

  return true;
}