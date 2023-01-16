#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_

#include "GameBoard.h"
#include "Player.h"
#include "Ship.h"
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

  /// Creates a ship of type SupportShip.
  /// \throws std::invali_argument
  /// \param bow The bow of the ship
  /// \param stern The stern of the ship
  SupportShip() : Ship('S', DEFAULT_SIZE, 106) {
	ship_type_ = SUPPORTSHIP;
  };

  /// Repairs all the \p player's hips in a range of 3 from the current position
  static void RepairNearbyShips(Player &player, Coordinates current_position);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUPPORTSHIP_H_
