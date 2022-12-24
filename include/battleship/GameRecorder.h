#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
#include "Action.h"
#include "GameBoard.h"
#include <string>
#include <vector>

class GameRecorder {

 private:
  std::vector<Action> player_a_actions_;
  std::vector<Action> player_b_actions_;
  GameBoard player_a_initial_board_;
  GameBoard player_b_initial_board_;

 public:
  GameRecorder();
  GameRecorder(GameBoard player_a_initial_board, GameBoard player_b_intial_board);
  void RecordAction(Action action);
  void RemoveLastAction();
  void GetPlayerActions(Player player);
  const std::vector<Action> &GetPlayerAActions() const;
  void SetPlayerAActions(const std::vector<Action> &player_a_actions);
  const std::vector<Action> &GetPlayerBActions() const;
  void SetPlayerBActions(const std::vector<Action> &player_b_actions);
  const GameBoard &GetPlayerAInitialBoard() const;
  void SetPlayerAInitialBoard(const GameBoard &player_a_initial_board);
  const GameBoard &GetPlayerBInitialBoard() const;
  void SetPlayerBInitialBoard(const GameBoard &player_b_initial_board);

  void SaveActionsToFile(std::string filePath);
  void GetActionsFromFile(std::string filePath);

};
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMERECORDER_H_
