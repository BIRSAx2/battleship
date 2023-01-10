#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_

#include <iomanip>
#include <ostream>

#include "FiringBoard.h"
#include "GameBoard.h"
#include "Utility.h"

class Player {
 private:
  std::string name_;
  GameBoard game_board_;
  FiringBoard firing_board_;
  int alive_battleships_ = 3;

  // This variables are used to avoid shooting randomly
  std::set<Coordinates> next_targets_;

 public:
  Player(std::string name) : name_(std::move(name)){};
  /// Posiziona una ship date le coordinate di prua e poppa
  /// \param bow Le coordinate della prua
  /// \param stern Le coordinate della poppa
  /// \param ship La nave da posizionare.
  /// \return
  bool PlaceShip(Coordinates bow, Coordinates stern, Ship &ship);
  /// Effettua una mossa di gioco.
  /// \param origin Le coordinate centrali della nave presa in considerazione.
  /// \param target Le coordinate da colpire nel caso la nave sia una Battleship, o quelle dove muoversi e cercare/coprire nel caso delle altre navi.
  /// \return true: se è stato possibile giocare la mossa, false altrimenti.
  bool PlayMove(Coordinates origin, Coordinates target);

  /// Posiziona le navi in modo randomico sulla griglia.
  void PlaceShipsRandomly();

  /// Restituisce la griglia di attacco e di difesa fianco affianco.
  std::string ToString() const;
  /// Utilizza il metodo ToString() per stampare su os le griglie di gioco.
  friend std::ostream &operator<<(std::ostream &os, const Player &player);
  std::pair<Coordinates, Coordinates> GetRandomShipPlacement(int ship_width) const;
  std::pair<Coordinates, Coordinates> GenerateRandomMove();
  std::shared_ptr<Ship> GetShipAt(Coordinates location);
  bool ReceiveAttack(Coordinates coordinates);
  void MarkAttack(Coordinates coordinates, bool b);
  bool MoveShip(Coordinates origin, Coordinates target);

  const std::string &GetName() const;
  void SetName(const std::string &name);
  Coordinates GetNextTarget();
  void AddNextTargets(Coordinates coordinates);
  OccupationType InquireState(Coordinates coordinates);
  void UpdateSubmarineSightings(std::map<Coordinates, OccupationType> scan_from_submarine);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
