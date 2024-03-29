#include "UserCommand.h"

const std::map<std::string, CommandType> UserCommand::SPECIAL_COMMANDS_ =
	{{"AA AA", CLEAR_SONAR}, {"XX XX", SHOW_GRID}, {"BB BB", CLEAR_HIT}, {"CC CC", CLEAR_MISS}, {"DD DD", CLEAR_ALL}, {{"SS SS"}, SHOW_COMMANDS_MENU}};

UserCommand::UserCommand(const std::pair<Coordinates, Coordinates> &move, CommandType command_type) {
  move_ = move;
  command_type_ = command_type;
}
UserCommand::UserCommand(CommandType command_type) : command_type_(command_type) {
}


UserCommand::UserCommand(const std::string &command) {
  auto special_command = SPECIAL_COMMANDS_.find(command);
  if (special_command != SPECIAL_COMMANDS_.end()) {
	command_type_ = special_command->second;
  } else {
	command_type_ = MOVE;
	std::vector<std::string> splitCommand = Split(command, ' ');
	move_ = std::make_pair(Coordinates(splitCommand[0]), Coordinates(splitCommand[1]));
  }
}

bool UserCommand::IsSpecial(const std::string &command) {
  return SPECIAL_COMMANDS_.count(command) != 0;
}
const std::pair<Coordinates, Coordinates> &UserCommand::GetMove() const {
  return move_;
}
void UserCommand::SetMove(const std::pair<Coordinates, Coordinates> &move) {
  move_ = move;
}
CommandType UserCommand::GetCommandType() const {
  return command_type_;
}
void UserCommand::SetCommandType(CommandType command_type) {
  command_type_ = command_type;
}
