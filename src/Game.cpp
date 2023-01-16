#include "Game.h"

#include "UserCommand.h"
#include <utility>

Game::Game(GameMode mode) : player_a_(Player("Bot 1")), player_b_(Player("Bot 2")), game_mode_(mode), game_recorder_(mode) {
  if (mode == COMPUTER_VS_HUMAN) {
	player_a_ = Player("Bot");
	player_b_ = Player("Admiral", true);
  }
}
void Game::PlayGame() {
  if (game_mode_ == COMPUTER_VS_COMPUTER) PlayComputerVsComputerGame();
  if (game_mode_ == COMPUTER_VS_HUMAN) PlayComputerVsHumanGame();
  if (game_mode_ == REPLAY) std::cout << "Not implemented yet!" << std::endl;
}

void Game::PlayComputerVsComputerGame() {

  std::cout << AsciiArt::GAME_TITLE << std::endl;
  if (LOGGING_ACTIVE) game_recorder_.SetIsPlayerATurn(true);
  player_a_.PlaceShipsRandomly(game_recorder_);
  if (LOGGING_ACTIVE) game_recorder_.SetIsPlayerATurn(false);
  player_b_.PlaceShipsRandomly(game_recorder_);

  bool player_a_turn = RandomIntInRange(0, 1);
  if (LOGGING_ACTIVE) game_recorder_.SetStartingPlayer(player_a_turn ? 1 : 2);
  int i;
  for (i = 0; i < MAX_ROUNDS && !player_a_.HasLost() && !player_b_.HasLost(); ++i) {
	if (LOGGING_ACTIVE) game_recorder_.SetIsPlayerATurn(player_a_turn);
	std::cout << ColourText256("\nTurn " + std::to_string(i), 6) << std::endl;

	Player &current_player = player_a_turn ? player_a_ : player_b_;
	Player &opponent = player_a_turn ? player_b_ : player_a_;

	std::cout << ColourText256(current_player.GetName(), player_a_turn ? 32 : 220) << " is making his move." << std::endl;
	std::pair<Coordinates, Coordinates> move = current_player.GenerateRandomMove();
	PlayMove(current_player, opponent, move);

	if (LOGGING_ACTIVE) game_recorder_.RecordMove(move);
	player_a_turn = !player_a_turn;
  }

  std::cout << AsciiArt::DIVIDER << std::endl;
  std::cout << AsciiArt::GAME_OVER << std::endl;

  if (LOGGING_ACTIVE) game_recorder_.PersistGameToLog();

  if (!player_a_.HasLost() && !player_b_.HasLost()) {
	std::cout << ColourText256("The game has ended after " + std::to_string(i) + " rounds without a winner.", 9) << std::endl;
	return;
  }

  Player &winner = player_a_.HasLost() ? player_b_ : player_a_;

  std::cout << ColourText256("The game has ended after " + std::to_string(i) + " rounds with " + winner.GetName() + " as winner.", 2) << std::endl;

  if (LOGGING_ACTIVE) game_recorder_.PersistGameToLog();
}
void Game::PlayComputerVsHumanGame() {
  std::cout << AsciiArt::GAME_TITLE << std::endl;
  std::cout << AsciiArt::DIVIDER_WITH_AUTORS << std::endl;

  std::cout
	  << ColourText256("Admiral, you're tasked with defending a territory that is 12 units wide by 12 units tall: ", 98) << '\n';
  std::cout << player_b_.GameBoardToString() << std::endl;

  std::cout << "Your fleet is composed of:\n-> 3 Battleships (5 units wide)\n-> 3 Support ships (3 units wide)\n-> 2 Submarines (1 unit wide)\n";
  std::cout << std::endl;

  // For testing only we generate the ships randomly
  //  PlaceShipsFromUser(player_b_);
  player_b_.PlaceShipsRandomly(game_recorder_);

  std::cout << ColourText256("Admiral, the opposing fleet is getting into position.", 98) << std::endl;
  player_a_.PlaceShipsRandomly(game_recorder_);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << ColourText256("Opponent fleet in position. Ready for battle.", 33) << std::endl;

  // Handle the special commands

  bool player_a_turn = RandomIntInRange(0, 1);

  int turn = 1;
  while (!player_a_.HasLost() || player_b_.HasLost()) {
	std::cout << AsciiArt::CLEAR_SCREEN << std::endl;
	std::cout << ColourText256("\nTurn " + std::to_string(turn), 6) << std::endl;

	Player &current_player = player_a_turn ? player_a_ : player_b_;
	Player &opponent = player_a_turn ? player_b_ : player_a_;

	if (player_a_turn) {
	  std::cout << ColourText256("The enemy is making their move.", 1) << std::endl;
	  std::pair<Coordinates, Coordinates> move = current_player.GenerateRandomMove();
	  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	  PlayMove(current_player, opponent, move);
	  if (LOGGING_ACTIVE) game_recorder_.RecordMove(move);

	} else {

	  std::cout << ColourText256("Admiral, it's our turn!", 2) << "\n To view all the available special commands, type SS SS" << std::endl;
	  bool executed_move = false;
	  std::string prompt = "Admiral, what's our next move?: ";
	  while (!executed_move) {

		UserCommand user_command = GetUserCommand(prompt);
		switch (user_command.GetCommandType()) {

		  case SHOW_COMMANDS_MENU:
			std::cout << AsciiArt::COMMANDS_MENU << std::endl;
			break;
		  case SHOW_GRID:
			std::cout << current_player << std::endl;
			break;
		  case CLEAR_SONAR:
			current_player.ClearSubmarineSightings();
			break;
		  case CLEAR_ALL:
			current_player.ClearAllHits();
			break;
		  case CLEAR_HIT:
			current_player.ClearSuccessfulHits();
			break;
		  case CLEAR_MISS:
			current_player.ClearUnsuccessfulHits();
			break;
		  case MOVE:
			try {

			  executed_move = PlayMove(current_player, opponent, user_command.GetMove());
			} catch (std::invalid_argument &ex) {
			  std::cout << ColourText256(ex.what(), 1) << std::endl;
			  executed_move = false;
			}
			break;
		}

		if (LOGGING_ACTIVE) game_recorder_.RecordMove(user_command.GetMove());
	  }
	}

	player_a_turn = !player_a_turn;
	//	if (turn == 4) break;
	turn++;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }

  if (LOGGING_ACTIVE) game_recorder_.PersistGameToLog();

  Player &winner = player_a_.HasLost() ? player_b_ : player_a_;

  std::cout << AsciiArt::DIVIDER << std::endl;
  std::cout << AsciiArt::GAME_OVER << std::endl;

  std::cout << ColourText256("The game has ended after " + std::to_string(turn) + " rounds with " + winner.GetName() + " as winner.", 2) << std::endl;
}

