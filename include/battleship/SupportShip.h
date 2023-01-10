#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_

#include "Ship.h"
#include "Utility.h"
class SupportShip : public Ship {
 public:
  static const int DEFAULT_SIZE = 3;

  /// Create una Ship di tipo SupportShip a partire da prua e poppa. Se la distanza tra prua e poppa non corrisponde alla dimensione della nave lancia un std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  SupportShip(Coordinates bow, Coordinates stern) : SupportShip() {
	bow_ = bow;
	stern_ = stern;
  };
  /// Create una Ship di tipo SupportShip senza specificare la prua e la poppa.
  /// \throws std::invali_argument
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  SupportShip() : Ship('S', DEFAULT_SIZE, 106) {
	icon_color_ = 106;
	ship_type_ = SUPPORTSHIP;
  };
  /// Cambia la prua e poppa di questa nave a partire da target. La prua e la poppa sono calcolate utilizzando target come cella centrale della nave.
  /// \param target
  /// \return true nel caso sia stato possibile cambiare posizione della nave, altrimenti false. Per il momento restituisce sempre true.
  bool MoveShip(Coordinates target);
  /// Restituisce un vector contente le coordinate delle celle coperte dalla questa nave.
  /// \return Un std::vector<Coordinate> contente le celle che questa nave copre dagli attacchi.
  std::vector<Coordinates> GetProtectedCoordinates();
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
