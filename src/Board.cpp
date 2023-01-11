#include "Board.h"
int Board::GetRows() const {
  return rows_;
}
void Board::SetRows(int rows) {
  rows_ = rows;
}
int Board::GetCols() const {
  return cols_;
}
void Board::SetCols(int cols) {
  cols_ = cols;
}
Board::Board(int rows, int cols) : rows_(rows), cols_(cols) {}
