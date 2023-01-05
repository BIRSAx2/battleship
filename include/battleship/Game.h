#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_

#include "Player.h"
#include <ostream>
#include <string>
class Game {
 private:
  Player player_a_;
  Player player_b_;

 public:
  Game();
  void PlaceShipsFromUser(const Player &player);
  static void PlaceShipsRandomly(Player &player);
  void Replay(std::string &file_path);
  friend std::ostream &operator<<(std::ostream &os, Game &game);
  static bool HandleAttack(Player &attacker, Player &opponent, Coordinates target);
  void PlayRandomGame();
  static void PlayMove(Player &player, Player &opponent, std::pair<Coordinates, Coordinates> move);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
