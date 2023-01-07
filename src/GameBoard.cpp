#include "GameBoard.h"
#include "Utility.h"
#include <iostream>
#include <utility>

GameBoard::GameBoard() : size_(DEFAULT_BOARD_SIZE) {
  tiles_.resize(size_, std::vector<Tile>(size_, Tile()));
}

GameBoard::GameBoard(int size) : size_(size) {
  tiles_.resize(size, std::vector<Tile>(size_, Tile()));
}

std::vector<std::vector<Tile>> &GameBoard::GetTiles() {
  return tiles_;
}

bool GameBoard::IsInsideBoard(int ship_width, Orientation orientation, Coordinates starting_position) {
  if (orientation == UNSET) throw std::invalid_argument("The orientation of the ship is unset");
  if (!starting_position.IsInBounds(0, 12)) return false;
  if (orientation == HORIZONTAL) return Coordinates(starting_position.GetRow(), starting_position.GetCol() + ship_width).IsInBounds();
  return Coordinates(starting_position.GetRow() + ship_width, starting_position.GetCol()).IsInBounds();
}

bool GameBoard::OverlapsOtherShip(const int width, const Orientation orientation, Coordinates &first_cell) {
  if (orientation == UNSET) throw std::invalid_argument("The orientation of the ship is unset");
  if (!first_cell.IsInBounds(0, size_)) throw std::invalid_argument("Invalid Coordinates");

  if (orientation == HORIZONTAL) {
	for (int i = first_cell.GetCol(); i < first_cell.GetCol() + width; ++i) {
	  if (tiles_[first_cell.GetRow()][i].IsOccupied()) return true;
	}
  } else {
	for (int i = first_cell.GetRow(); i < first_cell.GetRow() + width; ++i) {
	  if (tiles_[i][first_cell.GetCol()].IsOccupied()) return true;
	}
  }
  return false;
}

bool GameBoard::ReceiveAttack(Coordinates target) {
  if (!target.IsInBounds()) throw std::invalid_argument("Target not inside the game board");
  Tile &targetTile = tiles_.at(target.GetRow()).at(target.GetCol());
  if (targetTile.IsOccupied() || targetTile.GetOccupationType() == HIT) {
	targetTile.SetOccupationType(HIT);
	tiles_.at(target.GetRow()).at(target.GetCol()).GetShip()->IncreaseHits();
	return true;
  }

  return false;
}

std::vector<Tile> GameBoard::ScanSurroundings(Coordinates coordinates, int range) {
  std::vector<Tile> surroundings;
  for (int i = coordinates.GetRow() - range; i <= coordinates.GetRow() + range; ++i) {
	for (int j = coordinates.GetCol() - range; j <= coordinates.GetCol() + range; ++j) {

	  if (i >= 0 && i < size_ && j >= 0 && j < size_) {
		surroundings.push_back(tiles_[i][j]);
	  }
	}
  }
  return surroundings;
}

void GameBoard::MarkTile(Coordinates target, OccupationType new_type) {
  if (target.GetCol() < 0 || target.GetCol() >= size_ || target.GetRow() < 0 || target.GetRow() >= size_)
	throw std::invalid_argument("Target out of range");

  tiles_.at(target.GetRow()).at(target.GetCol()).SetOccupationType(new_type);
}

void GameBoard::MarkTile(Coordinates target, OccupationType new_type, Ship *ship) {
  if (target.GetCol() < 0 || target.GetCol() >= size_ || target.GetRow() < 0 || target.GetRow() >= size_)
	throw std::invalid_argument("Target out of range");
  Tile &tile = tiles_.at(target.GetRow()).at(target.GetCol());
  tile.SetOccupationType(new_type);
  tile.SetShip(ship);
}

void GameBoard::SetTiles(std::vector<std::vector<Tile>> tiles) {
  tiles_ = std::move(tiles);
}

