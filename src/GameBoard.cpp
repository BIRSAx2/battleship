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

  tiles_[target.GetRow()][target.GetCol()].SetOccupationType(new_type);
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

  std::cout << (*this) << std::endl;
  // TODO: Cannot Move ship if it's hit
  // TODO: There might a bug here: The coordinates should point to the center of a ship
  std::cout << "Moving ship from  " << origin << " to " << target << std::endl;

  OccupationType occupation_type = tiles_.at(origin.GetRow()).at(origin.GetCol()).GetOccupationType();

  if (occupation_type == HIT || occupation_type == BATTLESHIP) throw std::invalid_argument("Cannot move this ship either because it's already hit or because it's battleship");

  std::vector<Coordinates> occupied_tiles = Coordinates::GetAdjacentCoordinates(origin, orientation, width);

  // marking old ship position as empty
  // TODO: Check if we need to keep a spot marked as shot or if when we move the ship it becomes empty regardless

  std::cout << "Occupied cells: ";
  for (auto cell : occupied_tiles) {
	std::cout << cell << ' ' << tiles_.at(cell.GetRow()).at(cell.GetCol()).GetOccupationType();
	tiles_.at(cell.GetRow()).at(cell.GetCol()).SetOccupationType(EMPTY);
  }
  std::cout << std::endl;
  // marking new ship position
  std::vector<Coordinates> new_tiles = Coordinates::GetAdjacentCoordinates(target, orientation, width);
  std::cout << "New cells: ";
  for (auto cell : new_tiles) {
	std::cout << cell << ' ';
	tiles_.at(cell.GetRow()).at(cell.GetCol()).SetOccupationType(occupation_type);
  }
  std::cout << std::endl;
  return true;
}

int GameBoard::GetSize() const {
  return size_;
}

void GameBoard::SetSize(int size) {
  size_ = size;
}