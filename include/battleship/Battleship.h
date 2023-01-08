#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_

#include "GameBoard.h"
#include "Ship.h"
#include "Utility.h"

class Battleship : public Ship {
 public:
  /// Create una Ship di tipo Battleship a partire da prua e poppa. Se la distanza tra prua e poppa non corrisponde alla dimensione della nave lancia un std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  Battleship(Coordinates bow, Coordinates stern);
  Battleship() : Ship('C', 5, 127) {
	ship_type_ = BATTLESHIP;
  }
  /// Colpisce la cella target del campo di gioco avversario.
  /// \param opponent_board La griglia di gioco dell'avversario.
  /// \param target La cella colpire.
  /// \return true se l'attacco è andato a buon fine, false se invece non è andato a buon fine.
  bool ShootAt(GameBoard opponent_board, Coordinates target);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_BATTLESHIP_H_