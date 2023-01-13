#ifndef BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_
#define BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_

#include "Coordinates.h"
#include <map>

enum CommandType { MOVE,
				   SHOW_GRID,
				   CLEAR_SONAR,
				   CLEAR_ALL,
				   CLEAR_HIT,
				   CLEAR_MISS };
class UserCommand {
  std::pair<Coordinates, Coordinates> move_;
  CommandType command_type_;

 public:
  UserCommand(const std::pair<Coordinates, Coordinates> &move, CommandType command_type);
  explicit UserCommand(CommandType command_type);
  explicit UserCommand(const std::string &command);
  bool IsSpecial() const { return command_type_ != MOVE; };
  static bool IsSpecial(std::string &command);
};

#endif//BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_
