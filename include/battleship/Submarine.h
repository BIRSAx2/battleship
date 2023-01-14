#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_

#include "GameBoard.h"
#include "Player.h"
#include "Ship.h"
class Submarine : public Ship {
 public:
  static const int DEFAULT_SIZE = 1;
  /// Creates a Ship of type Submarine starting from the bow and stern. If the bow to stern distance does not match the vessel size, throw a std::invalid_argument
  /// \throws std::invali_argument
  /// \param bow The bow of the ship
  /// \param stern The stern of the ship
  Submarine(Coordinates bow, Coordinates stern) : Submarine() {
	bow_ = bow;
	stern_ = stern;
  };
  /// Creates a ship of type Submarine.
  Submarine() : Ship('E', DEFAULT_SIZE, 100) {
	ship_type_ = SUBMARINE;
  };


  /// Scans the the cells of the opponent's GameBoard the are in a 5 by 5 matrix with the \p current_position at the center.
  /// First it generates the needed surrounding coordinates and the users the \p InquireState() method from \p Player to get the state of the cell.
  /// \return a map of the scanned opponent's GameBoard.
  static std::map<Coordinates, OccupationType> ScanSurroundings(Player &opponent, Coordinates current_position);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SUBMARINE_H_
