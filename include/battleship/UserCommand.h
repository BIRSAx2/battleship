#ifndef BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_
#define BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_

#include "Coordinates.h"
#include <map>

enum CommandType { MOVE,
				   SHOW_GRID,
				   CLEAR_SONAR,
				   CLEAR_ALL,
				   CLEAR_HIT,
				   CLEAR_MISS,
				   SHOW_COMMANDS_MENU };
class UserCommand {
  std::pair<Coordinates, Coordinates> move_;
  CommandType command_type_;
  static const std::map<std::string, CommandType> SPECIAL_COMMANDS_;

 public:
  UserCommand() { command_type_ = MOVE; };
  /// Creates a UserCommand from a pair of Coordinates (origin, target) and CommandType
  /// \param move A pair of Coordinates representing the origin and the target of a move.
  /// \param command_type The CommandType
  UserCommand(const std::pair<Coordinates, Coordinates> &move, CommandType command_type);

  /// Create a UserCommand from a CommandType
  /// \param command_type
  explicit UserCommand(CommandType command_type);

  /// Create a UserCommand from a string representing the user's command. If the \p command is one of te special commands (\p UserCommand::SPECIAL_COMMANDS_)
  /// it creates a UserCommand simply by setting the command_type, otherwise it tries to parse the string \p command and extract a pair of coordinates from it.
  /// Uses \p Coordinates(std::string) constructor for the parsing.
  /// \throws std::invalid_argument if the provided string is not a valid command.
  explicit UserCommand(const std::string &command);

  /// Checks whether this is a special command or not.
  /// @return true if it's a special command
  /// @return false if it's not
  bool IsSpecial() const { return command_type_ != MOVE; };

  /// Checks where the string passed is a special command.
  /// \param command
  /// \return true if \p command is one of the special commands defined in \p UserCommand::SPECIAL_COMMANDS_
  /// \return false if it's not a special command.
  static bool IsSpecial(const std::string &command);

  const std::pair<Coordinates, Coordinates> &GetMove() const;
  void SetMove(const std::pair<Coordinates, Coordinates> &move);
  CommandType GetCommandType() const;
  void SetCommandType(CommandType command_type);
};

#endif//BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_
