#include "Player.h"
std::string Player::ToString() const {

  std::string attack_board_title = "Griglia di attacco";
  std::string defence_board_title = "Griglia di difesa";
  std::stringstream attack;
  attack << firing_board_.ToString();

  std::stringstream defence;
  defence << game_board_.ToString();

  std::string line_from_firing_board;
  std::string line_from_game_board;

  std::stringstream boards_side_by_side;

  boards_side_by_side << std::string((80 - name_.length()) / 2, ' ') << ColourText256(name_, 118) << "\n"
					  // Padding per centrare il titolo della griglia di difesa
					  << std::string((40 - defence_board_title.length()) / 2, ' ') << ColourText256(defence_board_title, 198) << std::string((40 - defence_board_title.length()) / 2, ' ')
					  // Padding per centrare il titolo della griglia di attacco
					  << std::string((40 - attack_board_title.length()) / 2, ' ') << ColourText256(attack_board_title, 212) << "\n";

  while (std::getline(attack, line_from_firing_board, '\n') && std::getline(defence, line_from_game_board, '\n')) {
	boards_side_by_side << line_from_game_board << "\t" << line_from_firing_board << "\n";
  }

  return boards_side_by_side.str();
}
std::ostream &operator<<(std::ostream &os, const Player &player) {
  return os << player.ToString();
}
bool Player::PlaceShip(Coordinates bow, Coordinates stern, Ship &ship) {
  return game_board_.PlaceShip(bow, stern, ship);
}

bool Player::PlayMove(Coordinates origin, Coordinates target) {
  return false;
}
void Player::PlaceShipsRandomly() {
  // Get next ship
  // Get random empty cell in game_board_ (the bow) the stern is bow.GetCol + width if horizontal, bow.GetRow() + width if vertical
  // Try to fit the ship
  	// if the ship doesn't fit, delete all and start from scratch
  	// if ship fits, proceed to place the next ship.
}
