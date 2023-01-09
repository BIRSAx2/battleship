#include "GameBoard.h"
bool GameBoard::PlaceShip(Coordinates bow, Coordinates stern, const Ship &ship) {

  std::shared_ptr<Ship> to_add = std::make_shared<Ship>(ship);
  if (bow.CalculateOffsetTo(stern) + 1 != ship.GetWidth()) throw std::invalid_argument("Le coordinate specificate per prua e poppa non sono sufficienti per contenere la nave");

  to_add->SetBow(bow);
  to_add->SetStern(stern);

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
  occupied_locations_.at(target)->HitLocation(target);
  return true;
}

std::shared_ptr<Ship> GameBoard::GetShipAt(Coordinates location) {
  if (occupied_locations_.count(location) == 0) return nullptr;
  return occupied_locations_.at(location);
}

bool GameBoard::MoveShip(Coordinates origin, Coordinates target) {

  std::shared_ptr<Ship> ship = GetShipAt(origin);
  if (ship == nullptr) throw std::invalid_argument("no ship scemo");

  auto current = ship->GetLocations();

  // TODO: add check of already occupied positions
  // TODO: add check if the ship is inside

  // idea: take the item at the center of current, it's the center of the ship.

  //horizontal

  Coordinates bow;
  Coordinates stern;
  if (ship->IsHorizontal()) {
	bow = {target.GetRow(), target.GetCol() - ship->GetWidth() / 2};
	stern = {target.GetRow(), target.GetCol() + ship->GetWidth() / 2};
  } else {
	bow = {target.GetRow() - ship->GetWidth() / 2, target.GetCol()};
	stern = {target.GetRow() + ship->GetWidth() / 2, target.GetCol()};
  }

  for (auto loc : current) {
	occupied_locations_.erase(loc);
  }
  ship->SetBow(bow);
  ship->SetStern(stern);

  for (auto loc : ship->GetLocations()) {
	occupied_locations_.emplace(loc, ship);
  }
  return true;
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
		string_stream << ColourText256("~", 87) << "  ";
	  }
	}
	string_stream << ColourText256(std::string(vertical_legend[legend]), 8) << "\n";
	legend++;
  }
  string_stream << ColourText256(horizontal_legend, 8) << "\n";
  return string_stream.str();
}
