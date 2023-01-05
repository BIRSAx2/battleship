#include "Player.h"

const std::string &Player::GetName() const {
  return name_;
}

GameBoard &Player::GetGameBoard() {
  return game_board_;
}

FiringBoard &Player::GetFiringBoard() {
  return firing_board_;
}

std::map<Coordinates, Ship> &Player::GetShips() {
  return ships_;
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
  return std::all_of(ships_.begin(), ships_.end(), [](const std::pair<Coordinates, Ship> &pair) { return pair.second.IsSunk(); });
}

std::string Player::ToString() {

  std::stringstream stringstream;

  stringstream << "\t\t\t\t" << colour_text_256(name_, 34) << '\n';
  std::vector<std::vector<Tile>> game_board = game_board_.GetTiles();
  std::vector<std::vector<Tile>> firing_board = firing_board_.GetTiles();

  std::string horizontal_legend = "1  2  3  4  5  6  7  8  9  10 11 12";
  std::string vertical_legend[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N"};

  int legend = 0;
  stringstream << "\t" << colour_text_256("Griglia di difesa", 202) << "\t\t\t" << colour_text_256("Griglia di attacco", 202) << '\n';
  stringstream << "     " << colour_text_256(horizontal_legend, 8) << "    " << colour_text_256(horizontal_legend, 8) << "\n";

  for (int i = 0; i < game_board.size(); ++i) {
	// Looping throw rows
	stringstream << std::setw(2) << (legend) << " " << colour_text_256(vertical_legend[legend], 8) << " ";
	// Game Board
	for (auto tile : game_board.at(i)) {
	  stringstream << tile << "  ";
	}
	stringstream << " " << colour_text_256(vertical_legend[legend], 8) << " ";
	// Firing Board
	for (auto tile : firing_board.at(i)) {
	  stringstream << tile << "  ";
	}
	stringstream << colour_text_256(vertical_legend[legend], 8) << "\n";
	legend++;
  }
  stringstream << "   " << colour_text_256(horizontal_legend, 8) << "      " << colour_text_256(horizontal_legend, 8) << "\n";
  return stringstream.str();
}

std::ostream &operator<<(std::ostream &os, Player &player) {
  return os << player.ToString();
}

Player::Player() : name_("unknown player") {
}
