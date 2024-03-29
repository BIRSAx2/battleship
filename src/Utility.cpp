#include "Utility.h"
std::vector<std::string> Split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream token_stream(s);
  while (std::getline(token_stream, token, delimiter)) {
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
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> int_distribution(min, max - 1);

  return int_distribution(gen);
}

int RandomEvenIntInRange(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> int_distribution(min, (max - 1) / 2);

  return int_distribution(gen) * 2;
}

int GetNumberFromLetter(char &c) {
  c = (char)toupper(c);
  char letters[] = "ABCDEFGHILMN";
  for (int i = 0; i < 12; i++)
	if (letters[i] == c)
	  return i;
  return -1;
}

char GetLetterFromNumber(int code_point) {
  char letters[] = "ABCDEFGHILMN";

  if (code_point < 0 || code_point > 11) throw std::invalid_argument("Invalid code point, can only convert numbers between 0 and 11 to letters! Received: " +std::to_string(code_point));
  return letters[code_point];
}

std::string GetTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(localtime(&in_time_t), "%Y%m%d%H%M%S");
  return ss.str();
}