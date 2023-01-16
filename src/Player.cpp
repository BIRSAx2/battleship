// Author: Mouhieddine Sabir


#include "Player.h"
#include "Battleship.h"
#include "GameRecorder.h"
#include "Submarine.h"
#include "SupportShip.h"
std::string Player::ToString() const {

  std::string attack_board_title = "Attack board";
  std::string defence_board_title = "Defence board";
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

void Player::PlaceShipsRandomly(GameRecorder &recorder) {
  // 3 Battleships of width 5
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Coordinates> randomPosition = GetRandomShipPlacement(Battleship::DEFAULT_SIZE);
	Battleship ship = Battleship(randomPosition.first, randomPosition.second);
	game_board_.PlaceShip(randomPosition.first, randomPosition.second, ship);
	recorder.RecordShipPlacement(randomPosition.first, randomPosition.second, ship.GetWidth());
  }

  // 3 Support ships of width 3
  for (int i = 0; i < 3; ++i) {
	std::pair<Coordinates, Coordinates> randomPosition = GetRandomShipPlacement(SupportShip::DEFAULT_SIZE);
	SupportShip ship = SupportShip(randomPosition.first, randomPosition.second);
	game_board_.PlaceShip(randomPosition.first, randomPosition.second, ship);
	recorder.RecordShipPlacement(randomPosition.first, randomPosition.second, ship.GetWidth());
  }

  // 2 submarines of width 1
  for (int i = 0; i < 2; ++i) {
	std::pair<Coordinates, Coordinates> randomPosition = GetRandomShipPlacement(Submarine::DEFAULT_SIZE);
	Submarine ship = Submarine(randomPosition.first, randomPosition.second);
	game_board_.PlaceShip(randomPosition.first, randomPosition.second, ship);
	recorder.RecordShipPlacement(randomPosition.first, randomPosition.second, ship.GetWidth());
  }
}

std::pair<Coordinates, Coordinates> Player::GetRandomShipPlacement(int ship_width) const {
  bool is_horizontal = RandomIntInRange(0, 2);
  return GetRandomShipPlacement(ship_width, is_horizontal);
}
std::pair<Coordinates, Coordinates> Player::GetRandomShipPlacement(int ship_width, bool is_horizontal) const {

  Coordinates bow;
  Coordinates stern;
  Ship ship;
  ship.SetWidth(ship_width);

  do {
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
  } while (!game_board_.CanPlaceShip(ship));

  return std::make_pair(bow, stern);
}

std::pair<Coordinates, Coordinates> Player::GenerateRandomMove() {

  // Pick a random ship of the ones placed

  std::vector<Coordinates> occupied_location;
  for (const auto &loc : game_board_.GetOccupiedLocations()) {
	occupied_location.emplace_back(loc.first);
  }

  // picking a random ship
  Coordinates origin = occupied_location.at(RandomIntInRange(0, (int)occupied_location.size()));

  std::shared_ptr<Ship> ship = game_board_.GetShipAt(origin);

  origin = ship->GetShipCenter();

  if (ship->GetShipType() == BATTLESHIP) {
	// if battleship just generate a target to shoot at
	return {origin, GetNextTarget()};
  }

  std::pair<Coordinates, Coordinates> bow_stern = GetRandomShipPlacement(ship->GetWidth(), ship->IsHorizontal());
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
  return game_board_.MoveShip(origin, target);
}
const std::string &Player::GetName() const {
  return name_;
}
Coordinates Player::GetNextTarget() {

  if (next_targets_.empty()) return Coordinates::GetRandomCoordinates();
  auto end = next_targets_.begin();
  Coordinates target = *end;
  next_targets_.erase(end);

  return target;
}
void Player::AddNextTargets(Coordinates successfully_hit_target) {
  std::set<Coordinates> new_target = Coordinates::GetAdjacentStarCoordinates(successfully_hit_target);
  for (auto target : new_target) {
	if (firing_board_.HasBeenAttacked(target)) continue;
	next_targets_.insert(target);
  }
}

void Player::AddNextTargets(const std::map<Coordinates, OccupationType> &submarine_sightings) {
  next_targets_.clear();
  for (auto target : submarine_sightings) {
	next_targets_.insert(target.first);
  }
}
OccupationType Player::InquireState(Coordinates coordinates) {
  if (GetShipAt(coordinates) != nullptr) {
	std::shared_ptr<Ship> ship = GetShipAt(coordinates);
	if (ship->IsHit(coordinates)) return HIT;

	return OCCUPIED;
  }
  return EMPTY;
}
void Player::AddSubmarineSightings(const std::map<Coordinates, OccupationType> &scan_from_submarine) {
  this->firing_board_.AddSubmarineSightings(scan_from_submarine);
}

bool Player::HasLost() {
  return game_board_.GetAvailableBattleships() == 0;
}
void Player::ClearSubmarineSightings() {
  firing_board_.ClearSubmarineSightings();
}
void Player::ClearSuccessfulHits() {
  firing_board_.ClearSuccessfulHits();
}
void Player::ClearUnsuccessfulHits() {
  firing_board_.ClearUnsuccessfulHits();
}
void Player::ClearAllHits() {
  firing_board_.Clear();
}
void Player::RepairShipAt(Coordinates coordinates) {
  std::shared_ptr<Ship> ship = game_board_.GetShipAt(coordinates);
  if (ship != nullptr) ship->Repair();
}
std::string Player::GetAttackMessage(bool is_successful) {

  std::stringstream stringstream;

  if (is_successful && is_human_) {
	return ColourText256("HIT!", 82) + " We got em!\n";
  }

  if (!is_successful && is_human_) {
	return ColourText256("SPLASH!", 1) + " We missed!\n";
  }

  if (is_successful && !is_human_) {
	return ColourText256("HIT!", 1) + " They got us!\n";
  }

  return ColourText256("SPLASH!", 82) + " They missed\n";
}
