#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_

#include "Coordinates.h"
#include "GameMode.h"
#include "Ship.h"
#include "Utility.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

class GameRecorder {
 private:
  std::map<std::pair<Coordinates, Coordinates>, int> player_a_ship_placement_;
  std::map<std::pair<Coordinates, Coordinates>, int> player_b_ship_placement_;
  std::vector<std::pair<Coordinates, Coordinates>> moves_;
  bool player_a_turn_;
  int starting_player_;
  GameMode game_mode_;

 public:
  static const std::string LOG_PATH;
  GameRecorder() : game_mode_(COMPUTER_VS_COMPUTER), player_a_turn_(false), starting_player_(0){};
  /// Creates a GameRecorder object base on the GameMode \p game_mode passed
  explicit GameRecorder(GameMode game_mode) : game_mode_(game_mode), player_a_turn_(false), starting_player_(0){};
  /// Records a ship placement to either \p player_a_ship_placement_ or \p player_a_ship_placement_ based on the value of player_a_turn.
  /// To record a ship placement to \p player_a_ship_placement_ set player_a_turn to true by calling \p SetIsPlayerATurn(), or set it to false to record the move to the other player.
  /// \param bow The bow of the ship placed
  /// \param stern The stern of the ship placed
  /// \param ship_with The ship's width
  void RecordShipPlacement(Coordinates bow, Coordinates stern, int ship_with);

  /// Records a move to the moves vector. There is no need to use \p SetIsPlayerATurn each time before recording a new move, the players takes turn making one move a time.
  /// \param move the move to record
  void RecordMove(std::pair<Coordinates, Coordinates> move);

  /// Given a plain text file path \p log_path, this method parses it's content and reads the starting player, player A's ship placement, player B's ship placement and the moves played.
  /// \param log_path The plain text file path from the executable root.
  void LoadGameFromLog(const std::string &log_path);
  /// Persists the contents of the internal variables to a plain text file.
  /// The generated file is named GAMEMODE_game_TIMESTAMP.txt
  /// GAMEMODE is either 'cc' or 'pc' based on \p game_mode_, 'cc' is computer vs computer, 'pc' is player vs computer
  /// TIMESTAMP is a timestamp in the format YYYYMMDDHHMMSS . See \c Utility::GetTimestamp().
  /// The directory where the file is saved is specified in \c GameRecorder::LOG_PATH
  void PersistGameToLog();
  /// Changes the turn
  /// \param is_player_a_turn: if true it's the player A's turn, false it's the player B's turn. See \c GameRecord::RecordShipPlacement() for it's usage.
  void SetIsPlayerATurn(bool is_player_a_turn);

  /// Returns which player start the game.
  /// \return 1: Player A, 2: Player B
  int GetStartingPlayer() const;
  /// Sets the starting player
  /// \param starting_player: 1: Player A starts, 2: Player B starts.
  void SetStartingPlayer(int starting_player);

  /// Returns the string representation of this object. This method to generate the contents of the log file to persist.
  /// The generated string follows the pattern: STARTING_PLAYER\\n\\nPLAYER_A_SHIP_PLACEMENT\\n\\nPLAYER_B_SHIP_PLACEMENT\\n\\nMOVES
  std::string ToString() const;
  /// Prints the string returned by \c ToString() to the output stream \p os
  friend std::ostream &operator<<(std::ostream &os, const GameRecorder &recorder);

  /// Returns the Player A's ship placement
  /// \return a map of a pair of coordinates (bow, stern) and a int (width)
  const std::map<std::pair<Coordinates, Coordinates>, int> &GetPlayerAShipPlacement() const;
  /// Returns the Player A's ship placement
  /// \return a map of a pairs of coordinates (bow, stern) and a int (width)
  const std::map<std::pair<Coordinates, Coordinates>, int> &GetPlayerBShipPlacement() const;

  /// Returns the moves played during the game
  /// \return a vector of pairs of coordinates (origin, target)
  const std::vector<std::pair<Coordinates, Coordinates>> &GetMoves() const;
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
