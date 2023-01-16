#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_

#include <iomanip>
#include <ostream>

#include "FiringBoard.h"
#include "GameBoard.h"
#include "GameRecorder.h"
#include "Utility.h"

class Player {
 private:
  std::string name_;
  GameBoard game_board_;
  FiringBoard firing_board_;
  bool is_human_;

  // This variables are used to avoid shooting randomly
  std::set<Coordinates> next_targets_;

 public:
  Player(std::string name, bool is_human = false) : name_(std::move(name)), is_human_(is_human){};

  /// Positions a ship given the bow and stern coordinates
  /// \param bow The coordinates of the bow
  /// \param stern The coordinates of the stern
  /// \param ship The ship to position.
  /// \return true if the ship has been placed successfully
  /// \return false if the ship has not been placed successfully
  bool PlaceShip(Coordinates bow, Coordinates stern, Ship &ship);

  /// Makes a game move.
  /// \param origin The central coordinates of the ship .
  /// \param target The target coordinates to hit if the ship is a Battleship, or where to move and search/cover in the case of other ships.
  /// \return true if the move could be played
  /// \return false otherwise.
  bool PlayMove(Coordinates origin, Coordinates target);

  /// Places the ships randomly on on the board.
  /// \param game_recorder The game recorder used to record the placements of the ships.
  void PlaceShipsRandomly(GameRecorder &game_recorder);

  /// Returns a string containing a string representation of GameBoard and FiringBoard side by side.
  std::string ToString() const;

  /// Generates a random ship placement for a ship with width \p ship_width
  /// \param ship_width
  /// \return Pair of coordinates (bow, stern)
  std::pair<Coordinates, Coordinates> GetRandomShipPlacement(int ship_width) const;

  /// Generates a random move composed of a pair of coordinates (origin, target). Origin is the central cell of one of the ships placed in GameBoard.
  /// Target is generated randomly if the ship at origin is not a Battleship, or using GetNextTarget() if it's a battleship.
  /// \return
  std::pair<Coordinates, Coordinates> GenerateRandomMove();

  /// This is a helper method to call GameBoard.GetShipAt without exposing the object GameBoard.
  std::shared_ptr<Ship> GetShipAt(Coordinates location);
  /// This is a helper method to call GameBoard.ReceiveAttack without exposing the object GameBoard.
  bool ReceiveAttack(Coordinates coordinates);

  /// This is a helper method to call FiringBoard.ReceiveAttack without exposing the object FiringBoard.
  void MarkAttack(Coordinates coordinates, bool b);

/// This is a helper method to call GameBoard.PlaceShip without exposing the object GameBoard.
  bool MoveShip(Coordinates origin, Coordinates target);

  /// Returns the name of the current player.
  /// \return
  const std::string &GetName() const;

  /// Returns the coordinates for the next target for the Battleship to shoot at.
  /// The next target is picked between a set of next targets that gets updated each time
  /// a successful hit is made with the adjacent coordinates.
  /// The set of next targets gets also updated each a time a submarine detects enemy ships.
  /// If the set is empty, it returns a random target.
  Coordinates GetNextTarget();

  /// Adds the Coordinates.GetAdjacentStartCoordinates to the set of next targets.
  /// The idea behind this is that every time we hit an enemy ship there is a high chance that the remaining
  /// parts of that ship are either above, below, right or left from the hit coordinate.
  /// \param coordinates
  void AddNextTargets(Coordinates coordinates);

  /// This is a helper method to avoid exposing the internal GameBoard to the caller (usually an enemy submarine).
  /// \param coordinates
  /// \return It returns the occupation type of the cell \p target,\p OCCUPIED at \p target a part of a ship is present but not hit,
  /// \p HIT if a part of a ship is present and hit or \p EMPTY if nothing is present there.
  OccupationType InquireState(Coordinates target);

  /// This is a helper method to avoid exposing the internal FiringBoard to the caller.
  /// It calls FiringBoard.AddSubmarineSightings
  void AddSubmarineSightings(const std::map<Coordinates, OccupationType> &scan_from_submarine);

  /// This a helper method to avoid exposing the internal FiringBoard to the caller. It calls the ClearSubmarineSightings() method of FiringBoard.
  void ClearSubmarineSightings();

  /// This a helper method to avoid exposing the internal FiringBoard to the caller. It calls the ClearSuccessfulHits() method of FiringBoard.
  void ClearSuccessfulHits();

  /// This a helper method to avoid exposing the internal FiringBoard to the caller. It calls the ClearUnsuccessfulHits() method of FiringBoard.
  void ClearUnsuccessfulHits();

  /// This a helper method to avoid exposing the internal FiringBoard to the caller. It calls the ClearAllHits() method of FiringBoard.
  void ClearAllHits();

  /// This methods add all coordinates present in \p submarine_sightings to the set of next targets.
  /// The idea behind this is that every time a submarine detects an enemy ship at some coordinates there is a high chance that the ship
  /// has not moved yet by the time GetNextTarget() is called, so it makes sense to try to shoot there.
  void AddNextTargets(const std::map<Coordinates, OccupationType>& submarine_sightings);

  /// A player loses when all of his Battleships are destroyed.
  bool HasLost();

  bool IsHuman() const { return is_human_; };

  /// A helper method that returns the string representation of the internal GameBoard, obtained by calling the GameBoard.ToString().
  /// It is used during the placement of the various ships.
  /// \return a string representation of the internal GameBoard.
  std::string GameBoardToString() const { return game_board_.ToString(); };


  /// Clears all the hits received by the ship at 
  void RepairShipAt(Coordinates coordinates);
};

/// Uses the \p ToString() method to print to the output stream \p os the boards of the player.
std::ostream &operator<<(std::ostream &os, const Player &player);
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
