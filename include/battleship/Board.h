#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BOARD_H_

class Board {
 private:
  int rows_;
  int cols_;

 public:
  /// Create a Board object of dimension rows x cols
  /// \param rows
  /// \param cols
  Board(int rows, int cols) : rows_{rows}, cols_{cols} {};

 public:
  int GetRows() const { return rows_; };
  void SetRows(int rows) { rows_ = rows; };
  int GetCols() const { return cols_; };
  void SetCols(int cols) { cols_ = cols; };
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BOARD_H_
