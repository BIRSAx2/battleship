#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_OCCUPATIONTYPE_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_OCCUPATIONTYPE_H_

#include <iostream>
enum OccupationType {
  EMPTY = 0,
  HIT,
  MISS,
  SUBMARINE,
  BATTLESHIP,
  SUPPORT_BATTLESHIP
};

inline std::ostream &operator<<(std::ostream &os, OccupationType occupation_type) {
  switch (occupation_type) {
	case EMPTY: return os << "EMPTY";
	case HIT: return os << "HIT";
	case MISS: return os << "MISS";
	case SUBMARINE: return os << "SUBMARINE";
	case BATTLESHIP: return os << "BATTLESHIP";
	case SUPPORT_BATTLESHIP:
	  return os << "SUPPORT_BATTLESHIP";
	default: return os << (int)occupation_type;
  }
}
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_OCCUPATIONTYPE_H_
