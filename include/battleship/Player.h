#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_

#include "Battleship.h"
#include "FiringBoard.h"
#include "GameBoard.h"
#include "Submarine.h"
#include "SupportShip.h"
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
  void PlaceShips(std::map<Coordinates, Ship> ships);
  bool PlaceShip(const Ship& ship, Coordinates coordinates);
  void PlaceShipsRandomly();
  std::string ToString() const;
  const std::string &GetName() const;
  void SetName(const std::string &name);
  GameBoard &GetGameBoard();
  bool HandleAttack(Coordinates target);
  void SetGameBoard(const GameBoard &game_board);
  FiringBoard &GetFiringBoard();
  void SetFiringBoard(const FiringBoard &firing_board);
  const std::map<Coordinates, Ship> &GetShips() const;
  void SetShips(const std::map<Coordinates, Ship> &ships);
  bool operator==(const Player &rhs) const;
  bool operator!=(const Player &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const Player &player);
  std::pair<Coordinates, Orientation> GetRandomShipPosition(int ship_width);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