bool Game::PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move) {

  if (attacker.GetShipAt(move.first) == nullptr) throw std::invalid_argument(std::string("No ship at the specified location"));

  std::shared_ptr<Ship> ship = attacker.GetShipAt(move.first);

  if (ship->GetShipType() == BATTLESHIP) {
	// handle attack
	if (game_mode_ != REPLAY) std::cout << "Attacking the square " << move.second.ToUserCoordinates() << std::endl;
	bool result = opponent.ReceiveAttack(move.second);
	attacker.MarkAttack(move.second, result);
	// TODO: Add a message to inform the user that a ship has been sunk
	if (result) {
	  attacker.AddNextTargets(move.second);
	}

	if (game_mode_ != REPLAY) std::cout << attacker.GetAttackMessage(result) << std::endl;
	return true;
  }

  // move ship

  bool ship_moved = attacker.MoveShip(move.first, move.second);
  if (!ship_moved) {
	std::cout << "Could not move this ship" << std::endl;
	return false;
  }

  if (game_mode_ != REPLAY) std::cout << "The player has moved one of his ships!" << std::endl;

  if (ship->GetShipType() == SUBMARINE) {
	// Update the sightings
	std::map<Coordinates, OccupationType> scans = Submarine::ScanSurroundings(opponent, move.second);
	attacker.AddSubmarineSightings(scans);
	attacker.AddNextTargets(scans);
  }

  if (ship->GetShipType() == SUPPORTSHIP) SupportShip::RepairNearbyShips(attacker, move.second);
  return true;
}
void Game::PlaceShipsFromUser(Player &player) {

  std::stringstream prompt;
  bool placed = false;

  // 3 battleships
  Battleship battleship = Battleship();
  UserCommand command;
  for (int i = 0; i < 3; ++i) {
	prompt << ColourText256("Where do you wish to place the battleship n. ", 68) << i + 1 << " (5 units wide) "
		   << ": ";
	while (!placed) {
	  command = GetUserCommand(prompt.str());
	  if (command.GetCommandType() != MOVE) continue;
	  placed = AttemptToPlaceAShip(player, command.GetMove(), battleship);
	}
	if (LOGGING_ACTIVE) game_recorder_.RecordMove(command.GetMove());
	placed = false;
	std::cout << ColourText256("Ship placed successfully!", 2) << std::endl;
	std::cout << player.GameBoardToString() << std::endl;
	prompt = std::stringstream();
  }

  std::cout << ColourText256("All the battleship have been placed successfully!", 20) << std::endl;

  // 3 support ships

  SupportShip support_ship = SupportShip();
  for (int i = 0; i < 3; ++i) {
	prompt << ColourText256("Where do you wish to place the support ship n. ", 68) << i + 1 << " (3 units wide) "
		   << ": ";
	while (!placed) {
	  command = GetUserCommand(prompt.str());
	  if (command.GetCommandType() != MOVE) continue;
	  placed = AttemptToPlaceAShip(player, command.GetMove(), support_ship);
	}
	if (LOGGING_ACTIVE) game_recorder_.RecordMove(command.GetMove());
	placed = false;
	std::cout << ColourText256("Ship placed successfully!", 2) << std::endl;
	std::cout << player.GameBoardToString() << std::endl;
	prompt = std::stringstream();
  }

  // 2 submarines

  Submarine submarine = Submarine();
  for (int i = 0; i < 2; ++i) {
	prompt << ColourText256("Where do you wish to place the submarine n. ", 68) << i + 1 << " (1 unit wide) "
		   << ": ";
	while (!placed) {
	  command = GetUserCommand(prompt.str());
	  if (command.GetCommandType() != MOVE) continue;
	  placed = AttemptToPlaceAShip(player, command.GetMove(), submarine);
	}
	if (LOGGING_ACTIVE) game_recorder_.RecordMove(command.GetMove());
	placed = false;
	std::cout << ColourText256("Ship placed successfully!", 2) << std::endl;
	std::cout << player.GameBoardToString() << std::endl;
	prompt = std::stringstream();
  }

  std::cout << AsciiArt::CLEAR_SCREEN << std::endl;
  std::cout << ColourText256("Admiral, our fleet is in position", 98) << std::endl;
}

