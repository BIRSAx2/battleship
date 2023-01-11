#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_

#include "AsciiArt.h"
#include "Player.h"
#include "Submarine.h"
enum GameMode { COMPUTER_VS_COMPUTER,
				COMPUTER_VS_HUMAN,
				REPLAY };
class Game {
 private:
  Player player_a_;
  Player player_b_;
  GameMode game_mode_;

 public:
  Game();
  explicit Game(GameMode mode);
  void PlayGame();
  void PlayComputerVsComputerGame();
  void PlayComputerVsHumanGame();
  bool PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move);
  int ReadyChoiceFromUser(std::set<int> availble_choices);
  int ReadChoiceFromUser(const std::set<int> &availble_choices);
};
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
