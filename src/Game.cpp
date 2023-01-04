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
void Game::PlaceShipsFromUser(Player player) {
}
void Game::PlaceShipsRandomly(Player player) {
  player.PlaceShipsRandomly();
}
void Game::PlayRound() {
}
void Game::PlayToEnd() {
}
void Game::Replay(GameRecorder game_recorder) {
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
	auto move = GenerateRandomMove(playerATurn ? playerA_ : playerB_);

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

std::pair<Coordinates, Coordinates> Game::GenerateRandomMove(Player player) {

  // TODO: find a better way to generate moves: take a look at https://www.datagenetics.com/blog/december32011/
  std::vector<Coordinates> keys;
  for (const auto &pair : player.GetShips()) {
	keys.emplace_back(pair.first);
  }
  Coordinates current;
  Ship ship;
  do {
	current = keys.at(random_int_in_range(0, keys.size() - 1));
	ship = const_cast<Ship &>(player.GetShips().at(current));

  } while (ship.GetOccupationType() != BATTLESHIP);
  Coordinates target;

  // TODO: Ugly change this

  // TODO: Split the logic to handle shooting a target and moving a ship
  do {
	target = {random_int_in_range(0, player.GetGameBoard().GetSize() - 1), random_int_in_range(0, player.GetGameBoard().GetSize() - 1)};

	if (ship.GetOccupationType() == BATTLESHIP) break;
	if (ship.GetOrientation() == HORIZONTAL) {
	  if (!Coordinates(target.GetRow(), target.GetCol() + ship.GetWidth()).IsInBounds(0, 12)) continue;
	  else
		break;
	} else {
	  if (!Coordinates(target.GetRow() + ship.GetWidth(), target.GetCol()).IsInBounds(0, 12)) continue;
	  else
		break;
	}
  } while (true);
  return std::make_pair(current, target);
}
void Game::PlayMove(Player &player, Player &opponent, std::pair<Coordinates, Coordinates> move) {
  if (!player.GetShips().count(move.first)) throw std::invalid_argument("There is no ship at the specified location");
  Ship ship = player.GetShips().at(move.first);
  std::cout << ship.GetOccupationType() << std::endl;

  switch (ship.GetOccupationType()) {

	case EMPTY:
	  throw std::invalid_argument("There is not Ship at the specified location");
	case HIT:
	case MISS:
	case SUBMARINE:
	case SUPPORT_BATTLESHIP:
	  player.MoveShip(move.first, move.second, ship);
	  break;
	case BATTLESHIP:
	  Battleship::Shoot(player.GetFiringBoard(), opponent.GetGameBoard(), move.second);
	  break;
  }
}
Game::Game(Player playerA, Player playerB) {
}
