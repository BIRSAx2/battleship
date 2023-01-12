#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_

#include "Coordinates.h"
#include "Ship.h"
#include "Utility.h"
#include <ctime>
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

 public:
  static const std::string LOG_PATH;
  GameRecorder() {
	player_a_turn_ = false;
	starting_player_ = 0;
  };
  void RecordShipPlacement(Coordinates bow, Coordinates stern, int ship_with);
  void RecordMove(std::pair<Coordinates, Coordinates> move);
  void LoadGameFromLog(std::string log_path);
  void PersistGameToLog();
  std::vector<std::string> GetGameLogs();
  bool IsPlayerATurn() const;
  void SetIsPlayerATurn(bool is_player_a_turn);
  int GetStartingPlayer() const;
  void SetStartingPlayer(int starting_player);
  std::string ToString() const;
  friend std::ostream &operator<<(std::ostream &os, const GameRecorder &recorder);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
