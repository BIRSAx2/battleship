#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_

#include "FiringBoard.h"
#include "GameBoard.h"
#include <map>
#include <ostream>
#include <string>
class Player {
 private:
  std::string name_;
  GameBoard game_board_;
  FiringBoard firing_board_;
  std::map<Coordinates, Ship> ships_;

 public:
  Player();
  Player(std::string name);
  bool HasLost();
  void PlaceShips(std::map<Coordinates, Ship> ships);
  void PlaceShip(Ship ship, Coordinates coordinates);
  void PlaceShipsRandomly(std::map<Ship, int> numberOfShips);
  std::string ToString();
  const std::string &GetName() const;
  void SetName(const std::string &name);
  const GameBoard &GetGameBoard() const;
  void SetGameBoard(const GameBoard &game_board);
  const FiringBoard &GetFiringBoard() const;
  void SetFiringBoard(const FiringBoard &firing_board);
  const std::map<Coordinates, Ship> &GetShips() const;
  void SetShips(const std::map<Coordinates, Ship> &ships);
  bool operator==(const Player &rhs) const;
  bool operator!=(const Player &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const Player &player);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
