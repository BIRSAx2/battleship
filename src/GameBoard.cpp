#include "GameBoard.h"
GameBoard::GameBoard() : size_(DEFAULT_BOARD_SIZE) {
  tiles_.resize(size_, std::vector<Tile>(size_, Tile()));
}
GameBoard::GameBoard(int size) : size_(size) {
  tiles_.resize(size, std::vector<Tile>(size_, Tile()));
}
std::vector<std::vector<Tile>> GameBoard::GetTiles() const {
  return tiles_;
}
bool GameBoard::IsInsideBoard(Ship ship, Coordinates startingPositions) {

  // Le coordinate si riferiscono alla casella centrale di una nave

  return false;
}
bool GameBoard::OverlapsShip(Ship ship, Coordinates startingPositions) {
  return false;
}
bool GameBoard::ReceiveAttack(Coordinates target) {
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

  char arr[] = {'A', 'B','C','D','E','F','G','H','I','L','M','N'};
  int legend = 0;
  for (const auto &row : board.GetTiles()) {
	os << arr[legend++] << ' ';
	for (auto tile : row) {
	  os << tile << "  ";
	}
	os << '\n';
  }
  return os << "  1  2  3  4  5  6  7  8  9  10 11 12\n";
}
bool GameBoard::MoveShip(Coordinates origin, Coordinates target) {
  return false;
}
