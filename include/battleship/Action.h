#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_ACTION_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_ACTION_H_

#include "ActionType.h"
#include "Coordinates.h"
#include "Player.h"
#include <ostream>

class Action {
 private:
  Player player_;
  ActionType action_type_;
  Coordinates origin_;
  Coordinates destination_;

 public:
  Action();
  Action(const Player &player, ActionType action_type, const Coordinates &origin, const Coordinates &destination);
  Action(const Player &player, ActionType action_type, const Coordinates &origin);
  const Player &GetPlayer() const;
  void SetPlayer(const Player &player);
  ActionType GetActionType() const;
  void SetActionType(ActionType action_type);
  const Coordinates &GetOrigin() const;
  void SetOrigin(const Coordinates &origin);
  const Coordinates &GetDestination() const;
  void SetDestination(const Coordinates &destination);
  bool operator==(const Action &rhs) const;
  bool operator!=(const Action &rhs) const;

  friend std::ostream &operator<<(std::ostream &os, const Action &action);

};
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_ACTION_H_
