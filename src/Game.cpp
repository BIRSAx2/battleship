#include "Game.h"
#include "Battleship.h"
#include "Submarine.h"
#include "SupportShip.h"
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
  playerB_ = Player("Random player B");


}
void Game::PlaceShipsFromUser(Player player) {
}
void Game::PlaceShipsRandomly(Player player) {
}
void Game::PlayRound() {
}
void Game::PlayToEnd() {
}
void Game::Replay(GameRecorder game_recorder) {
}
std::ostream &operator<<(std::ostream &os, const Game &game) {
  os << "playerA: " << game.playerA_ << " playerB: " << game.playerB_;
  return os;
}
