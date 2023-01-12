#include "GameRecorder.h"
#include "Utility.h"

const std::string GameRecorder::LOG_PATH = "../game_logs/";

bool GameRecorder::IsPlayerATurn() const {
  return player_a_turn_;
}
void GameRecorder::SetIsPlayerATurn(bool is_player_a_turn) {
  GameRecorder::player_a_turn_ = is_player_a_turn;
}
void GameRecorder::RecordShipPlacement(Coordinates bow, Coordinates stern, int ship_with) {

  if (player_a_turn_) {
	player_a_ship_placement_.emplace(std::make_pair(bow, stern), ship_with);
  } else {
	player_b_ship_placement_.emplace(std::make_pair(bow, stern), ship_with);
  }
}
void GameRecorder::RecordMove(std::pair<Coordinates, Coordinates> move) {
  moves_.emplace_back(move);
}
std::string GameRecorder::ToString() const {
  std::stringstream string_stream;
  // Starting player
  string_stream << starting_player_ << '\n';
  string_stream << "\n\n";

  // Print Player A ship placement

  for (auto placement : player_a_ship_placement_) {
	string_stream << placement.first.first.ToUserCoordinates() << " " << placement.first.second.ToUserCoordinates() << " " << placement.second << '\n';
  }

  string_stream << "\n\n";
  // Print Player B ship placement

  for (auto placement : player_b_ship_placement_) {
	string_stream << placement.first.first.ToUserCoordinates() << " " << placement.first.second.ToUserCoordinates() << " " << placement.second << '\n';
  }
  string_stream << "\n\n";

  // Print all the moves

  for (auto move : moves_) {
	string_stream << move.first.ToUserCoordinates() << " " << move.second.ToUserCoordinates() << '\n';
  }

  return string_stream.str();
}
std::ostream &operator<<(std::ostream &os, const GameRecorder &recorder) {
  return os << recorder.ToString();
}
int GameRecorder::GetStartingPlayer() const {
  return starting_player_;
}
void GameRecorder::SetStartingPlayer(int starting_player) {
  starting_player_ = starting_player;
}

void GameRecorder::PersistGameToLog() {
  std::string file_path = LOG_PATH + "game_" + GetTimestamp() + ".txt";
  std::fstream log;
  log.open(file_path, std::ios::out);
  if (!log) {
	std::cout << "ERROR! Could not open the file " + file_path + " to save the current game" << std::endl;
	std::cout << "Please check if a directory named 'game_logs' exists in the root of the project, if it doesn't exit create it.";
  }

  log << ToString();
  log.close();
}
std::vector<std::string> GameRecorder::GetGameLogs() {

  //
  return std::vector<std::string>();
}
