#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_

#include "GameBoard.h"
#include "Player.h"
#include "Ship.h"
class Submarine : public Ship {
 public:
  static const int DEFAULT_SIZE = 1;
  /// Create una Ship di tipo Submarine a partire da prua e poppa. Se la distanza tra prua e poppa non corrisponde alla dimensione della nave lancia un std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  Submarine(Coordinates bow, Coordinates stern) : Submarine() {
	bow_ = bow;
	stern_ = stern;
  };
  Submarine() : Ship('E', DEFAULT_SIZE, 100) {
	ship_type_ = SUBMARINE;
  };

  /// Scansiona le celle del campo di gioco avversario presenti in un raggio di 5x5 al centro c'è il sottomarino.
  /// Generare prima le coordinate e utilizzare il metodo InquireState() di Player per ottenere lo stato della cella.
  /// \return Un vector delle coordinate che contengono navi avversarie.
  static std::map<Coordinates, OccupationType> ScanSurroundings(Player &opponent, Coordinates current_position);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
