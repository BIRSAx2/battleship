#include "Player.h"
#include "Battleship.h"
#include "Submarine.h"
#include "SupportShip.h"
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

void Player::PlaceShipsRandomly() {
  // Tre Corazzate, dimensione 5
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Coordinates> randomPosition = GetRandomShipPlacement(Battleship::DEFAULT_SIZE);
	Battleship ship = Battleship(randomPosition.first, randomPosition.second);
	game_board_.PlaceShip(randomPosition.first, randomPosition.second, ship);
  }

  // Tre Navi di support, dimensione 3
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Coordinates> randomPosition = GetRandomShipPlacement(SupportShip::DEFAULT_SIZE);
	SupportShip ship = SupportShip(randomPosition.first, randomPosition.second);
	game_board_.PlaceShip(randomPosition.first, randomPosition.second, ship);
  }

  // Due Sottomarini di esplicazione , dimensione 1
  for (int i = 0; i < 2; ++i) {
	std::pair<Coordinates, Coordinates> randomPosition = GetRandomShipPlacement(Submarine::DEFAULT_SIZE);
	Submarine ship = Submarine(randomPosition.first, randomPosition.second);
	game_board_.PlaceShip(randomPosition.first, randomPosition.second, ship);
  }
}

std::pair<Coordinates, Coordinates> Player::GetRandomShipPlacement(int ship_width) const {

  Coordinates bow;
  Coordinates stern;
  Ship ship;
  ship.SetWidth(ship_width);

  do {
	bool is_horizontal = RandomIntInRange(0, 1);

	bow.SetRow(RandomIntInRange(0, game_board_.GetRows()));

	// Calculating the stern

	if (is_horizontal) {
	  bow.SetCol(RandomIntInRange(0, game_board_.GetCols() - ship_width));
	  bow.SetRow(RandomIntInRange(0, game_board_.GetRows()));
	  stern.SetRow(bow.GetRow());
	  stern.SetCol(bow.GetCol() + ship_width - 1);
	} else {
	  bow.SetCol(RandomIntInRange(0, game_board_.GetCols()));
	  bow.SetRow(RandomIntInRange(0, game_board_.GetRows() - ship_width));
	  stern.SetCol(bow.GetCol());
	  stern.SetRow(bow.GetRow() + ship_width - 1);
	}

	ship.SetBow(bow);
	ship.SetStern(stern);
  } while (!game_board_.IsInsideBoard(ship) || !game_board_.CanPlaceShip(ship));
  return std::make_pair(bow, stern);
}

std::pair<Coordinates, Coordinates> Player::GenerateRandomMove() {

  // Pick a random ship of the ones placed

  std::vector<Coordinates> occupied_location;
  for (const auto &loc : game_board_.GetOccupiedLocations()) {
	occupied_location.emplace_back(loc.first);
  }

  Coordinates origin = occupied_location.at(RandomIntInRange(0, (int)occupied_location.size()));

  std::shared_ptr<Ship> ship = game_board_.GetShipAt(origin);

  origin = ship->GetShipCenter();

  if (ship->GetShipType() == BATTLESHIP) {
	// if battleship just generate a target to shoot at
	return {origin, GetNextTarget()};
  }

  // if support ship or submarine we need to generate a valid coordinate to move it to

  std::pair<Coordinates, Coordinates> bow_stern = GetRandomShipPlacement(ship->GetWidth());
  Coordinates target = Coordinates::GetCoordinatesBetween(bow_stern.first, bow_stern.second).at(ship->GetWidth() / 2);
  return std::make_pair(origin, target);
}

std::shared_ptr<Ship> Player::GetShipAt(Coordinates location) {
  return game_board_.GetShipAt(location);
}
bool Player::ReceiveAttack(Coordinates coordinates) {
  return game_board_.ReceiveAttack(coordinates);
}
void Player::MarkAttack(Coordinates target, bool is_successful) {
  firing_board_.MarkAttack(target, is_successful);
}
bool Player::MoveShip(Coordinates origin, Coordinates target) {
  bool successfully_moved = game_board_.MoveShip(origin, target);
  return successfully_moved;
}
const std::string &Player::GetName() const {
  return name_;
}
void Player::SetName(const std::string &name) {
  name_ = name;
}
Coordinates Player::GetNextTarget() {

  if (next_targets_.empty()) return Coordinates::GetRandomCoordinates();
  Coordinates target = *next_targets_.begin();
  next_targets_.erase(target);
  return target;
}
void Player::AddNextTargets(Coordinates successfully_hit_target) {
  std::set<Coordinates> new_target = Coordinates::GetAdjacentStarCoordinates(successfully_hit_target);
  // TODO: Use submarine sighting to develop a more efficient algorithm

  // It's a hard task to develop an efficient and fast algorithm to play this variant of the battleship game.
  // The main reason behind this is the fact that ships can move, so keeping track of where the enemy ships might be is basically useless, as an enemy can move the ship under attack right after an attack.
  // Making it useless to hit the targets near the one just hit in search of the remaining parts of the ship.
  for (auto target : new_target) {
	if (firing_board_.HasBeenAttacked(target)) continue;
	next_targets_.insert(target);
  }
}

void Player::AddNextTargets(std::map<Coordinates, OccupationType> submarine_sightings) {
  next_targets_.clear();
  for (auto target : submarine_sightings) {
	next_targets_.insert(target.first);
  }
}
OccupationType Player::InquireState(Coordinates coordinates) {
  if (GetShipAt(coordinates) != nullptr) return OCCUPIED;
  return EMPTY;
}
void Player::UpdateSubmarineSightings(const std::map<Coordinates, OccupationType> &scan_from_submarine) {
  this->firing_board_.AddSubmarineSightings(scan_from_submarine);
}

bool Player::HasLost() {
  return game_board_.GetAvailableBattleships() == 0;
}