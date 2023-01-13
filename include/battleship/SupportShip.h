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
  /// Restituisce un vector contente le coordinate delle celle coperte dalla questa nave.
  /// \return Un std::set<Coordinate> contente le celle che questa nave copre dagli attacchi.
  static std::set<Coordinates> GetProtectedCoordinates(Coordinates current_position);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
