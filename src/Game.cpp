#include "Game.h"
Game::Game(GameMode mode) : player_a_(Player("Bot 1")), player_b_(Player("Bot 2")), game_mode_(mode) {

  if (mode == COMPUTER_VS_HUMAN) {
	player_a_ = Player("Bot");
	player_b_ = Player("Human");
  }
}
void Game::PlayGame() {
  if (game_mode_ == COMPUTER_VS_COMPUTER) PlayComputerVsComputerGame();
  if (game_mode_ == COMPUTER_VS_HUMAN) PlayComputerVsHumanGame();
  if (game_mode_ == REPLAY) std::cout << "Not implemented yet!" << std::endl;
}

void Game::PlayComputerVsComputerGame() {

  std::cout << AsciiArt::GAME_TITLE << std::endl;
  //  game_recorder_.SetIsPlayerATurn(true);
  player_a_.PlaceShipsRandomly(game_recorder_);
  //  game_recorder_.SetIsPlayerATurn(false);
  player_b_.PlaceShipsRandomly(game_recorder_);

  bool player_a_turn = RandomIntInRange(0, 1);
  //  game_recorder_.SetStartingPlayer(player_a_turn ? 1 : 2);
  int i;
  for (i = 0; i < 100 && !player_a_.HasLost() && !player_b_.HasLost(); ++i) {
	//	game_recorder_.SetIsPlayerATurn(player_a_turn);
	std::cout << ColourText256("\nTurn " + std::to_string(i), 6) << std::endl;
	Player &current_player = player_a_turn ? player_a_ : player_b_;
	Player &opponent = player_a_turn ? player_b_ : player_a_;
	std::cout << ColourText256(current_player.GetName(), player_a_turn ? 32 : 220) << " is making his move." << std::endl;

	std::pair<Coordinates, Coordinates> move = current_player.GenerateRandomMove();
	PlayMove(current_player, opponent, move);
	//	game_recorder_.RecordMove(move);
	player_a_turn = !player_a_turn;
  }

  std::cout << AsciiArt::DIVIDER << std::endl;
  //  std::cout << game_recorder_ << std::endl;
  //  std::cout << AsciiArt::DIVIDER << std::endl;
  std::cout << AsciiArt::GAME_OVER << std::endl;

  if (!player_a_.HasLost() && !player_b_.HasLost()) {
	std::cout << ColourText256("The game has ended after " + std::to_string(i) + " rounds without a winner.", 9) << std::endl;
	return;
  }

  Player &winner = player_a_.HasLost() ? player_b_ : player_a_;
  //  game_recorder_.PersistGameToLog();
}
void Game::PlayComputerVsHumanGame() {
  // Get Ship placement from user
  // Print the starting config
  // Handle the special commands
}

bool Game::PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move) {

  if (attacker.GetShipAt(move.first) == nullptr) throw std::invalid_argument(std::string("No ship at the specified location"));

  std::shared_ptr<Ship> ship = attacker.GetShipAt(move.first);

  if (ship->GetShipType() == BATTLESHIP) {
	// handle attack
	std::cout << "The player is attacking the square " << move.second.ToUserCoordinates() << std::endl;
	bool result = opponent.ReceiveAttack(move.second);
	attacker.MarkAttack(move.second, result);
	if (result) {
	  attacker.AddNextTargets(move.second);
	  std::cout << ColourText256("Hit! ", 40) << "Successful attack" << std::endl;
	} else {
	  std::cout << ColourText256("Splash! ", 9) << "Missed" << std::endl;
	}

	return true;
  }

  // move ship

  bool ship_moved = attacker.MoveShip(move.first, move.second);
  if (!ship_moved) {
	std::cout << "Could not move this ship" << std::endl;
	return false;
  }

  std::cout << "The player has moved one of his ships!" << std::endl;

  if (ship->GetShipType() == SUBMARINE) {
	// Update the sightings
	std::map<Coordinates, OccupationType> scans = Submarine::ScanSurroundings(opponent, move.second);
	attacker.UpdateSubmarineSightings(scans);
	attacker.AddNextTargets(scans);
  }
  return true;
}
Game::Game() : player_a_(Player("Bot 1")), player_b_(Player("Bot 2")) {

  std::cout << AsciiArt::GAME_TITLE << std::endl;
  std::cout << AsciiArt::DIVIDER_WITH_AUTORS << std::endl;
  std::cout << "\n"
			<< AsciiArt::MAIN_MENU << std::endl;
  int mode = ReadChoiceFromUser({1, 2, 3});

  switch (mode) {
	case 1: game_mode_ = COMPUTER_VS_HUMAN; break;
	case 2: game_mode_ = COMPUTER_VS_COMPUTER; break;
	default:
	  std::cout << "Not implemented yet!" << std::endl;
	  break;
  }
}

int Game::ReadChoiceFromUser(const std::set<int> &availble_choices) {
  std::string input;
  int choice;
  std::set<int> available_choices = {1, 2, 3};
  do {
	std::cout << "Select a voice from the menu: ";
	std::cin >> input;
	std::stringstream(input) >> choice;
	if (available_choices.count(choice) == 0) std::cout << "Invalid choice!" << std::endl;
  } while (available_choices.count(choice) == 0);

  return choice;
}