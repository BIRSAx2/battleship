#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_

#include "GameBoard.h"
#include "Ship.h"
class Submarine : public Ship {
 public:
  /// Create una Ship di tipo Submarine a partire da prua e poppa. Se la distanza tra prua e poppa non corrisponde alla dimensione della nave lancia un std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  Submarine(Coordinates bow, Coordinates stern) : Ship('E', 1, 100) {
	bow_ = bow;
	stern_ = stern;
  };
  Submarine() : Ship('E', 1, 100) {
	ship_type_ = SUBMARINE;
  };
  /// Cambia la prua e poppa di questa nave a partire da target. La prua e la poppa sono calcolate utilizzando target come cella centrale della nave.
  /// \param target
  /// \return true nel caso sia stato possibile cambiare posizione della nave, altrimenti false. Per il momento restituisce sempre true.

  bool MoveShip(Coordinates target);

  /// Scansiona le celle del campo di gioco avversario presenti in un raggio di 5 celle dal centro della nave.
  /// \return Un vector delle coordinate che contengono navi avversarie.
  std::vector<Coordinates> ScanSurroundings(GameBoard opponent_board);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
