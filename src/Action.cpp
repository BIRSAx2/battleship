#include "Action.h"
Action::Action(const Player &player, ActionType action_type, const Coordinates &origin, const Coordinates &destination) : player_(player), action_type_(action_type), origin_(origin), destination_(destination) {}
Action::Action(const Player &player, ActionType action_type, const Coordinates &origin) : player_(player), action_type_(action_type), origin_(origin) {}
const Player &Action::GetPlayer() const {
  return player_;
}
void Action::SetPlayer(const Player &player) {
  player_ = player;
}
ActionType Action::GetActionType() const {
  return action_type_;
}
void Action::SetActionType(ActionType action_type) {
  action_type_ = action_type;
}
const Coordinates &Action::GetOrigin() const {
  return origin_;
}
void Action::SetOrigin(const Coordinates &origin) {
  origin_ = origin;
}
const Coordinates &Action::GetDestination() const {
  return destination_;
}
void Action::SetDestination(const Coordinates &destination) {
  destination_ = destination;
}
//bool Action::operator==(const Action &rhs) const {
//  return player_ == rhs.player_ && action_type_ == rhs.action_type_ && origin_ == rhs.origin_ && destination_ == rhs.destination_;
//}
//bool Action::operator!=(const Action &rhs) const {
//  return !(rhs == *this);
//}
//std::ostream &operator<<(std::ostream &os, Action &action) {
//  os << "player_: " << action.GetPlayer() << " action_type_: " << action.GetActionType() << " origin_: " << action.GetOrigin() << " destination_: " << action.GetDestination();
//  return os;
//}
