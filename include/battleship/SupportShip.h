#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_

#include "Ship.h"
#include "Utility.h"
class SupportShip : public Ship {
 public:
  static const int DEFAULT_SIZE = 3;

  /// Creates a Ship of type SupportShip starting from the bow and stern. If the bow to stern distance does not match the vessel size, throw a std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow The bow of the ship
  /// \param stern The stern of the ship
  SupportShip(Coordinates bow, Coordinates stern) : SupportShip() {
	bow_ = bow;
	stern_ = stern;
  };
  /// Creates a ship of tupe SupportShip.
  /// \throws std::invali_argument
  /// \param bow The bow of the ship
  /// \param stern The stern of the ship
  SupportShip() : Ship('S', DEFAULT_SIZE, 106) {
	icon_color_ = 106;
	ship_type_ = SUPPORTSHIP;
  };

  // TODO: remove this
  /// Restituisce un vector contente le coordinate delle celle coperte dalla questa nave.
  /// \return Un std::set<Coordinate> contente le celle che questa nave copre dagli attacchi.
  static std::set<Coordinates> GetProtectedCoordinates(Coordinates current_position);


  // TODO: define this
  static std::set<Coordinates> RepairNearbyShits();
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
