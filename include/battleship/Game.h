#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_

#include "GameRecorder.h"
#include "Player.h"
#include <ostream>
#include <string>
class Game {
 private:
  Player playerA_;
  Player playerB_;
  GameRecorder game_recorder_;

 public:
  Game();
  Game(Player playerA, Player playerB);
  void PlaceShipsFromUser(Player player);
  void PlaceShipsRandomly(Player player);
  void PlayRound();
  void PlayToEnd();
  void Replay(GameRecorder game_recorder);
  const Player &GetPlayerA() const;
  void SetPlayerA(const Player &player_a);
  const Player &GetPlayerB() const;
  void SetPlayerB(const Player &player_b);
  const GameRecorder &GetGameRecorder() const;
  void SetGameRecorder(const GameRecorder &game_recorder);
  friend std::ostream &operator<<(std::ostream &os, const Game &game);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
