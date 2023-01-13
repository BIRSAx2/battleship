#include "UserCommand.h"

const std::map<std::string, CommandType> UserCommand::SPECIAL_COMMANDS_ =
	{{"AA AA", CLEAR_SONAR}, {"XX XX", SHOW_GRID}, {"BB BB", CLEAR_HIT}, {"CC CC", CLEAR_MISS}, {"DD DD", CLEAR_ALL}};

UserCommand::UserCommand(const std::pair<Coordinates, Coordinates> &move, CommandType command_type) : move_(move), command_type_(command_type) {}

UserCommand::UserCommand(CommandType command_type) : command_type_(command_type) {}

UserCommand::UserCommand(const std::string &command) {
  auto special_command = SPECIAL_COMMANDS_.find(command);
  if (special_command != SPECIAL_COMMANDS_.end()) {
    command_type_ = special_command->second;
  } else {
    command_type_ = MOVE;
    std::string temp_string_1(command.substr(0, 2));
    std::string temp_string_2(command.substr(2, 2));
    move_ = std::make_pair(Coordinates(temp_string_1), Coordinates(temp_string_2));
  }
}

bool UserCommand::IsSpecial(const std::string &command) {
  return SPECIAL_COMMANDS_.find(command) != SPECIAL_COMMANDS_.end();
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
