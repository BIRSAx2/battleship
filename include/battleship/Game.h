#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_

#include "GameEngine.h"
#include "GameRecorder.h"
#include "Player.h"
#include "Utility.h"
#include <ostream>
#include <string>
class Game {
 private:
  Player player_a_;
  Player player_b_;
  GameRecorder game_recorder_;
  GameEngine game_engine_;

 public:
  Game();
  Game(Player playerA, Player playerB);
  void PlaceShipsFromUser(const Player &player);
  static void PlaceShipsRandomly(Player &player);
  void Replay(const GameRecorder &game_recorder);
  const Player &GetPlayerA() const;
  void SetPlayerA(const Player &player_a);
  const Player &GetPlayerB() const;
  void SetPlayerB(const Player &player_b);
  const GameRecorder &GetGameRecorder() const;
  void SetGameRecorder(const GameRecorder &game_recorder);
  friend std::ostream &operator<<(std::ostream &os, Game &game);
  static bool HandleAttack(Player &attacker, Player &opponent, Coordinates target);
  void PlayRandomGame();
  void PlayUserVsUserGame();
  static void PlayMove(Player &player, Player &opponent, std::pair<Coordinates, Coordinates> move);
  void PlaceSubmarineFromUser(Player &player_a) const;
  void PlaceSupportshipFromUser(Player &player_a) const;
  void PlaceBattleshipFromUser(Player &player_a) const;
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
