#include "Game.h"
#include "Battleship.h"
#include "Submarine.h"
#include "SupportShip.h"
#include <chrono>
#include <iostream>
#include <thread>
const Player &Game::GetPlayerA() const {
  return player_a_;
}
void Game::SetPlayerA(const Player &player_a) {
  player_a_ = player_a;
}
const Player &Game::GetPlayerB() const {
  return player_b_;
}
void Game::SetPlayerB(const Player &player_b) {
  player_b_ = player_b;
}
const GameRecorder &Game::GetGameRecorder() const {
  return game_recorder_;
}
void Game::SetGameRecorder(const GameRecorder &game_recorder) {
  game_recorder_ = game_recorder;
}
Game::Game() {
  player_a_ = Player("Random player A");
  player_a_.PlaceShipsRandomly();
  player_b_ = Player("Random player B");
  player_b_.PlaceShipsRandomly();
}
bool Game::HandleAttack(Player &attacker, Player &opponent, Coordinates target) {
  bool attackResult = Battleship::Shoot(attacker.GetFiringBoard(), opponent.GetGameBoard(), target);
  // In caso di attacco andato a buon fine, incremento i colpi ricevuti dalla nave avversaria

  if (attackResult) {
	opponent.IncreaseShipHits(target);
	attacker.AddPotentialTargets(target);
  }
  std::cout << "Attack result: " << attackResult << std::endl;
  return attackResult;
}
void Game::PlaceShipsFromUser(const Player &player) {
}
void Game::PlaceShipsRandomly(Player& player) {
  player.PlaceShipsRandomly();
}
void Game::Replay(const GameRecorder &game_recorder) {
}
std::ostream &operator<<(std::ostream &os, Game &game) {
  os << game.player_a_ << "\n"
	 << game.player_b_;
  return os;
}
void Game::PlayRandomGame() {

  bool playerATurn = false;
  int rounds = 0;

  std::cout << player_a_ << std::endl;
  std::cout << player_b_ << std::endl;

  while (!player_a_.HasLost() || !player_b_.HasLost()) {
	std::cout << rounds << " "
			  << "Turno di : " << (playerATurn ? player_a_.GetName() : player_b_.GetName()) << std::endl;

	Player &current_player = playerATurn ? player_a_ : player_b_;
	auto move = current_player.GetRandomMove();
	std::cout << move.first << " " << move.second << std::endl;
	if (playerATurn) {
	  std::cout << "Before" << std::endl;
	  std::cout << player_a_ << std::endl;
	  PlayMove(player_a_, player_b_, move);
	  std::cout << "After" << std::endl;
	  std::cout << player_a_ << std::endl;

	} else {
	  std::cout << "Before" << std::endl;
	  std::cout << player_b_ << std::endl;

	  PlayMove(player_b_, player_a_, move);
	  std::cout << "After" << std::endl;
	  std::cout << player_b_ << std::endl;
	}

	std::cout << "------------------------------------------------------------------" << std::endl;
	playerATurn = !playerATurn;

	if (rounds++ == 200) exit(1);
	std::string c;
	std::cin >> c;
  }
}

void Game::PlayMove(Player &player, Player &opponent, std::pair<Coordinates, Coordinates> move) {
  if (!player.GetShips().count(move.first)) throw std::invalid_argument("There is no ship at the specified location");
  Ship &ship = const_cast<Ship &>(player.GetShips().at(move.first));
  std::cout << ship << std::endl;
  switch (ship.GetOccupationType()) {

	case EMPTY:
	  throw std::invalid_argument("There is not Ship at the specified location");
	case HIT:
	case MISS:
	  return;
	case SUBMARINE:
	case SUPPORT_SHIP:
	  if (player.GetShips().at(move.first).GetHits() != 0) throw std::invalid_argument("Cannot move ship because it's already shot");
	  player.MoveShip(move.first, move.second, ship);
	  break;
	case BATTLESHIP:
	  HandleAttack(player, opponent, move.second);
	  break;
  }
}
Game::Game(Player playerA, Player playerB) {
}
