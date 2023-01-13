#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_

#include "AsciiArt.h"
#include "GameRecorder.h"
#include "Player.h"
#include "Submarine.h"
#include "Battleship.h"
#include <thread>
#include <chrono>
#include <tuple>

enum GameMode { COMPUTER_VS_COMPUTER,
				COMPUTER_VS_HUMAN,
				REPLAY };
class Game {
 private:
  Player player_b_;
  // By convention the player_b_ in the games COMPUTER_VS_HUMAN is the human player.
  Player player_a_;
  GameMode game_mode_;
  GameRecorder game_recorder_;

 public:
  Game();
  explicit Game(GameMode mode);
  void PlayGame();
  void PlayComputerVsComputerGame();
  void PlayComputerVsHumanGame();
  bool PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move);
  static int ReadChoiceFromUser(const std::set<int> &available_choices);
  void PlaceShipsFromUser(Player &player);
  UserCommand GetUserCommand(const std::string &promt);
  bool AttemptToPlaceAShip(Player &player, std::pair<Coordinates, Coordinates> bow_stern, Ship &ship);
};
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
