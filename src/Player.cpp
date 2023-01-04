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
  return std::all_of(ships_.begin(), ships_.end(), [](const std::pair<Coordinates, Ship> &pair) { return pair.second.IsSunk(); });
}

std::string Player::ToString() const {

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

std::ostream &operator<<(std::ostream &os, const Player &player) {
  return os << player.ToString();
}

Player::Player() : name_("unknown player") {
}

void Player::PlaceShipsRandomly() {

  // 3 Corazzate, dimensione 5
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Orientation> randomPosition = GetRandomShipPosition(Battleship::DEFAULT_SIZE);
	PlaceShip(Battleship(randomPosition.second), randomPosition.first);
  }
  // 3 Navi di supporto, dimensione 3
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Orientation> randomPosition = GetRandomShipPosition(SupportShip::DEFAULT_SIZE);
	PlaceShip(SupportShip(randomPosition.second), randomPosition.first);
  }
  // 2 Sottomarini di esplorazione, dimensione 1
  for (int i = 0; i < 2; ++i) {
	std::pair<Coordinates, Orientation> randomPosition = GetRandomShipPosition(Submarine::DEFAULT_SIZE);
	PlaceShip(Submarine(randomPosition.second), randomPosition.first);
  }
}

void Player::PlaceShips(std::map<Coordinates, Ship> ships) {
}

bool Player::PlaceShip(const Ship &ship, Coordinates coordinates) {

  // Check if the position is inside the bounds of the board

  if (!GameBoard::IsInsideBoard(ship.GetWidth(), ship.GetOrientation(), coordinates)) {
	throw std::invalid_argument("Ship outside of the board's bounds");
  }
  // Check if the ship doesn't overlap other ships

  if (game_board_.OverlapsOtherShip(ship.GetWidth(), ship.GetOrientation(), coordinates)) {
	throw std::invalid_argument("Ship overlaps another ship");
  }

  // Place the ship in the board

  // The coordinates refer to the central cell of a ship

  Orientation orientation = ship.GetOrientation();
  int width = ship.GetWidth();

  int first = orientation == HORIZONTAL ? coordinates.GetCol() : coordinates.GetRow();
  first -= (width - 1) / 2;

  if (orientation == HORIZONTAL) {
	coordinates.SetCol(first);
  } else {
	coordinates.SetRow(first);
  }
  std::vector<Coordinates> tiles = Coordinates::GetAdjacentCoordinates(coordinates, orientation, width);

  for (auto coordinate : tiles) {
	game_board_.MarkTile(coordinate, ship.GetOccupationType());
  }
  // Add the ship to the user's roster

  ships_.emplace(coordinates, ship);

  return true;
}

bool Player::HandleAttack(Coordinates target) {
  if (!target.IsInBounds(0, 12)) throw std::invalid_argument("Target outside the board");
  bool result = game_board_.ReceiveAttack(target);
  // successfull attack
  if (result) {
	// TODO: Handle discrepancy between player ships and board ships
	ships_.at(target).IncreaseHits();
  }
  return result;
}

std::pair<Coordinates, Orientation> Player::GetRandomShipPosition(int ship_width) {

  // TODO: Refactor this to use a more deterministic approach, first generate a list of available positions and the choose randomly between it's elements
  Orientation orientation;
  Coordinates coordinates{0, 0};
  Ship ship;
  do {
	coordinates = {random_int_in_range(0, game_board_.GetSize()), random_int_in_range(0, game_board_.GetSize())};
	orientation = static_cast<Orientation>(random_int_in_range(0, 1));
  } while (!GameBoard::IsInsideBoard(ship_width, orientation, coordinates) || game_board_.OverlapsOtherShip(ship_width, orientation, coordinates));
  return std::make_pair(coordinates, orientation);
}
void Player::MoveShip(Coordinates origin, Coordinates target, const Ship &ship_to_move) {
  if (ship_to_move.GetHits() != 0) throw std::invalid_argument("Cannot move ship because it's hit");
  if (!ships_.count(origin)) throw std::invalid_argument("Ship not found");
  game_board_.MoveShip(origin, target, ship_to_move.GetWidth(), ship_to_move.GetOrientation());
  Ship ship = ships_.at(origin);
  ships_.erase(origin);
  ships_.emplace(target, ship);
}
