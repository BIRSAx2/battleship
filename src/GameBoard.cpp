// Author: Alessandro Trigolo

#include "GameBoard.h"
bool GameBoard::PlaceShip(Coordinates bow, Coordinates stern, const Ship &ship) {

  std::shared_ptr<Ship> to_add = std::make_shared<Ship>(ship);
  if (bow.CalculateOffsetTo(stern) + 1 != ship.GetWidth())
	throw std::invalid_argument("The units between bow and stern must contain exactly the ship. Ship width: "
								+ std::to_string(ship.GetWidth()) + ", space between bow and stern: "
								+ std::to_string(bow.CalculateOffsetTo(stern) + 1));

  to_add->SetBow(bow);
  to_add->SetStern(stern);
  for (auto loc : to_add->GetLocations()) {
	if (occupied_locations_.count(loc) != 0) throw std::invalid_argument("Cannot place this ship here, location " + loc.ToUserCoordinates() + " is already occupied by another ship!");
  }
  for (auto loc : to_add->GetLocations()) {
	occupied_locations_.emplace(loc, to_add);
  }

  return true;
}

std::ostream &operator<<(std::ostream &os, const GameBoard &board) {
  return os << board.ToString();
}

bool GameBoard::ReceiveAttack(Coordinates target) {
  if (occupied_locations_.count(target) == 0) return false;
  if (protected_coordinates_.count(target) != 0) return false;
  occupied_locations_.at(target)->HitLocation(target);
  // Remove a ship if it's sunk
  if (occupied_locations_.at(target)->IsSunk()) {
	if (occupied_locations_.at(target)->GetShipType() == BATTLESHIP) available_battleships--;
	RemoveShip(target);
  }
  return true;
}

std::shared_ptr<Ship> GameBoard::GetShipAt(Coordinates location) {
  if (occupied_locations_.count(location) == 0) return nullptr;
  return occupied_locations_.at(location);
}

bool GameBoard::MoveShip(Coordinates origin, Coordinates target) {

  std::shared_ptr<Ship> ship = GetShipAt(origin);
  if (ship == nullptr) throw std::invalid_argument("There is no ship at the specified location.");

  auto current = ship->GetLocations();

  std::pair<Coordinates, Coordinates> bow_stern = GetBowAndSternFromCenter(target, ship);
  Coordinates bow = bow_stern.first;
  Coordinates stern = bow_stern.second;

  Ship tmp = Ship();
  tmp.SetBow(bow);
  tmp.SetStern(stern);

  for (auto loc : tmp.GetLocations()) {

	// if the loc is not empty, and it doesn't contain a part of this ship
	if (occupied_locations_.count(loc) != 0 && std::count(current.begin(), current.end(), loc) == 0) {
	  throw std::invalid_argument("Cannot move this ship, the location " + loc.ToUserCoordinates() + " is already occupied by another ship!");
	}
  }

  for (auto loc : current) {
	occupied_locations_.erase(loc);
  }
  ship->SetBow(bow);
  ship->SetStern(stern);

  if (!IsInsideBoard(*ship)) throw std::invalid_argument("The target is outside the board's bounds");

  for (auto loc : ship->GetLocations()) {
	occupied_locations_.emplace(loc, ship);
  }
  return true;
}
std::pair<Coordinates, Coordinates> GameBoard::GetBowAndSternFromCenter(const Coordinates &center, const std::shared_ptr<Ship> &ship) const {

  Coordinates bow, stern;
  if (ship->IsHorizontal()) {

	//
	bow = {center.GetRow(), center.GetCol() - ship->GetWidth() / 2};
	stern = {center.GetRow(), center.GetCol() + ship->GetWidth() / 2};
  } else {
	bow = {center.GetRow() - ship->GetWidth() / 2, center.GetCol()};
	stern = {center.GetRow() + ship->GetWidth() / 2, center.GetCol()};
  }
  return {bow, stern};
}

std::string GameBoard::ToString() const {

  std::stringstream string_stream;

  std::string horizontal_legend = "  1  2  3  4  5  6  7  8  9  10 11 12";

  std::string vertical_legend[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N"};
  int legend = 0;
  string_stream << ColourText256(horizontal_legend, 8) << "\n";

  for (int i = 0; i < GetRows(); ++i) {
	string_stream << ColourText256(std::string(vertical_legend[legend]), 8) << " ";
	for (int j = 0; j < GetCols(); ++j) {

	  if (occupied_locations_.count({i, j}) != 0) string_stream << occupied_locations_.at({i, j})->ToString({i, j}) << "  ";
	  else {
		string_stream << ColourText256(" ", 87) << "  ";
	  }
	}
	string_stream << ColourText256(std::string(vertical_legend[legend]), 8) << "\n";
	legend++;
  }
  string_stream << ColourText256(horizontal_legend, 8) << "\n";
  return string_stream.str();
}

bool GameBoard::CanPlaceShip(const Ship &ship) const {

  for (auto loc : Coordinates::GetCoordinatesBetween(ship.GetBow(), ship.GetStern())) {
	if (occupied_locations_.count(loc) != 0) return false;
  }
  return true;
}
bool GameBoard::IsInsideBoard(const Ship &ship) const {
  return Coordinates::IsValid(ship.GetBow().GetRow(), ship.GetBow().GetCol()) && Coordinates::IsValid(ship.GetStern().GetRow(), ship.GetStern().GetCol());
}
const std::map<Coordinates, std::shared_ptr<Ship>> &GameBoard::GetOccupiedLocations() const {
  return occupied_locations_;
}
void GameBoard::RemoveShip(Coordinates location) {
  //  std::cout << ColourBackground256("A ship has been sunk and it's getting removed from the board", 34) << std::endl;

  if (occupied_locations_.count(location) == 0) return;

  std::shared_ptr<Ship> ship = GetShipAt(location);

  for (auto loc : ship->GetLocations()) {
	occupied_locations_.erase(occupied_locations_.find(loc));
  }
}
int GameBoard::GetAvailableBattleships() const {
  return available_battleships;
}
