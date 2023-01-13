#include "Game.h"
#include "UserCommand.h"
Game::Game(GameMode mode) : player_a_(Player("Bot 1")), player_b_(Player("Bot 2")), game_mode_(mode) {

  if (mode == COMPUTER_VS_HUMAN) {
	player_a_ = Player("Bot");
	player_b_ = Player("Admiral");
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
	std::cout << ColourText256("\nTurn " + std::to_string(turn), 6) << std::endl;

	Player &current_player = player_a_turn ? player_a_ : player_b_;
	Player &opponent = player_a_turn ? player_b_ : player_a_;

	if (player_a_turn) {
	  std::cout << ColourText256("The enemy is making their move.", 1) << std::endl;
	  std::pair<Coordinates, Coordinates> move = current_player.GenerateRandomMove();
	  PlayMove(current_player, opponent, move);

	} else {
	  std::cout << ColourText256("Admiral, it's our turn!", 2) << std::endl;
	  std::cout << "Type " << ColourText256("XX XX", 50) << " to view our current territory." << std::endl;
	  std::cout << "Type " << ColourText256("AA AA", 50) << " to reset our submarine sightings." << std::endl;
	  std::cout << "Type " << ColourText256("BB BB", 50) << " to reset our sonar completely." << std::endl;
	}

	player_a_turn = !player_a_turn;
	if (turn == 2) break;
	turn++;
  }
}

bool Game::PlayMove(Player &attacker, Player &opponent, std::pair<Coordinates, Coordinates> move) {

  if (attacker.GetShipAt(move.first) == nullptr) throw std::invalid_argument(std::string("No ship at the specified location"));

  std::shared_ptr<Ship> ship = attacker.GetShipAt(move.first);

  if (ship->GetShipType() == BATTLESHIP) {
	// handle attack
	if (attacker.IsHuman()) {
	  std::cout << "The enemy is attacking the square " << move.second.ToUserCoordinates() << std::endl;
	} else {
	  std::cout << "We are attacking the square " << move.second.ToUserCoordinates() << std::endl;
	}
	bool result = opponent.ReceiveAttack(move.second);
	attacker.MarkAttack(move.second, result);
	if (result) {
	  attacker.AddNextTargets(move.second);
	  if (attacker.IsHuman()) {
		std::cout << ColourText256("HIT!", 31) << " We got em!" << std::endl;
	  } else {
		std::cout << ColourText256("HIT!", 32) << " They got us!" << std::endl;
	  }
	} else {
	  if (attacker.IsHuman()) {
		std::cout << ColourText256("SPLASH!", 32) << " We missed!" << std::endl;
	  } else {
		std::cout << ColourText256("SPLASH!", 31) << " They missed, those fools!" << std::endl;
	  }
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

int Game::ReadChoiceFromUser(const std::set<int> &available_choices) {
  std::string input;
  int choice;
  do {
	std::cout << "Select a voice from the menu: ";
	std::cin >> input;
	std::stringstream(input) >> choice;
	if (available_choices.count(choice) == 0) std::cout << "Invalid choice!" << std::endl;
  } while (available_choices.count(choice) == 0);

  return choice;
}

void Game::PlaceShipsFromUser(Player &player) {

  std::stringstream promt;
  bool placed = false;

  // 3 Corazzate
  Battleship battleship = Battleship();
  for (int i = 0; i < 3; ++i) {
	promt << ColourText256("Where do you wish to place the battleship n. ", 68) << i + 1 << " (5 units wide) "
		  << ": ";
	while (!placed) {
	  std::pair<Coordinates, Coordinates> placement = GetUserCommand(promt.str());
	  placed = AttemptToPlaceAShip(player, placement, battleship);
	}
	placed = false;
	std::cout << ColourText256("Ship placed successfully!", 2) << std::endl;
	std::cout << player.GameBoardToString() << std::endl;
	promt = std::stringstream();
  }

  std::cout << ColourText256("All the battleship have been placed successfully!", 20) << std::endl;

  // 3 Navi di supporto

  SupportShip support_ship = SupportShip();
  for (int i = 0; i < 3; ++i) {
	promt << ColourText256("Where do you wish to place the support ship n. ", 68) << i + 1 << " (3 units wide) "
		  << ": ";
	while (!placed) {
	  std::pair<Coordinates, Coordinates> placement = GetUserCommand(promt.str());
	  placed = AttemptToPlaceAShip(player, placement, support_ship);
	}
	placed = false;
	std::cout << ColourText256("Ship placed successfully!", 2) << std::endl;
	std::cout << player.GameBoardToString() << std::endl;
	promt = std::stringstream();
  }

  // 2 Sottomarini

  Submarine submarine = Submarine();
  for (int i = 0; i < 2; ++i) {
	promt << ColourText256("Where do you wish to place the submarine n. ", 68) << i + 1 << " (1 unit wide) "
		  << ": ";
	while (!placed) {
	  std::pair<Coordinates, Coordinates> placement = GetUserCommand(promt.str());
	  placed = AttemptToPlaceAShip(player, placement, submarine);
	}
	placed = false;
	std::cout << ColourText256("Ship placed successfully!", 2) << std::endl;
	std::cout << player << std::endl;
	promt = std::stringstream();
  }

  std::cout << AsciiArt::CLEAR_SCREEN << std::endl;
  std::cout << ColourText256("Admiral, our fleet is in position", 98) << std::endl;
}

UserCommand Game::GetUserCommand(const std::string &promt) {

  std::string input;
  Coordinates bow, stern;
  while (true) {
	try {
	  std::cout << promt;

	  getline(std::cin, input);

	  if (UserCommand::IsSpecial(input)) {
		return UserCommand(input);
	  }
	  // Handling special commands

	  // Not special command
	  std::vector<std::string> coordinate_pair = Split(input, ' ');
	  // Bow

	  if (coordinate_pair.at(0).size() > 3 || coordinate_pair.at(0).size() < 2) throw std::invalid_argument("Invalid syntax!");
	  if (coordinate_pair.at(1).size() > 3 || coordinate_pair.at(1).size() < 2) throw std::invalid_argument("Invalid syntax!");

	  bow = Coordinates(coordinate_pair.at(0));
	  stern = Coordinates(coordinate_pair.at(1));

	} catch (std::invalid_argument &ex) {
	  std::cout << ColourText256(ex.what(), 1) << std::endl;
	  continue;
	}
	break;
  }
  return {{bow, stern}, MOVE};
};

bool Game::AttemptToPlaceAShip(Player &player, std::pair<Coordinates, Coordinates> bow_stern, Ship &ship) {
  try {
	player.PlaceShip(bow_stern.first, bow_stern.second, ship);
  } catch (std::invalid_argument &ex) {
	std::cout << ColourText256(ex.what(), 1) << std::endl;
	return false;
  }
  return true;
}