#include "Player.h"

#include <utility>
const std::string &Player::GetName() const {
  return name_;
}
void Player::SetName(const std::string &name) {
  name_ = name;
}
const GameBoard &Player::GetGameBoard() const {
  return game_board_;
}
void Player::SetGameBoard(const GameBoard &game_board) {
  game_board_ = game_board;
}
const FiringBoard &Player::GetFiringBoard() const {
  return firing_board_;
}
void Player::SetFiringBoard(const FiringBoard &firing_board) {
  firing_board_ = firing_board;
}
const std::map<Coordinates, Ship> &Player::GetShips() const {
  return ships_;
}
void Player::SetShips(const std::map<Coordinates, Ship> &ships) {
  ships_ = ships;
}
bool Player::operator==(const Player &rhs) const {
  return name_ == rhs.name_;
}
bool Player::operator!=(const Player &rhs) const {
  return !(rhs == *this);
}
Player::Player(std::string name) : name_(std::move(name)) {
  game_board_ = GameBoard();
  firing_board_ = FiringBoard();
}
bool Player::HasLost() {
  return false;
}
void Player::PlaceShips(std::map<Coordinates, Ship> ships) {
}
void Player::PlaceShip(Ship ship, Coordinates coordinates) {
}
std::string Player::ToString() {
  return std::string();
}
std::ostream &operator<<(std::ostream &os, const Player &player) {
  os << "Giocatore: " << player.name_
	 << "\nGriglia di difesa:\n"
	 << player.game_board_
	 << "\nGriglia di attacco:\n"
	 << player.firing_board_;
  return os;
}
Player::Player() {
}
void Player::PlaceShipsRandomly(std::map<Ship, int> number_of_ships) {


}
