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

 public:
  GameBoard() : Board(12, 12){};

  ///
  /// \param bow La prua della nave
  /// \param stern La poppa della nave
  /// \param ship La nave da posizionare sulla griglia
  /// \return true se la nave è stata posizionata correttamente, false se non è stato possibile posizionare la nave.
  /// Può restituire false se le celle dove andrebbe posizionata la nave sono già occupate oppure si trovano fuori dalla griglia.
  bool PlaceShip(Coordinates bow, Coordinates stern, const Ship &ship);

  /// \param location
  /// \return  Restituisce un puntatore alla nave contenuta nella cella location, oppure null_ptr se la cella è vuota
  std::shared_ptr<Ship> GetShipAt(Coordinates location);

  /// Cambia la prua e poppa di questa nave a partire da target. La prua e la poppa sono calcolate utilizzando target come cella centrale della nave.
  ///
  /// \param origin La cella centrale dove la nave è contenuta
  /// \param target La cella centrale della nuova posizione della nave.
  /// \return true nel caso sia stato possibile cambiare posizione della nave, altrimenti false.
  /// Restituisce false se la nave va fuori dai bordi del campo di gioco, oppure le celle di destinazione sono già occupate.

  bool MoveShip(Coordinates origin, Coordinates target);

  /// Stampa il contenuto di GameBoard sotto forma di griglia rows_ x columns_

  friend std::ostream &operator<<(std::ostream &os, const GameBoard &board);

  /// Gestisce l'attacco da parte di una nave nemica. In caso di successo, restituisce true, e segna la cella interessata della nave come attaccata. Altrimenti restiuisce false.
  /// \param target
  /// \return true: attacco andato a buon fine, false: attacco andato a vuoto.
  bool ReceiveAttack(Coordinates target);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
