#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include "Utility.h"
#include <map>
#include <ostream>
class Coordinates {
 public:
  Coordinates() : row_col_{0, 0} {};
  /// A partire dalle coordinate dell'utente (XY, dove X è una lettera tra 'ABCDEFGHILMN' e Y è un numero tra 1 e 12), crea un oggetto Coordinate.
  /// Le coordinate vengono convertite secondo il seguente scema:
  /// X -> Un numero tra 0 e 11
  /// Y -> Il numero stesso -1
  /// \param user_coordinates Le coordinate fornite dall'utente.
  explicit Coordinates(std::string &user_coordinates);
  /// \param row La coordinata per la riga
  /// \param col La coordinata per la colonna
  Coordinates(int row, int col);
  int GetRow() const;
  int GetCol() const;

  /// \return Restituisce true se 0 <= row < 12 e 0 <= col < 12, false in tutti gli altri casi.
  static bool IsValid(int row, int col);
  /// Effettua il confronto tra this e other
  /// \param other
  /// \return true se sono uguali, false altrimenti.
  bool operator==(const Coordinates &other) const;
  /// Effettua il confronto tra this e other
  /// \param other
  /// \return true se sono diversi, false altrimenti.
  bool operator!=(const Coordinates &other) const;

  /// Il confronto effettuato è il seguente (GetRow() < other.GetRow() || (GetRow() == other.GetRow() && GetCol() < other.GetCol())
  /// \param other
  /// \return true se this si trova prima di other, false altrimenti.
  bool operator<(const Coordinates &other) const;

  /// Restituisce le coordinate sotto forma di (row,col)
  friend std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);

  /// Calcola l'offset tra this e coordinates. L'offset è calcolato solo se entrambe le coordinate si trovano sulla stessa riga oppure sulla stessa colonna.
  /// Se le coordinate non si trovano sulla stessa riga/colonna viene lanciata un eccezione std::invalid_argument
  /// \param coordinates
  /// \return Il numero di celle presente tra this e other, calcolato come differenza tra righe/colonne.
  int CalculateOffsetTo(Coordinates other);

  /// Restituisce le coordinate che si trovano tra start ed end (inclusi).
  /// \param start Coordinata di partenza
  /// \param end Coordinata di arrivo
  /// \return  Un vector delle coordinate che si trovano tra start ed end.
  static std::vector<Coordinates> GetCoordinatesBetween(Coordinates start, Coordinates end);


  /// Restituisce delle coordinate random all'interno della griglia
  /// \return
  static Coordinates GetRandomCoordinates();

  void SetRow(int row);
  void SetCol(int col);

 private:
  std::pair<int, int> row_col_;
  /// Converte le coordinate fornite dall'utente in coordinate di sistema.
  Coordinates ParseCoordinates(std::string &coordinates);
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
