#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

/// Splits \p string in tokens by \p delimiter
/// \param s
/// \param delimiter
/// \return a vector of the tokens of the string.
std::vector<std::string> Split(const std::string &string, char delimiter);

/// Converts \p text in a colored string using ANSI Escape codes with the color code specified in \p ansi_code.
/// \see \link https://en.wikipedia.org/wiki/ANSI_escape_code
/// \param text
/// \param ansi_code
/// \return Colored \p text
std::string ColourText256(const std::string &text, int ansi_code);

/// Puts \p text in a colored background using ANSI Escape codes with the color code specified in \p ansi_code.
/// \see \link https://en.wikipedia.org/wiki/ANSI_escape_code
/// \param text
/// \param ansi_code
/// \return Background colored \p text
std::string ColourBackground256(const std::string &text, int ansi_code);

/// Generated a random integer between \p min and \p max (excluded)
/// \param min Lower bound
/// \param max Upper bound (excluded)
/// \return a random int
int RandomIntInRange(int min, int max);

/// Converts the char \p c into an int using it's index in the string "ABCDEFGHILMN".
/// \param c
/// \return An int between 0 and 11
int GetNumberFromLetter(char &c);

/// Converts the int \p num a char from "ABCDEFGHILMN".
/// \param c
/// \return An char between A and N
char GetLetterFromNumber(int num);

/// Generate an even random int from \p min to \p max (excluded)
/// \param min Lower bound
/// \param max Upper bound (excluded)
/// \return a random even int
int RandomEvenIntInRange(int min, int max);

/// Returns the current time as a string in the format YYYYMMDDHHMMSS
/// \return a string in the format YYYYMMDDHHMMSS
std::string GetTimestamp();

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
