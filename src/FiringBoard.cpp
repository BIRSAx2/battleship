#include "FiringBoard.h"
#include "Utility.h"
void FiringBoard::MarkAttack(Coordinates target, bool is_hit) {
  tiles_[target] = is_hit ? HIT : MISS;
}
void FiringBoard::ClearSubmarineSightings() {
  for (auto it = tiles_.begin(); it != tiles_.end();) {
	(it->second == OCCUPIED) ? tiles_.erase(it++) : (++it);
  }
}
void FiringBoard::Clear() {
  tiles_.clear();
}
std::ostream &operator<<(std::ostream &os, const FiringBoard &board) {
  std::string horizontal_legend = "  1  2  3  4  5  6  7  8  9  10 11 12";

  std::string arr[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N"};
  int legend = 0;
  os << ColourText256(horizontal_legend, 8) << "\n";

  for (int i = 0; i < board.GetRows(); ++i) {
	os << ColourText256(std::string(arr[legend]), 8) << " ";
	for (int j = 0; j < board.GetCols(); ++j) {

	  if (board.tiles_.count({i, j}) != 0) os << board.tiles_.at({i, j}) << "  ";
	  else {
		os << ColourText256("~", 87) << "  ";
	  }
	}
	os << ColourText256(std::string(arr[legend]), 8) << "\n";
	legend++;
  }
  return os << ColourText256(horizontal_legend, 8) << "\n";
}
std::ostream &operator<<(std::ostream &os, OccupationType cat) {
  switch (cat) {
	case EMPTY: os << "~"; break;
	case HIT: os << ColourText256("X", 1); break;
	case MISS: os << ColourText256("O", 220); break;
	case OCCUPIED: os << ColourText256("Y", 100); break;
  }
  return os;
}