UserCommand Game::GetUserCommand(const std::string &prompt) {

  std::string input;
  Coordinates bow, stern;
  while (true) {
	try {
	  std::cout << prompt;

	  getline(std::cin, input);

	  // TODO: DEBUG ONLY
	  if (input == "SHOW") {

		std::cout << player_a_ << std::endl;
		std::cout << player_b_ << std::endl;
		input = "";
		continue;
	  }
	  //

	  if (input.size() < 5) throw std::invalid_argument("Invalid command syntax!");
	  if (UserCommand::IsSpecial(input)) {
		return UserCommand(input);
	  }
	  // Handling special commands

	  // Not special command
	  std::vector<std::string> coordinate_pair = Split(input, ' ');
	  // Bow

	  if (coordinate_pair.at(0).size() > 3 || coordinate_pair.at(0).size() < 2 || coordinate_pair.at(1).size() > 3 || coordinate_pair.at(1).size() < 2)
		throw std::invalid_argument("Invalid  command syntax!");

	  bow = Coordinates(coordinate_pair.at(0));
	  stern = Coordinates(coordinate_pair.at(1));

	} catch (std::invalid_argument &ex) {
	  std::cout << ColourText256(ex.what(), 1) << std::endl;
	  input = "";
	  continue;
	}
	return {{bow, stern}, MOVE};
  }
}

bool Game::AttemptToPlaceAShip(Player &player, std::pair<Coordinates, Coordinates> bow_stern, Ship &ship) {
  try {
	player.PlaceShip(bow_stern.first, bow_stern.second, ship);
  } catch (std::invalid_argument &ex) {
	std::cout << ColourText256(ex.what(), 1) << std::endl;
	return false;
  }
  return true;
}
Game::Game(GameRecorder game_recorder) : player_a_(Player("Player 1")), player_b_(Player("Player 2")), game_mode_(REPLAY) {
  game_recorder_ = std::move(game_recorder);
}
std::string Game::Replay(bool to_ostream) {

  std::stringstream stringstream;
  bool player_a_turn = game_recorder_.GetStartingPlayer() == 1;

  std::map<std::pair<Coordinates, Coordinates>, int> player_a_placement = game_recorder_.GetPlayerAShipPlacement();
  std::map<std::pair<Coordinates, Coordinates>, int> player_b_placement = game_recorder_.GetPlayerBShipPlacement();

  std::vector<std::pair<Coordinates, Coordinates>> moves = game_recorder_.GetMoves();

  // Placing player A's ships

  Submarine submarine = Submarine();
  Battleship battleship = Battleship();
  SupportShip support_ship = SupportShip();

  for (auto placement : player_a_placement) {

	switch (placement.second) {
	  case 1:
		player_a_.PlaceShip(placement.first.first, placement.first.second, submarine);
		break;
	  case 3:
		player_a_.PlaceShip(placement.first.first, placement.first.second, support_ship);
		break;
	  case 5:
		player_a_.PlaceShip(placement.first.first, placement.first.second, battleship);
		break;
	  default:
		throw std::invalid_argument("Unknown ship");
		break;
	}
  }

  // Placing player B's ships

  for (auto placement : player_b_placement) {

	switch (placement.second) {
	  case 1:
		player_b_.PlaceShip(placement.first.first, placement.first.second, submarine);
		break;
	  case 3:
		player_b_.PlaceShip(placement.first.first, placement.first.second, support_ship);
		break;
	  case 5:
		player_b_.PlaceShip(placement.first.first, placement.first.second, battleship);
		break;
	  default:
		throw std::invalid_argument("Unknown ship");
		break;
	}
  }

  // Playing the moves;
  int rounds = 0;
  for (auto move : moves) {
	Player &current_player = player_a_turn ? player_a_ : player_b_;
	Player &opponent = player_a_turn ? player_b_ : player_a_;
	PlayMove(current_player, opponent, move);

	if (to_ostream) {
	  std::cout << current_player << std::endl;
	  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	} else {
	  stringstream << current_player << "\n\n";
	}

	player_a_turn = !player_a_turn;
	rounds++;
  }

  return stringstream.str();
}
