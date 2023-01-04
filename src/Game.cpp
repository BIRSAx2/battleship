#include "Game.h"
#include "Battleship.h"
#include "Submarine.h"
#include "SupportShip.h"
#include <chrono>
#include <iostream>
#include <thread>
const Player &Game::GetPlayerA() const {
  return playerA_;
}
void Game::SetPlayerA(const Player &player_a) {
  playerA_ = player_a;
}
const Player &Game::GetPlayerB() const {
  return playerB_;
}
void Game::SetPlayerB(const Player &player_b) {
  playerB_ = player_b;
}
const GameRecorder &Game::GetGameRecorder() const {
  return game_recorder_;
}
void Game::SetGameRecorder(const GameRecorder &game_recorder) {
  game_recorder_ = game_recorder;
}
Game::Game() {
  playerA_ = Player("Random player A");
  playerA_.PlaceShipsRandomly();
  playerB_ = Player("Random player B");
  playerB_.PlaceShipsRandomly();
}
void Game::HandleAttack(Player &attacker, Player &opponent, Coordinates target) {
  bool attackResult = opponent.HandleAttack(target);
  attacker.GetFiringBoard().ChangeTileType(target, attackResult ? HIT : MISS);
}
void Game::PlaceShipsFromUser(const Player &player) {
}
void Game::PlaceShipsRandomly(Player player) {
  player.PlaceShipsRandomly();
}
void Game::Replay(const GameRecorder &game_recorder) {
}
std::ostream &operator<<(std::ostream &os, const Game &game) {
  os << game.playerA_ << "\n"
	 << game.playerB_;
  return os;
}
void Game::PlayRandomGame() {

  bool playerATurn = false;
  int rounds = 0;

  while (!playerA_.HasLost() || !playerB_.HasLost()) {
	std::cout << rounds << " "
			  << "Turno di : " << (playerATurn ? playerA_.GetName() : playerB_.GetName()) << std::endl;

	Player &current_player = playerATurn ? playerA_ : playerB_;
	auto move = current_player.GetRandomMove();

	if (playerATurn) {
	  PlayMove(playerA_, playerB_, move);

	} else {
	  PlayMove(playerB_, playerA_, move);
	}

	playerATurn = !playerATurn;

	std::cout << playerA_ << std::endl;
	std::cout << playerB_ << std::endl;
	if (rounds++ == 200) exit(1);
	std::string c;
	std::cin >> c;
  }
}

void Game::PlayMove(Player &player, Player &opponent, std::pair<Coordinates, Coordinates> move) {
  if (!player.GetShips().count(move.first)) throw std::invalid_argument("There is no ship at the specified location");
  Ship &ship = const_cast<Ship &>(player.GetShips().at(move.first));

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
	  //	  if (!successful) { std::cout << "Cannot move this ship because it's already shot" << std::endl; }
	  break;
	case BATTLESHIP:
	  bool result = Battleship::Shoot(player.GetGameBoard(), opponent.GetFiringBoard(), move.second);
	  if (result) {
		opponent.IncreaseShipHits(move.second);
		player.AddPotentialTargets(move.second);
	  }
	  break;
  }
}
Game::Game(Player playerA, Player playerB) {
}
