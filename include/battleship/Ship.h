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
  std::string icon_;
  int icon_color_ = 2;
  std::string hit_icon_;
  int hit_icon_color_ = 1;
  int width_{};
  // this might be deleted int the future
  ShipType ship_type_ = UNSET;
  Coordinates bow_;
  Coordinates stern_;
  std::set<int> hit_locations_offset_;

 public:
  Ship() = default;
  /// \param icon L'icona della nave
  /// \param width La dimensione della nave
  Ship(char icon, int width) : width_(width) {
	icon_ = (char)toupper(icon);
	hit_icon_ = (char)tolower(icon);
  };
  /// \param icon L'icona della nave
  /// \param width La dimensione della nave
  /// \param icon_color Il codice del colore dell'icona della nave
  Ship(char icon, int width, int icon_color) : width_(width), icon_color_(icon_color) {
	icon_ = (char)toupper(icon);
	hit_icon_ = (char)tolower(icon);
  };

  /// Restituisce gli offset dalla prua delle celle della nave colpite.
  /// \return Offset dalla prua della nave delle celle colpite.
  const std::set<int> &GetHitLocationsOffset() const;
  void SetHitLocationsOffset(const std::set<int> &hit_locations_offset);
  const std::string &GetIcon() const;
  void SetIcon(const std::string &icon);
  const std::string &GetHitIcon() const;
  void SetHitIcon(const std::string &hit_icon);

  ///
  /// \return true se i colpi ricevuti della nave sono >= la sua dimensione, false altrimenti.
  bool IsSunk();

  /// Segna la cella nave presente a location come colpita.
  /// \param location
  void HitLocation(Coordinates location);
  int GetWidth() const;
  void SetWidth(int width);
  ShipType GetShipType() const;
  const Coordinates &GetBow() const;
  void SetBow(const Coordinates &bow);
  const Coordinates &GetStern() const;
  void SetStern(const Coordinates &stern);
  /// Restituisce l'icona della nave in base a location. Se a location è presente una cella della nave colpita restituisce hit_icon_, altrimenti _icon
  /// \param location
  /// \return
  std::string ToString(Coordinates location);

  /// Restituisce le coordinate a metà tra prua e poppa.
  /// \return
  Coordinates GetShipCenter();

  /// \return Restituisce le coordinate presenti tra prua e poppa, in pratica quelle occupate dalla nave. Utilizza il metodo GetCoordinateBetween di Coordinates.
  std::vector<Coordinates> GetLocations();
  /// \return true se la nave è orizzontale, false se è verticale.
  bool IsHorizontal() const;
  /// Stampa le caratteristiche principali della nave, come icona, larghezza, orientamento ed il numero di colpi ricevuto.
  /// \return
  friend std::ostream &operator<<(std::ostream &os, const Ship &ship);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_SHIP_H_
