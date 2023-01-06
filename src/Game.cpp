#include "Game.h"
#include "Battleship.h"
#include "Submarine.h"
#include "SupportShip.h"
#include <chrono>
#include <iostream>
#include <thread>
const Player &Game::GetPlayerA() const {
  return player_a_;
}
void Game::SetPlayerA(const Player &player_a) {
  player_a_ = player_a;
}
const Player &Game::GetPlayerB() const {
  return player_b_;
}
void Game::SetPlayerB(const Player &player_b) {
  player_b_ = player_b;
}
const GameRecorder &Game::GetGameRecorder() const {
  return game_recorder_;
}
void Game::SetGameRecorder(const GameRecorder &game_recorder) {
  game_recorder_ = game_recorder;
}
Game::Game() {
}
bool Game::HandleAttack(Player &attacker, Player &opponent, Coordinates target) {
  bool attackResult = Battleship::Shoot(attacker.GetFiringBoard(), opponent.GetGameBoard(), target);
  // In caso di attacco andato a buon fine, incremento i colpi ricevuti dalla nave avversaria

  if (attackResult) {
	opponent.IncreaseShipHits(target);
	attacker.AddPotentialTargets(target);
  }
  std::cout << "Attack result: " << attackResult << std::endl;
  return attackResult;
}
void Game::PlaceShipsFromUser(const Player &player) {
}
//void Game::PlaceShipsRandomly(Player &player) {
//  player.PlaceShipsRandomly();
//}
void Game::Replay(const GameRecorder &game_recorder) {
}
std::ostream &operator<<(std::ostream &os, Game &game) {
  os << game.player_a_ << "\n"
	 << game.player_b_;
  return os;
}
void Game::PlayRandomGame() {

  bool playerATurn = false;
  int rounds = 0;

  player_a_.PlaceShipsRandomly();
  player_b_.PlaceShipsRandomly();

  std::cout << player_a_ << std::endl;
  std::cout << player_b_ << std::endl;

  while (!player_a_.HasLost() || !player_b_.HasLost()) {
	std::cout << rounds << " "
			  << "Turno di : " << (playerATurn ? player_a_.GetName() : player_b_.GetName()) << std::endl;

	Player &current_player = playerATurn ? player_a_ : player_b_;
	auto move = current_player.GetRandomMove();
	std::cout << move.first << " " << move.second << std::endl;
	if (playerATurn) {
	  std::cout << "Before" << std::endl;
	  std::cout << player_a_ << std::endl;
	  PlayMove(player_a_, player_b_, move);
	  std::cout << "After" << std::endl;
	  std::cout << player_a_ << std::endl;

	} else {
	  std::cout << "Before" << std::endl;
	  std::cout << player_b_ << std::endl;

	  PlayMove(player_b_, player_a_, move);
	  std::cout << "After" << std::endl;
	  std::cout << player_b_ << std::endl;
	}

	std::cout << "------------------------------------------------------------------" << std::endl;
	playerATurn = !playerATurn;

	if (rounds++ == 200) exit(1);
	//	std::string c;
	//	std::cin >> c;
  }
}

void Game::PlayMove(Player &player, Player &opponent, std::pair<Coordinates, Coordinates> move) {
  if (!player.GetShips().count(move.first)) throw std::invalid_argument("There is no ship at the specified location");
  Ship &ship = const_cast<Ship &>(player.GetShips().at(move.first));
  std::cout << ship << std::endl;
  switch (ship.GetOccupationType()) {

	case EMPTY:
	  throw std::invalid_argument("There is not Ship at the specified location");
	case HIT:
	case MISS:
	  return;
	case SUBMARINE:
	case SUPPORT_SHIP:
	  if (player.GetShips().at(move.first).GetHits() != 0) throw std::invalid_argument("Cannot move ship because it's already shot");
	  player.MoveShip(move.first, move.second, ship);
	  break;
	case BATTLESHIP:
	  HandleAttack(player, opponent, move.second);
	  break;
  }
}
Game::Game(Player playerA, Player playerB) {
}
void Game::PlayUserVsUserGame() {
  std::string player_a_name;
  std::string player_b_name;

  // Getting the player's name
  std::cout << "Please insert player A's name: "
			<< " ";
  std::cin >> player_a_name;
  std::cout << "Please insert player B's name: "
			<< " ";
  std::cin >> player_b_name;

  Player player_a = Player(player_a_name);

  Player player_b = Player(player_b_name);

  std::cout << "\033[2J";

  std::cout << "Placing player A's ships" << std::endl;
  std::cout << player_a << std::endl;

  PlaceBattleshipFromUser(player_a);
  PlaceSupportshipFromUser(player_a);
  PlaceSubmarineFromUser(player_a);


  PlaceBattleshipFromUser(player_b);
  PlaceSupportshipFromUser(player_b);
  PlaceSubmarineFromUser(player_b);

  // Getting for each player place ships
  // Start a turn based game
}
void Game::PlaceBattleshipFromUser(Player &player_a) const {
  std::string input;
  for (int i = 0; i < 3; ++i) {
	std::cout << "Inserire le coordinate per la corazzata " << (i + 1) << ": ";
	std::cin >> input;
	Coordinates bow = Coordinates::ParseCoordinate(input);
	std::cin >> input;
	Coordinates stern = Coordinates::ParseCoordinate(input);

	Battleship ship = Battleship(bow.GetRow() == stern.GetRow() ? HORIZONTAL : VERTICAL);
	player_a.PlaceShip(ship, bow, stern);

	std::cout << player_a << std::endl;
  }
}
void Game::PlaceSupportshipFromUser(Player &player_a) const {
  std::string input;
  for (int i = 0; i < 3; ++i) {
	std::cout << "Inserire le coordinate per la nave di supporto " << (i + 1) << ": ";
	std::cin >> input;
	Coordinates bow = Coordinates::ParseCoordinate(input);
	std::cin >> input;
	Coordinates stern = Coordinates::ParseCoordinate(input);

	SupportShip ship = SupportShip(bow.GetRow() == stern.GetRow() ? HORIZONTAL : VERTICAL);
	player_a.PlaceShip(ship, bow, stern);

	std::cout << player_a << std::endl;
  }
}
void Game::PlaceSubmarineFromUser(Player &player) const {
  for (int i = 0; i < 2; ++i) {

	std::string input;
	std::cout << "Inserire le coordinate per il sottomarino di esplorazione " << (i + 1) << ": ";
	std::cin >> input;
	Coordinates bow = Coordinates::ParseCoordinate(input);
	std::cin >> input;
	Coordinates stern = Coordinates::ParseCoordinate(input);

	Submarine ship = Submarine(bow.GetRow() == stern.GetRow() ? HORIZONTAL : VERTICAL);
	player.PlaceShip(ship, bow, stern);

	std::cout << player << std::endl;
  }
}
