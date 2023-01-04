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
  GameEngine game_engine_;
  std::map<Coordinates, Ship> ships_;

 public:
  Player();
  explicit Player(std::string name);
  bool HasLost();
  void PlaceShips(const std::map<Coordinates, Ship> &ships);
  bool PlaceShip(const Ship &ship, Coordinates coordinates);
  void PlaceShipsRandomly();
  std::string ToString();
  const std::string &GetName() const;
  void SetName(const std::string &name);
  GameBoard &GetGameBoard();
  GameEngine &GetGameEngine();
  bool HandleAttack(Coordinates target);
  void SetGameBoard(const GameBoard &game_board);
  FiringBoard &GetFiringBoard();
  void SetFiringBoard(const FiringBoard &firing_board);
  std::map<Coordinates, Ship> &GetShips();
  void SetShips(const std::map<Coordinates, Ship> &ships);
  bool operator==(const Player &rhs) const;
  bool operator!=(const Player &rhs) const;
  friend std::ostream &operator<<(std::ostream &os,  Player &player);
  bool MoveShip(Coordinates origin, Coordinates target, const Ship &ship_to_move);
  void AddPotentialTargets(Coordinates target);
  std::pair<Coordinates, Coordinates> GetRandomMove();
  void IncreaseShipHits(Coordinates target);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
