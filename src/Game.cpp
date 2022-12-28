#include "Game.h"
#include "Battleship.h"
#include "Submarine.h"
#include "SupportShip.h"
#include <iostream>
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

  while (!playerA_.HasLost() || !playerB_.HasLost()) {
	auto move = GenerateRandomMove(playerA_);

	std::cout << *this << std::endl;

	std::cout << move.first << "->" << move.second << std::endl;
	exit(1);
  }
}

std::pair<Coordinates, Coordinates> Game::GenerateRandomMove(Player player) {

  // TODO: find a better way to generate moves: take a look at https://www.datagenetics.com/blog/december32011/
  std::vector<Coordinates> keys;
  for (const auto &pair : player.GetShips()) {
	keys.emplace_back(pair.first);
  }

  Coordinates current = keys.at(random_int_in_range(0, keys.size()));
  Coordinates target = {random_int_in_range(0, player.GetGameBoard().GetSize()), random_int_in_range(0, player.GetGameBoard().GetSize())};

  std::cout << current << std::endl;

  return std::make_pair(current, target);
}
