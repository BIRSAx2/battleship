#include "Game.h"
#include "GameMode.h"
#include "GameRecorder.h"
#include "Utility.h"
#include <iostream>
#include <regex>

void persistReplayToFile(std::string file_path);
int main(int argc, char **argv) {

  std::regex ansi_escape_start("\\\033\\[\\d+;\\d+;\\d+m");
  std::regex ansi_escape_end("\\\033\\[m");

  std::string usage = "Usage:\n 'replay v path/to/log_file' to watch the replay of game on terminal\n 'replay f path/to/log_file path/to/output_file' to print the replay of a game to an output file";
  // Command line arguments validation

  if (argc != 3 && argc != 4) {
	std::cout << ColourText256("Invalid command line arguments!", 1) << std::endl;
	std::cout << usage << std::endl;
	return 1;
  }

  std::string replay_mode = argv[1];

  std::string path_log_file, path_to_output_file;
  if (replay_mode == "v") {
	// replay on screen
	path_log_file = argv[2];
  }

  std::string path_output_file;
  if (replay_mode == "f") {
	path_log_file = argv[2];
	path_output_file = argv[3];
  }

  GameRecorder game_recorder = GameRecorder();
  game_recorder.LoadGameFromLog(path_log_file);

  Game game = Game(game_recorder);

  std::string replay = game.Replay(replay_mode == "v");

  // Stripping out ANSI escape codes to be able to persist it to a file
  replay = std::regex_replace(std::regex_replace(replay, ansi_escape_start, ""), ansi_escape_end, "");
  if (replay_mode == "f") {

	std::fstream log;
	log.open(path_output_file, std::ios::out);
	if (!log) {
	  std::cout << "ERROR! Could not open the file " + path_output_file + " to save the game replay" << std::endl;
	}

	log << replay;
	log.close();
  }

  return 0;
}