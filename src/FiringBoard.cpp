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
  return os << board.ToString();
}

std::string FiringBoard::ToString() const {
  std::stringstream os;
  std::string horizontal_legend = "  1  2  3  4  5  6  7  8  9  10 11 12";

  std::string vertical_legend[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "L", "M", "N"};
  int legend = 0;
  os << ColourText256(horizontal_legend, 8) << "\n";

  for (int i = 0; i < GetRows(); ++i) {
	os << ColourText256(std::string(vertical_legend[legend]), 8) << " ";
	for (int j = 0; j < GetCols(); ++j) {

	  if (tiles_.count({i, j}) != 0) os << tiles_.at({i, j}) << "  ";
	  else {
		os << ColourText256("~", 87) << "  ";
	  }
	}
	os << ColourText256(std::string(vertical_legend[legend]), 8) << "\n";
	legend++;
  }
  os << ColourText256(horizontal_legend, 8) << "\n";
  return os.str();
}
bool FiringBoard::HasBeenAttacked(Coordinates target) {
  return tiles_.count(target) != 0;
}
void FiringBoard::AddSubmarineSightings(const std::map<Coordinates, OccupationType> &sightings) {

  // TODO: We could ignore empty ones
  for (auto pair : sightings) {
	tiles_[pair.first] = pair.second;
  }
}

std::ostream &operator<<(std::ostream &os, OccupationType cat) {
  switch (cat) {
	case EMPTY: os << ColourText256("~", 87); break;
	case HIT: os << ColourText256("X", 1); break;
	case MISS: os << ColourText256("O", 220); break;
	case OCCUPIED: os << ColourText256("Y", 100); break;
  }
  return os;
}
