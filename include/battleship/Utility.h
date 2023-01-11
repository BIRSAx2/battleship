#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

std::vector<std::string> Split(const std::string &s, char delimiter);
std::string ColourText256(const std::string &text, int ansi_code);
std::string ColourBackground256(const std::string &text, int ansi_code);
int RandomIntInRange(int min, int max);
int GetNumberFromLetter(char &c);
char GetLetterFromNumber(int code_point);
int RandomEvenIntInRange(int min, int max);
std::string GetClearScreenANSISequence();

// DEBUG ONLY
void Print256ColoursTxt();

void Print256ColoursBackground();

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
