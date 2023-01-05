#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_

#include "Battleship.h"
#include "FiringBoard.h"
#include "GameBoard.h"
#include "GameEngine.h"
#include "Submarine.h"
#include "SupportShip.h"
#include <iomanip>
#include <map>
#include <ostream>
#include <string>

#include <iostream>
#include <utility>
class Player {
 private:
  std::string name_;
  GameBoard game_board_;
  FiringBoard firing_board_;
  std::map<Coordinates, Ship> ships_;

 public:
  Player();
  explicit Player(std::string name);
  bool HasLost();
  bool PlaceShip(Ship ship, Coordinates coordinates);
  void PlaceShipsRandomly();
  std::string ToString();
  const std::string &GetName() const;
  GameBoard &GetGameBoard();
  FiringBoard &GetFiringBoard();
  std::map<Coordinates, Ship> &GetShips();
  bool operator==(const Player &rhs) const;
  bool operator!=(const Player &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, Player &player);
  bool MoveShip(Coordinates origin, Coordinates target, const Ship &ship_to_move);
  void AddPotentialTargets(Coordinates target);
  std::pair<Coordinates, Coordinates> GetRandomMove();
  void IncreaseShipHits(Coordinates target);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
