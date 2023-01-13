#include "Game.h"
int main(int argc, char **argv) {
  if (argc <= 1) {
	// Se nessuna opzione è specificata si fa scegliere all'utente mediante un menu.
	Game game = Game();
	game.PlayGame();
  } else {
	std::string game_mode = argv[1];
	if (game_mode != "pc" && game_mode != "cc") {
	  std::cout << ColourText256("Invalid command line arguments!\n"
								 "Use:\n'pc' for a player vs computer game\n"
								 "'cc' for a computer vs computer game",
								 1)
				<< std::endl;
	  exit(0);
	}

	Game game = Game(game_mode == "pc" ? COMPUTER_VS_HUMAN : COMPUTER_VS_COMPUTER);
	game.PlayGame();
  }
  return 0;
}
