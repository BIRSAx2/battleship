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
  static const std::map<std::string, CommandType> SPECIAL_COMMANDS_;

 public:
  /// Crea uno UserCommand a partire da un pair di Coordinates (origin, target) e un CommandType
  /// \param move
  /// \param command_type
  UserCommand(const std::pair<Coordinates, Coordinates> &move, CommandType command_type);
  /// Crea uno UserCommand a partire da un CommandType
  /// \param command_type
  explicit UserCommand(CommandType command_type);

  /// Crea uno UserCommand a partire da una stringa rappresentate il comando dell'utente. Se il comando è tra quelli speciali
  /// setta semplicemente la variabile di classe command_type_, altrimenti imposta command_type_ = MOVE e
  explicit UserCommand(const std::string &command);

  /// Restituisce true se questo oggetto rappresenta un comando speciale.
  bool IsSpecial() const { return command_type_ != MOVE; };

  /// Verifica se il comando passato è tra quelli speciali o meno.
  /// \param command
  /// \return true se command è comando considerato speciale, ovvero uno tra quelli presenti come chiave in SPECIAL_COMMANDS_, false altrimenti
  static bool IsSpecial(const std::string &command);
};

#endif//BATTAGLIA_NAVALE_INCLUDE_BATTLESHIP_USERCOMMAND_H_
