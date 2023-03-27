#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
#include "Coordinates.h"
#include <algorithm>
#include <ostream>
#include <set>
#include <vector>
enum ShipType { UNSET = -1,
				SUBMARINE = 0,
				BATTLESHIP,
				SUPPORTSHIP };
class Ship {
 protected:
  /// Icon of this ship, this is the icon that gets returned by the \p ToString() method.
  std::string icon_;
  /// This is the main color of the icon of the ship.
  int icon_color_ = 2;

  /// When a unit of a ship is hit this is the icon that get returned by the ToString() method.
  std::string hit_icon_;
  /// The color of a hit unit's icon
  int hit_icon_color_ = 1;
  /// The width of this ship.
  int width_;

  /// The ship type.
  ShipType ship_type_ = UNSET;

  Coordinates bow_;
  Coordinates stern_;

  /// Each time a unit of a ship gets hit, it's offset from \p bow_ gets added to this set
  /// This set is used to keep track of which units of a ship have been hit during the movement of a ship.
  std::set<int> hit_locations_offset_;

 public:
  Ship() = default;
  /// \param icon The icon of the ship
  /// \param width The width of the ship
  Ship(char icon, int width) : width_(width) {
	icon_ = (char)toupper(icon);
	hit_icon_ = (char)tolower(icon);
  };
  /// \param icon The icon of the ship
  /// \param width The width of the ship
  /// \param icon_color The color of the icon of the ship
  Ship(char icon, int width, int icon_color) : width_(width), icon_color_(icon_color) {
	icon_ = (char)toupper(icon);
	hit_icon_ = (char)tolower(icon);
  };

  /// Returns the offsets from the bow that have been hit in this ship.
  /// \return A set of the offsets hit in this ship.
  const std::set<int> &GetHitLocationsOffset() const;
  void SetHitLocationsOffset(const std::set<int> &hit_locations_offset);
  const std::string &GetIcon() const;
  void SetIcon(const std::string &icon);
  const std::string &GetHitIcon() const;
  void SetHitIcon(const std::string &hit_icon);

  /// Check whether a ship has been sunk. A ship is considered sunk when the number of hits received is >= it's width.
  bool IsSunk();

  /// If \p location is part of this ship, the unit of this ship in it get marked as hit.
  /// \param location
  void HitLocation(Coordinates location);

  int GetWidth() const;
  void SetWidth(int width);
  ShipType GetShipType() const;
  const Coordinates &GetBow() const;
  void SetBow(const Coordinates &bow);
  const Coordinates &GetStern() const;
  void SetStern(const Coordinates &stern);

  /// Returns the icon of this ship based on the location provided. If \p location contains a unit from this ship, and that unit is hit,  it returns hit_icon
  /// Otherwise it returns icon.
  /// \param location The location where a unit of ship is present.
  std::string ToString(Coordinates location);

  /// Returns the center of this ship. The center is calculated as the middle unit between bow and stern.
  /// \return
  Coordinates GetShipCenter();

  /// Uses the Coordinates::GetCoordinateBetween(bow, stern) to generate all the location occupied by this ship.
  /// \return The a vector of Coordinates representing the locations where units of this ship are placed.
  std::vector<Coordinates> GetLocations();

  /// \return true: if the ship is horizontal
  /// \return false: if the ship is vertical
  bool IsHorizontal() const;

  /// Checks whether the unit of this ship contained at \p target has been hit or not.
  /// \param target
  /// \return true: the unit at \p target has been hit
  /// \return false: the unit at \p target has not been hit.
  bool IsHit(Coordinates target);

  /// Clears all hits received by this ship restoring the health.
  void Repair();
};

/// Prints to the output stream \p os the string the main characteristics of this this ship, like width, hits received etc.
std::ostream &operator<<(std::ostream &os, const Ship &ship);

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
