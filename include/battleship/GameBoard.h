#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_

#include "Board.h"
#include "Coordinates.h"
#include "Ship.h"
#include "Utility.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
class GameBoard : public Board {
 private:
  std::map<Coordinates, std::shared_ptr<Ship>> occupied_locations_;
  std::set<Coordinates> protected_coordinates_;
  int available_battleships = 3;

 public:
  GameBoard() : Board(12, 12){};

  /// Places a ship inside this board.
  /// \param bow The bow of the ship
  /// \param stern The stern of the ship
  /// \param ship The ship to place on the grid
  /// \return true if the ship was placed correctly, false if the ship could not be placed.
  /// May return false if the cells where the ship should be placed are already occupied or outside the board.
  bool PlaceShip(Coordinates bow, Coordinates stern, const Ship &ship);

  /// \param location
  /// \return  Returns a pointer to the ship contained in the location \p location, or <em> null_ptr </em> if the cell is empty
  std::shared_ptr<Ship> GetShipAt(Coordinates location);

  /// Changes this ship's bow and stern. Bow and stern are calculated using target as the ship's center cell.
  /// \param origin The central cell where the ship is contained
  /// \param target The center cell of the ship's new position.
  /// \return true if it was possible to change the ship's position, otherwise false.
  /// Returns false if the ship goes off the edge of board, or one of the destination cells are already occupied.
  bool MoveShip(Coordinates origin, Coordinates target);

  /// Handles an attack by an enemy ship. If the attack is successful returns true and marks the affected ship cell as attacked. Otherwise it returns false.
  /// \param target
  /// \return true: attack successful, false: attack unsuccessful.
  bool ReceiveAttack(Coordinates target);

  /// Checks that the \p ship does not overlaps any other ships in the board, and it's fully inside the board.
  /// \param ship
  /// \return true: if ship doesn't overlap any other ship and it's inside the board , false otherwise.
  bool CanPlaceShip(const Ship &ship) const;


  /// Checks that ship is within the bounds of board. Basically check that both ship.GetBow() and ship.GetStern() are inside borders.
  /// \param ship
  /// \return true: if the ship is within the margins, false: otherwise
  bool IsInsideBoard(const Ship &ship) const;
  std::string ToString() const;

  /// Returns all the occupied locations any ship
  /// \return  A map of pairs of coordinates and the ship at that position.
  const std::map<Coordinates, std::shared_ptr<Ship>> &GetOccupiedLocations() const;
  /// Remove the vessel from the board.. To get the coordinates where the ship is, it call the ship's GetLocations() method and eliminate them one by one.
  /// \param coordinates The center of the ship.
  void RemoveShip(Coordinates coordinates);

  /// Returns the coordinates of the bow and stern starting from those of the center. Ship is needed to get the width and orientation of the ship.
  /// \paramCenter
  /// \param ship
  /// \return
  std::pair<Coordinates, Coordinates> GetBowAndSternFromCenter(const Coordinates &center, const std::shared_ptr<Ship> &ship) const;

  /// Returns the number of active battleships in the board.
  int GetAvailableBattleships() const;
};

/// Prints the FiringBoard to \p os in the form of a grid  rows_ x columns_
std::ostream &operator<<(std::ostream &os, const GameBoard &board);

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
