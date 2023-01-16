// Author: Mouhieddine Sabir

#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_ASCIIART_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_ASCIIART_H_
#include "Utility.h"
#include <string>

namespace AsciiArt {
const std::string SUBMARINE = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~oo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
							  "                                 o o\n"
							  "                                 o ooo\n"
							  "                                   o oo\n"
							  "                                      o o      |   #)\n"
							  "                                       oo     _|_|_#_\n"
							  "                                         o   | 751   |\n"
							  "    __                    ___________________|       |_________________\n"
							  "   |   -_______-----------                                              \\\n"
							  "  >|    _____                                                   --->     )\n"
							  "   |__ -     ---------_________________________________________________ /";

const std::string BATTLESHIP = "                                     |__\n"
							   "                                     |\\/\n"
							   "                                     ---\n"
							   "                                     / | [\n"
							   "                              !      | |||\n"
							   "                            _/|     _/|-++'\n"
							   "                        +  +--|    |--|--|_ |-\n"
							   "                     { /|__|  |/\\__|  |--- |||__/\n"
							   "                    +---------------___[}-_===_.'____               /\\\n"
							   "                ____`-' ||___-{]_| _[}-  |     |_[___\\==--          \\/   _\n"
							   " __..._____--==/___]_|__|_____________________________[___\\==--___,-----' .7\n"
							   "|                                                                   BB-61/\n"
							   " \\_______________________________________________________________________|";

const std::string GAME_TITLE = "\n"
							   "▀█████████▄     ▄████████     ███         ███      ▄█          ▄████████    ▄████████    ▄█    █▄     ▄█     ▄███████▄ \n"
							   "  ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███         ███    ███   ███    ███   ███    ███   ███    ███    ███ \n"
							   "  ███    ███   ███    ███    ▀███▀▀██    ▀███▀▀██ ███         ███    █▀    ███    █▀    ███    ███   ███▌   ███    ███ \n"
							   " ▄███▄▄▄██▀    ███    ███     ███   ▀     ███   ▀ ███        ▄███▄▄▄       ███         ▄███▄▄▄▄███▄▄ ███▌   ███    ███ \n"
							   "▀▀███▀▀▀██▄  ▀███████████     ███         ███     ███       ▀▀███▀▀▀     ▀███████████ ▀▀███▀▀▀▀███▀  ███▌ ▀█████████▀  \n"
							   "  ███    ██▄   ███    ███     ███         ███     ███         ███    █▄           ███   ███    ███   ███    ███        \n"
							   "  ███    ███   ███    ███     ███         ███     ███▌    ▄   ███    ███    ▄█    ███   ███    ███   ███    ███        \n"
							   "▄█████████▀    ███    █▀     ▄████▀      ▄████▀   █████▄▄██   ██████████  ▄████████▀    ███    █▀    █▀    ▄████▀      \n"
							   "                                                  ▀                                                                    ";

const std::string DIVIDER = "<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>";
const std::string DIVIDER_WITH_AUTORS = "<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> By CTRL + C, CTRL + V";
const std::string CLEAR_SCREEN = "\033[2J";

const std::string GAME_OVER = "\n"
							  "  ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███  \n"
							  " ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒\n"
							  "▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒\n"
							  "░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄  \n"
							  "░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒\n"
							  " ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░\n"
							  "  ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░\n"
							  "░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░ \n"
							  "      ░       ░  ░       ░      ░  ░       ░ ░        ░     ░  ░   ░     \n"
							  "                                                     ░                   ";

const std::string MAIN_MENU = "Welcome to Battleship 1.0!\n"
							  "1) Play a new Human vs Bot game.\n"
							  "2) Watch a Bot vs Bot game.\n"
							  "3) Replay game from log file.\n";

const std::string COMMANDS_MENU ="\nType " + ColourText256("XX XX", 50) + " to view our current territory."
	+ "\nType " + ColourText256("AA AA", 50) + " to reset our submarine sightings."
	+ "\nType " + ColourText256("BB BB", 50) + " to reset our sonar completely from successful hits."
	+ "\nType " + ColourText256("CC CC", 50) + " to reset our sonar completely from unsuccessful hits"
	+ "\nType " + ColourText256("DD DD", 50) + " to reset our sonar completely.\n";
}// namespace AsciiArt
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_ASCIIART_H_
