#include "Utility.h"

std::vector<std::string> Split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream token_stream(s);
  while (std::getline(token_stream, token, delimiter)) {
	std::cout << token << std::endl;
	tokens.push_back(token);
  }
  return tokens;
}
std::string ColourText256(const std::string &text, int ansi_code) {

  std::stringstream string_stream;
  string_stream << "\033[38;5;" << ansi_code << "m" << text << "\033[m";
  return string_stream.str();
}
std::string ColourBackground256(const std::string &text, int ansi_code) {

  std::stringstream string_stream;
  string_stream << "\033[48;5;" << ansi_code << "m" << text << "\033[m";
  return string_stream.str();
}

int RandomIntInRange(int min, int max) {
  // TODO: rand() has limited randomness, use c++ random library instead
  // We still use rand() for testing, for prod change it
  return min + (rand() % static_cast<int>(max - min));
}

int RandomEvenIntInRange(int min, int max) {
  return (min + (rand() % static_cast<int>(max / 2 - 1))) * 2;
}

int GetNumberFromLetter(char &c) {
  char letters[] = "ABCDEFGHILMN";
  for (int i = 0; i < 12; i++)
	if (letters[i] == c)
	  return i;
  return -1;
}

char GetLetterFromNumber(int code_point) {
  char letters[] = "ABCDEFGHILMN";
  return letters[code_point];
}