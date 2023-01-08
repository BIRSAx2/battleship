#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BOARD_H_

class Board {
 private:
  int rows_;
  int cols_;

 public:
  /// Crea un oggetto Board con rows righe e cols colonne
  /// \param rows
  /// \param cols
  Board(int rows, int cols);

 public:
  int GetRows() const;
  void SetRows(int rows);
  int GetCols() const;
  void SetCols(int cols);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BOARD_H_