std::ostream &operator<<(std::ostream &os, GameBoard board) {

  std::string horizontal_legend = "  1  2  3  4  5  6  7  8  9  10 11 12";

  std::string arr[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N"};
  int legend = 0;
  os << colour_text_256(horizontal_legend, 8) << "\n";
  for (auto &row : board.GetTiles()) {
	os << colour_text_256(std::string(arr[legend]), 8) << " ";
	for (auto tile : row) {
	  os << tile << "  ";
	}
	os << colour_text_256(std::string(arr[legend]), 8) << "\n";
	legend++;
  }
  return os << colour_text_256(horizontal_legend, 8) << "\n";
}

bool GameBoard::MoveShip(Coordinates origin, Coordinates target, int width, Orientation orientation) {
  // TODO: There might a bug here: The coordinates should point to the center of a ship
  std::cout << "Moving ship from  " << origin << " to " << target << std::endl;

  OccupationType occupation_type = tiles_.at(origin.GetRow()).at(origin.GetCol()).GetOccupationType();

  if (occupation_type == BATTLESHIP) throw std::invalid_argument("Cannot move this ship either because it's a battleship");

  std::vector<Coordinates> occupied_tiles = Coordinates::GetAdjacentCoordinates(origin, orientation, width);

  // marking old ship position as empty
  // necessario per mantenere traccia di quali celle della nave sono state colpite
  std::map<Coordinates, OccupationType> hits;
  for (auto cell : occupied_tiles) {
	hits.emplace(cell, tiles_.at(cell.GetRow()).at(cell.GetCol()).GetOccupationType());
	tiles_.at(cell.GetRow()).at(cell.GetCol()).SetOccupationType(EMPTY);
  }
  // marking new ship position
  std::vector<Coordinates> new_tiles = Coordinates::GetAdjacentCoordinates(target, orientation, width);
  for (int i = 0; i < new_tiles.size(); ++i) {
	Coordinates old = occupied_tiles.at(i);
	Coordinates cell = new_tiles.at(i);
	tiles_.at(cell.GetRow()).at(cell.GetCol()).SetOccupationType(hits.at(old));
  }
  return true;
}

int GameBoard::GetSize() const {
  return size_;
}

void GameBoard::SetSize(int size) {
  size_ = size;
}

bool GameBoard::PlaceShip(Ship ship, Coordinates bow, Coordinates stern) {

  // Check if the position is inside the bounds of the board

  if (!GameBoard::IsInsideBoard(ship.GetWidth(), ship.GetOrientation(), bow)) {
	throw std::invalid_argument("Ship outside of the board's bounds");
  }
  // Check if the ship doesn't overlap other ships

  if (OverlapsOtherShip(ship.GetWidth(), ship.GetOrientation(), bow)) {
	throw std::invalid_argument("Ship overlaps another ship");
  }

  // Place the ship in the board

  std::vector<Coordinates> tiles = Coordinates::GetAdjacentCoordinates(bow, ship.GetOrientation(), ship.GetWidth());
  for (auto coordinate : tiles) {
	MarkTile(coordinate, ship.GetOccupationType(), &ship);
  }
  // Add the ship to the user's roster
  ships_.emplace(bow, std::move(ship));

  return true;
}

bool GameBoard::MoveShip(Coordinates origin, Coordinates target) {

  if (ships_.count(origin) == 0) throw std::invalid_argument("Ship not found");

  Ship &ship = ships_.at(origin);
  std::cout << ship << std::endl;
  if (ship.IsSunk()) throw std::invalid_argument("This ship is sunk and cannot be moved");
  MoveShip(origin, target, ship.GetWidth(), ship.GetOrientation());

  ships_.erase(origin);
  ships_.emplace(target, ship);
  return true;
}
const std::map<Coordinates, Ship> &GameBoard::GetShips() const {
  return ships_;
}
void GameBoard::SetShips(const std::map<Coordinates, Ship> &ships) {
  ships_ = ships;
}

void GameBoard::IncreaseShipHits(Coordinates target) {
  if (ships_.count(target) == 0) return;
  ships_.at(target).IncreaseHits();
}
