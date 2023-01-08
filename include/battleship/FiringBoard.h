#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_

#include "Board.h"
#include "GameBoard.h"
#include <ostream>

enum OccupationType { EMPTY,
					  HIT,
					  MISS,
					  OCCUPIED };

std::ostream &operator<<(std::ostream &os, OccupationType cat);
class FiringBoard : public Board {
 private:
  std::map<Coordinates, OccupationType> tiles_;

 public:
  FiringBoard() : Board(12, 12){};
  /// Segna la cella target, quella sotto attacco, con il risultato dell'attacco (is_hit). Se is_hit è true, la cella corrispondente viene segnata con il valore HIT, altrimenti come MISS.
  /// \param target La cella sotto attacco
  /// \param is_hit true: successo, false: attacco fallito.
  void MarkAttack(Coordinates target, bool is_hit);

  /// Elimina tutti gli avvistamenti del sottomarino (occupation_type = OCCUPIED)
  void ClearSubmarineSightings();

  // Elimina sia gli avvistamenti del sottomarino che i vari risultati degli attacchi.
  void Clear();

  /// Stampa il contenuto di GameBoard sotto forma di griglia rows_ x columns_
  friend std::ostream &operator<<(std::ostream &os, const FiringBoard &board);
  std::string ToString() const;
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
