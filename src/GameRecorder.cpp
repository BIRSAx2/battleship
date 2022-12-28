#include "GameRecorder.h"
const std::vector<Action> &GameRecorder::GetPlayerAActions() const {
  return player_a_actions_;
}
void GameRecorder::SetPlayerAActions(const std::vector<Action> &player_a_actions) {
  player_a_actions_ = player_a_actions;
}
const std::vector<Action> &GameRecorder::GetPlayerBActions() const {
  return player_b_actions_;
}
void GameRecorder::SetPlayerBActions(const std::vector<Action> &player_b_actions) {
  player_b_actions_ = player_b_actions;
}
const GameBoard &GameRecorder::GetPlayerAInitialBoard() const {
  return player_a_initial_board_;
}
void GameRecorder::SetPlayerAInitialBoard(const GameBoard &player_a_initial_board) {
  player_a_initial_board_ = player_a_initial_board;
}
const GameBoard &GameRecorder::GetPlayerBInitialBoard() const {
  return player_b_initial_board_;
}
void GameRecorder::SetPlayerBInitialBoard(const GameBoard &player_b_initial_board) {
  player_b_initial_board_ = player_b_initial_board;
}
GameRecorder::GameRecorder() {
}
GameRecorder::GameRecorder(GameBoard player_a_initial_board, GameBoard player_b_intial_board) {
}
void GameRecorder::RecordAction(Action action) {
}
void GameRecorder::RemoveLastAction() {
}
void GameRecorder::GetPlayerActions(Player player) {
}
void GameRecorder::SaveActionsToFile(std::string filePath) {
}
void GameRecorder::GetActionsFromFile(std::string filePath) {
}
