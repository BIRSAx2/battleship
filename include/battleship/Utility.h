#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string &s, char delimiter);
std::string ColourText256(const std::string &text, int ansi_code);
std::string ColourBackground256(const std::string &text, int ansi_code);
/// Genera un numero intero casualmente tra min e max, con max escluso.
int RandomIntInRange(int min, int max);
int GetNumberFromLetter(char &c);
char GetLetterFromNumber(int code_point);
/// Genera un numero intero pari casualmente tra min e max, con max escluso.
int RandomEvenIntInRange(int min, int max);
std::string GetClearScreenANSISequence();
std::string GetTimestamp();

// DEBUG ONLY
void Print256ColoursTxt();

void Print256ColoursBackground();

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_UTILITY_H_
