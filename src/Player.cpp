#include "Player.h"
std::string Player::ToString() const {

  std::string attack = firing_board_.ToString();

  return attack;
}
std::ostream &operator<<(std::ostream &os, const Player &player) {
  return os << player.ToString();
}
