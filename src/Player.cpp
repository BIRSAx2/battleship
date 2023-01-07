#include "Player.h"

const std::string &Player::GetName() const {
  return name_;
}

void Player::SetName(const std::string &name) {
  name_ = name;
}

GameBoard &Player::GetGameBoard() {
  return game_board_;
}

void Player::SetGameBoard(const GameBoard &game_board) {
  game_board_ = game_board;
}

FiringBoard &Player::GetFiringBoard() {
  return firing_board_;
}

void Player::SetFiringBoard(const FiringBoard &firing_board) {
  firing_board_ = firing_board;
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
  game_engine_ = GameEngine();
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

void Player::PlaceShipsRandomly() {

  // Tre Corazzate, dimensione 5
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Orientation> randomPosition = game_engine_.GetRandomShipPlacement(game_board_, Battleship::DEFAULT_SIZE);
	Battleship ship = Battleship(randomPosition.second);
	Coordinates bow;
	Coordinates stern;
	if (randomPosition.second == HORIZONTAL) {
	  bow = randomPosition.first;
	  stern = {bow.GetRow(), bow.GetCol() + ship.GetWidth() - 1};
	} else {
	  bow = randomPosition.first;
	  stern = {bow.GetRow() + ship.GetWidth() - 1, bow.GetCol()};
	}
	game_board_.PlaceShip(ship, bow, stern);
  }
  // Tre Navi di supporto, dimensione 3
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Orientation> randomPosition = game_engine_.GetRandomShipPlacement(game_board_, SupportShip::DEFAULT_SIZE);
	SupportShip support_ship = SupportShip(randomPosition.second);
	Coordinates bow;
	Coordinates stern;
	if (randomPosition.second == HORIZONTAL) {
	  bow = randomPosition.first;
	  stern = {bow.GetRow(), bow.GetCol() + support_ship.GetWidth() - 1};
	} else {
	  bow = randomPosition.first;
	  stern = {bow.GetRow() + support_ship.GetWidth() - 1, bow.GetCol()};
	}
	game_board_.PlaceShip(support_ship, bow, stern);
  }
  // Due Sottomarini di esplorazione, dimensione 1
  for (int i = 0; i < 2; ++i) {
	std::pair<Coordinates, Orientation> randomPosition = game_engine_.GetRandomShipPlacement(game_board_, Submarine::DEFAULT_SIZE);
	Submarine submarine = Submarine(randomPosition.second);
	Coordinates bow;
	Coordinates stern;
	if (randomPosition.second == HORIZONTAL) {
	  bow = randomPosition.first;
	  stern = {bow.GetRow(), bow.GetCol() + submarine.GetWidth() - 1};
	} else {
	  bow = randomPosition.first;
	  stern = {bow.GetRow() + submarine.GetWidth() - 1, bow.GetCol()};
	}
	game_board_.PlaceShip(submarine, bow, stern);
  }
}

std::pair<Coordinates, Coordinates> Player::GetRandomMove() {
  return game_engine_.GetRandomMove(game_board_);
}

void Player::AddPotentialTargets(Coordinates target) {
  game_engine_.AddNearTargets(target);
}
bool Player::HasLost() {
  return false;
}
