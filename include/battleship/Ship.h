// Antonio Tangaro 2043429

#ifndef SHIP_H
#define SHIP_H

#include <string>

enum class Orientation {
  Horizontal,
  Vertical
};

class Ship {
 public:
  // Constructor
  Ship(std::string name, int width, int armor, Orientation orientation);

  // Check if the ship is sunk (all its squares have been hit)
  bool IsSunk();

  // Take a hit
  void TakeHit();

  // Getters
  std::string GetName();
  int GetWidth();
  int GetArmor();
  int GetHits();
  Orientation GetOrientation();

  // Setters
  void SetName(std::string name);
  void SetWidth(int width);
  void SetArmor(int armor);
  void SetHits(int hits);
  void SetOrientation(Orientation orientation);

 protected:
  std::string name_;
  int width_;
  int armor_;
  int hits_;
  Orientation orientation_;
};

#endif  // SHIP_H
