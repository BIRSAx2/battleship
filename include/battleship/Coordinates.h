// Author: Alessandro Trigolo

#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include "Utility.h"
#include <map>
#include <ostream>
#include <set>
class Coordinates {
 public:
  Coordinates() : row_col_{0, 0} {};
  // helper function
  explicit Coordinates(std::pair<int, int> coordinates) : Coordinates(coordinates.first, coordinates.second){};
  static bool IsValid(std::pair<int, int> row_col) {
	return IsValid(row_col.first, row_col.second);
  };

  /// Starting from the user's coordinates (XY, where X is a letter in 'ABCDEFGHILMN' and Y is a number between 1 and 12), create a Coordinates object.
  /// The coordinates are converted according to the following scheme:
  /// X -> A number between 0 and 11
  /// Y -> The number itself -1
  /// \param user_coordinates Coordinates supplied by the user.
  explicit Coordinates(std::string &user_coordinates);

  /// \param row number representing the row
  /// \param col number representing the col
  /// \throws std::invalid_argument if the coordinates are not valid.
  Coordinates(int row, int col);

  int GetRow() const { return row_col_.first; };
  int GetCol() const { return row_col_.second; };

  /// \return Returns true if 0 <= row < 12 and 0 <= col < 12, false otherwise.
  static bool IsValid(int row, int col);

  /// Calculates the offset between this and other. The offset is calculated only if both coordinates are in the same row or column.
  /// If the coordinates are not on the same row/column an exception is thrown std::invalid_argument
  /// \param coordinates
  /// \throws std::invalid_argument if the coordinates are not in the same row/column
  /// \return The number of cells between this and other, calculated as the difference between rows/columns.
  int CalculateOffsetTo(Coordinates other) const;

  /// Generates all coordinates between \p start and \p end
  /// \param start
  /// \param end
  /// \return  A vector containing all the coordinates between \p start and \p end
  static std::vector<Coordinates> GetCoordinatesBetween(Coordinates start, Coordinates end);

  /// Generates random coordinates
  /// \return Random coordinates
  static Coordinates GetRandomCoordinates();

  /// Formats the coordinates in the format: XY, where X is a letter in 'ABCDEFHILMN' and Y is a number between 1 and 12.
  std::string ToUserCoordinates() const;

  /// Returns a vector composed of the coordinates immediately to the right, left, above and below \p current.
  /// Esempio: (X = current)\n
  /// A B C \n
  /// D X E \n
  /// F G H \n
  /// In this case it returns { B, D, E, G}
  static std::set<Coordinates> GetAdjacentStarCoordinates(Coordinates current);

  void SetRow(int row);
  void SetCol(int col);

 private:
  std::pair<int, int> row_col_;
  /// Starting from the user's coordinates (XY, where X is a letter in 'ABCDEFGHILMN' and Y is a number between 1 and 12), create a Coordinates object.
  /// The coordinates are converted according to the following scheme:
  /// X -> A number between 0 and 11
  /// Y -> The number itself -1
  static Coordinates ParseCoordinates(std::string &coordinates);
};

/// Compares a to b
/// \param other
/// \return true if a and b are represent the same coordinate, false otherwise
bool operator==(const Coordinates &a, const Coordinates &b);

/// Compares a to b
/// \param other
/// \return true if a and b doesn't represent the same coordinate, false otherwise
bool operator!=(const Coordinates &a, const Coordinates &b);

/// Compares a to b, the comparison made is the following:\n
/// (a.GetRow() > b.GetRow() || (a.GetRow() == b.GetRow() && a.GetCol() > b.GetCol())
/// \param other
/// \return true if a comes after b in the grid, false otherwise.
bool operator>(const Coordinates &a, const Coordinates &b);

/// Compares a to b, the comparison made is the following:\n
/// (a.GetRow() < b.GetRow() || (a.GetRow() == b.GetRow() && a.GetCol() < b.GetCol())
/// \return true
/// \param other true if a comes before b in the grid, false otherwise.
bool operator<(const Coordinates &a, const Coordinates &b);

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);
std::istream &operator>>(std::istream &is, Coordinates& coordinates);

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_