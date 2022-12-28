#include "Utility.h"
#include <sstream>

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
	tokens.push_back(token);
  }
  return tokens;
}
std::string colour_text_256(const std::string &text, int ansi_code) {

  std::stringstream stringstream;
  stringstream << "\033[38;5;" << ansi_code << "m" << text << "\033[m";
  return stringstream.str();
}
std::string colour_background_256(const std::string &text, int ansi_code) {

  std::stringstream stringstream;
  stringstream << "\033[48;5;" << ansi_code << "m" << text << "\033[m";
  return stringstream.str();
}

int random_int_in_range(int min, int max) {
  return min + (rand() % static_cast<int>(max - min + 1));
}