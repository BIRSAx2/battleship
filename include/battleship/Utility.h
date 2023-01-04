#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter);
std::string colour_text_256(const std::string &text, int ansi_code);
std::string colour_background_256(const std::string &text, int ansi_code);
int random_int_in_range(int min, int max);
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
