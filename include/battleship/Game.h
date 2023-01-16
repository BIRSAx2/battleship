#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_

#include "AsciiArt.h"
#include "GameRecorder.h"
#include "Player.h"
#include "Submarine.h"
#include "SupportShip.h"
#include "Battleship.h"
#include "UserCommand.h"
#include <thread>
#include <chrono>
#include <tuple>

enum GameMode { COMPUTER_VS_COMPUTER,
				COMPUTER_VS_HUMAN,
				REPLAY };
class Game {
 private:
  const int MAX_ROUNDS = 100;
  Player player_b_;
  // By convention the player_b_ in the games COMPUTER_VS_HUMAN is the human player.
  Player player_a_;
  GameMode game_mode_;
  GameRecorder game_recorder_;

 public:

  /// Creates a game object and asks the user for the game object before initializing the players.
  Game();
  /// Creates a game object with the mode specified in \p mode
  explicit Game(GameMode mode);

  /// Initializes the main game loop, based on \p game_mode_ starts a game.
  void PlayGame();

  /// Starts a Computer vs Computer Game.
  /// The game ends after one of the players loses or after MAX_ROUNDS rounds have been played.
  void PlayComputerVsComputerGame();

  /// Starts a Computer vs Human game.
  /// For the computer rounds the move are generated randomly, for the human's ones the user is asked for a move.
  /// The game ends after one of the players loses.
  void PlayComputerVsHumanGame();

  /// Performs a \p move.
  /// \param attacker The current player at this turn
  /// \param opponent The opponent.
  /// \param move A pair of coordinates (origin, target) representing the center of a ship (origin) and a target, based on the type of ship
  /// target can be the square to attack or the square to move to.
  /// \return if the move has been performed successfully.
  bool PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move);

  /// Utility function to read a choice from the user between a set of available choices.
  /// It keeps asking for a valid choice until the user types a valid choice.
  /// \param available_choices
  /// \return
  static int ReadChoiceFromUser(const std::set<int> &available_choices);

  /// Places the ships on \p player GameBoard, by asking the user for coordinates of bow and stern of each ship to place.
  /// \param player
  void PlaceShipsFromUser(Player &player);

  /// Receives and parses a command from the user. See \c UserCommand
  UserCommand GetUserCommand(const std::string &prompt);

  /// Attempts to place a ship in \p player's GameBoard. See \c Player::PlaceShip
  /// \return true if the has been placed successfully, false otherwise.
  bool AttemptToPlaceAShip(Player &player, std::pair<Coordinates, Coordinates> bow_stern, Ship &ship);
};
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAME_H_
