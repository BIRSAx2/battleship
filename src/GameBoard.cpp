#include "GameBoard.h"
#include "Utility.h"
#include <iostream>
GameBoard::GameBoard() : size_(DEFAULT_BOARD_SIZE) {
  tiles_.resize(size_, std::vector<Tile>(size_, Tile()));
}
GameBoard::GameBoard(int size) : size_(size) {
  tiles_.resize(size, std::vector<Tile>(size_, Tile()));
}
std::vector<std::vector<Tile>> GameBoard::GetTiles() const {
  return tiles_;
}
bool GameBoard::IsInsideBoard(int ship_width, Orientation orientation, Coordinates starting_position) {
  if (orientation == UNSET) throw std::invalid_argument("The orientation of the ship is unset");
  if (!starting_position.IsInBounds(0, 12)) return false;

  // Le coordinate si riferiscono alla casella centrale di una nave

  int first = 0, last = 0;

  first = orientation == HORIZONTAL ? starting_position.GetCol() : starting_position.GetRow();

  first -= (ship_width - 1) / 2;
  last = first + ship_width - 1;

  return Coordinates(first, last).IsInBounds(0, 12);
}
bool GameBoard::OverlapsOtherShip(const int width, const Orientation orientation, Coordinates &startingPositions) {
  if (orientation == UNSET) throw std::invalid_argument("The orientation of the ship is unset");
  if (!startingPositions.IsInBounds(0, size_)) throw std::invalid_argument("Invalid Coordinates");

  // Le coordinate si riferiscono alla casella centrale di una nave

  int first = 0, last = 0;
  first = orientation == HORIZONTAL ? startingPositions.GetCol() : startingPositions.GetRow();
  first -= (width - 1) / 2;
  last = first + width - 1;

  for (int i = first; i <= last; ++i) {
	if (orientation == HORIZONTAL) {
	  if (tiles_[startingPositions.GetRow()][i].IsOccupied()) return true;
	} else {
	  if (tiles_[i][startingPositions.GetCol()].IsOccupied()) return true;
	}
  }
  return false;
}
bool GameBoard::ReceiveAttack(Coordinates target) {
  if (!target.IsInBounds(0, 12)) throw std::invalid_argument("Target not inside the game board");
  Tile &targetTile = tiles_[target.GetRow()][target.GetCol()];
  if (targetTile.IsOccupied()) {
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
void GameBoard::ChangeTileType(Coordinates target, OccupationType type) {
  if (target.GetCol() < 0 || target.GetCol() >= size_ || target.GetRow() < 0 || target.GetRow() >= size_)
	throw std::invalid_argument("Target out of range");

  tiles_[target.GetRow()][target.GetCol()].SetOccupationType(type);
}
void GameBoard::MarkTile(Coordinates target, OccupationType newType) {
  ChangeTileType(target, newType);
}
void GameBoard::SetTiles(std::vector<std::vector<Tile>> tiles) {
  tiles_ = tiles;
}
std::ostream &operator<<(std::ostream &os, const GameBoard &board) {

  std::string horizontal_legend = "  1  2  3  4  5  6  7  8  9  10 11 12";

  std::string arr[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N"};
  int legend = 0;
  os << colour_text_256(horizontal_legend, 8) << "\n";
  for (const auto &row : board.GetTiles()) {
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

  // TODO: Cannot Move ship if it's hit
  // TODO: There might a bug here: The coordinates should point to the center of a ship
  std::cout << "Moving ship from  " << origin << " to " << target << std::endl;

  OccupationType occupation_type = tiles_[origin.GetRow()][origin.GetCol()].GetOccupationType();
  std::vector<Coordinates> occupied_tiles = Coordinates::GetAdjacentCoordinates(origin, orientation, width);

  // marking old ship position as empty
  // TODO: Check if we need to keep a spot marked as shot or if when we move the ship it becomes empty regardless
  for (auto cell : occupied_tiles) {
	tiles_.at(cell.GetRow()).at(cell.GetCol()).SetOccupationType(EMPTY);
  }

  // marking new ship position
  std::vector<Coordinates> new_tiles = Coordinates::GetAdjacentCoordinates(target, orientation, width);
  for (auto cell : new_tiles) {
	tiles_.at(cell.GetRow()).at(cell.GetCol()).SetOccupationType(occupation_type);
  }

  return true;
}
int GameBoard::GetSize() const {
  return size_;
}
void GameBoard::SetSize(int size) {
  size_ = size;
}
