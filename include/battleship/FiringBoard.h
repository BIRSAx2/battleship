#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_

#include "Board.h"
#include "GameBoard.h"
#include <ostream>

enum OccupationType { EMPTY,
					  HIT,
					  MISS,
					  OCCUPIED };

std::ostream &operator<<(std::ostream &os, OccupationType cat);
class FiringBoard : public Board {
 private:
  std::map<Coordinates, OccupationType> tiles_;

 public:
  FiringBoard() : Board(12, 12){};

  /// Marks the \p target coordinate as HIT if is_hit is true, or with MISS otherwise.
  /// \param target The coordinate under attack
  /// \param is_hit true: successful attack, false: unsuccessful.
  void MarkAttack(Coordinates target, bool is_hit);

  /// Clears all the submarine sightings marked on the board.
  void ClearSubmarineSightings();

  // Clears the board completely.
  void Clear();


  /// \return FiringBoard as a string  in the form of a grid  rows_ x columns_
  std::string ToString() const;

  /// \return true if \p coordinates has been attacked (HIT/MISS), false otherwise.

  bool HasBeenAttacked(Coordinates coordinates);

  /// Adds the sightings from the submarine to the board. The sightings are marked in the grid with OCCUPIED if a ship is present in the opponent board, but not yet hit,
  /// or with HIT if it's present and hit.
  /// \param sightings A map of coordinates and their status in the opponent's board.
  void AddSubmarineSightings(const std::map<Coordinates, OccupationType>& sightings);

  /// Clears all the coordinates with status HIT from the board.
  void ClearSuccessfulHits();

  /// Clears all the coordinates with status MISS from the board.
  void ClearUnsuccessfulHits();
};

/// Prints the FiringBoard to \p os in the form of a grid  rows_ x columns_
std::ostream &operator<<(std::ostream &os, const FiringBoard &board);
#endif//BATTLESHIP_INCLUDE_BATTLESHIP_FIRINGBOARD_H_
