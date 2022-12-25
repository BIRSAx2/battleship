// Antonio Tangaro 2043429 

#include "Ship.h"

// Constructor
Ship::Ship(std::string name, int width, int armor, Orientation orientation) : 
name_(name), width_(width), armor_(armor), hits_(0), orientation_(orientation) {}

// Check if the ship is sunk (all its squares have been hit)
bool Ship::IsSunk() {
  return hits_ == width_;
}

void Ship::TakeHit() {
  hits_++;
  armor_--;
}

// Getters
std::string Ship::GetName() { return name_; }
int Ship::GetWidth() { return width_; }
int Ship::GetHits() { return hits_; }
Orientation Ship::GetOrientation() { return orientation_; }

// Setters
void Ship::SetName(std::string name) { name_ = name; }
void Ship::SetWidth(int width) { width_ = width; }
void Ship::SetHits(int hits) { hits_ = hits; }
void Ship::SetOrientation(Orientation orientation) { orientation_ = orientation; }
void Ship::SetArmor(int armor) { armor_ = armor; }
