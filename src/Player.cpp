#include "Player.h"
std::string Player::ToString() const {

  return std::string();
}
std::ostream &operator<<(std::ostream &os, const Player &player) {
  return os << player.ToString();
}
