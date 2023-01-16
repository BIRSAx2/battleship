// Author: Mouhieddine Sabir

#include "GameRecorder.h"
#include "Battleship.h"
#include "Submarine.h"
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

  for (int i = 0; i < moves_.size(); ++i) {

	string_stream << moves_.at(i).first.ToUserCoordinates() << " " << moves_.at(i).second.ToUserCoordinates();
	if (i + 1 != moves_.size()) string_stream << "\n";
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
  std::string file_path = LOG_PATH + (game_mode_ == COMPUTER_VS_COMPUTER ? "cc" : "pc") + "_game_" + GetTimestamp() + ".txt";
  std::fstream log;

  // Executable launched from the build directory inside the root of the project
  log.open(file_path, std::ios::out);

  if (!log) {
	// Probably the executable has been launched from the root of the project

	file_path = file_path.substr(3, file_path.size());
	std::cout << file_path << std::endl;
	log.open(file_path, std::ios::out);
  }

  if (!log) {
	std::cout << "ERROR! Could not open the file " + file_path + " to save the current game\n";
	std::cout << "Please check if a directory named 'game_logs' exists in the root of the project, if it doesn't exit create it.\n";
	std::cout << "If it exists but you are still getting this error. Check that you running the executable from the build directory\n";
  }

  log << ToString();
  log.close();
}
void GameRecorder::LoadGameFromLog(const std::string &log_path) {

  player_a_ship_placement_.clear();
  player_b_ship_placement_.clear();
  moves_.clear();

  std::fstream game_log;
  game_log.open(log_path);

  if (!game_log) {
	std::cout << "ERROR! Could not open the file " + log_path + ", please check if the file exists" << std::endl;
  }

  std::string line;

  int starting_player;

  game_log >> starting_player;

  // Player A ships
  for (int i = 0; i < 8; ++i) {
	Coordinates bow, stern;
	int width;
	game_log >> bow;
	game_log >> stern;
	game_log >> width;
	player_a_ship_placement_.emplace(std::make_pair(bow, stern), width);
  }

  // Player B ships
  for (int i = 0; i < 8; ++i) {
	Coordinates bow, stern;
	int width;
	game_log >> bow;
	game_log >> stern;
	game_log >> width;
	player_b_ship_placement_.emplace(std::make_pair(bow, stern), width);
  }

  // Ready all the moves
  while (!game_log.eof()) {
	Coordinates origin, target;
	game_log >> origin;
	game_log >> target;
	RecordMove({origin, target});
  }
}

const std::map<std::pair<Coordinates, Coordinates>, int> &GameRecorder::GetPlayerAShipPlacement() const {
  return player_a_ship_placement_;
}
void GameRecorder::SetPlayerAShipPlacement(const std::map<std::pair<Coordinates, Coordinates>, int> &player_a_ship_placement) {
  player_a_ship_placement_ = player_a_ship_placement;
}
const std::map<std::pair<Coordinates, Coordinates>, int> &GameRecorder::GetPlayerBShipPlacement() const {
  return player_b_ship_placement_;
}
void GameRecorder::SetPlayerBShipPlacement(const std::map<std::pair<Coordinates, Coordinates>, int> &player_b_ship_placement) {
  player_b_ship_placement_ = player_b_ship_placement;
}
const std::vector<std::pair<Coordinates, Coordinates>> &GameRecorder::GetMoves() const {
  return moves_;
}
void GameRecorder::SetMoves(const std::vector<std::pair<Coordinates, Coordinates>> &moves) {
  moves_ = moves;
}
