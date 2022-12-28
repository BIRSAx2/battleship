#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_ORIENTATION_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_ORIENTATION_H_

#include <iostream>
enum Orientation {
  HORIZONTAL = 0,
  VERTICAL,
  UNSET
};

inline std::ostream &operator<<(std::ostream &os, Orientation orientation) {
  switch (orientation) {
	case HORIZONTAL: return os << "HORIZONTAL";
	case VERTICAL: return os << "VERTICAL";
	case UNSET: return os << "UNSET";
  }
  return os;
}
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_ORIENTATION_H_
