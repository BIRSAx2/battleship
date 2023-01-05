#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_OCCUPATIONTYPE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_OCCUPATIONTYPE_H_

#include <iostream>
enum OccupationType {
  EMPTY = 0,
  HIT,
  MISS,
  SUBMARINE,
  BATTLESHIP,
  SUPPORT_SHIP
};
// Definirla direttamente qui in linea visto che serve solo per il debug e verrà rimosso in futuro. Deve restituire il valore di occupation_type come string. Es. EMPTY -> "EMPTY"
inline std::ostream &operator<<(std::ostream &os, OccupationType occupation_type);

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_OCCUPATIONTYPE_H_

