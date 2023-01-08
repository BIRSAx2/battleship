#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_

#include <ostream>
#include <utility>

#include "FiringBoard.h"
#include "GameBoard.h"
class Player {
 private:
  std::string name_;
  GameBoard game_board_;
  FiringBoard firing_board_;
  int alive_battleships_ = 3;

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
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_PLAYER_H_
