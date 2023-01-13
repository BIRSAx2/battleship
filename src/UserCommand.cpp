#include "UserCommand.h"

const std::map<std::string, CommandType> UserCommand::SPECIAL_COMMANDS_ =
	{{"AA AA", CLEAR_SONAR}, {"XX XX", SHOW_GRID}, {"BB BB", CLEAR_HIT}, {"CC CC", CLEAR_MISS}, {"DD DD", CLEAR_ALL}};
