#include "../include/battleship/Coordinates.h"
#include "Utility.cpp"

/* TODO: 
  -- explicit Coordinates(std::string &user_coordinates);
  -- Coordinates(int row, int col);
  -- static bool IsValid(int row, int col);
  -- int CalculateOffsetTo(Coordinates other);
  -- static std::vector<Coordinates> GetCoordinatesBetween(Coordinates start, Coordinates end);
  static Coordinates GetRandomCoordinates();
  -- std::string ToUserCoordinates() const;
  -- static std::set<Coordinates> GetAdjacentStarCoordinates(Coordinates current);
  -- void SetRow(int row);
  -- void SetCol(int col);
  -- static Coordinates ParseCoordinates(std::string &coordinates);

  bool operator==(const Coordinates &c1,const Coordinates &c2);
  bool operator!=(const Coordinates &c1,const Coordinates &c2);
  -- bool operator>(const Coordinates &a, const Coordinates &b);
  -- bool operator<(const Coordinates &a, const Coordinates &b);
  -- std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);
*/

Coordinates::Coordinates(std::string &user_coordinates){
  Coordinates parsed = ParseCoordinates(user_coordinates);
  SetRow(parsed.GetRow());
  SetCol(parsed.GetCol());
}

Coordinates::Coordinates(int row, int col){
  if(!IsValid(row,col))
    throw std::invalid_argument("Invalid coordinates");
  row_col_.first = row;
  row_col_.second = col;
}

bool Coordinates::IsValid(int row, int col){
  return (row >= 0 && row <= 11) && (col >= 0 && col <= 11);
}

int Coordinates::CalculateOffsetTo(Coordinates other){
  if(GetRow() == other.GetRow())
    return other.GetCol() - GetCol();
  
  if(GetCol() == other.GetCol())
    return other.GetRow() - GetRow();

  throw std::invalid_argument("Cannot calculate offset. The two coordinates need to be either in the same row or in the same col");
}

std::vector<Coordinates> Coordinates::GetCoordinatesBetween(Coordinates start, Coordinates end){
  std::vector<Coordinates> inBetween;

  if(start.GetRow() == end.GetRow())
    while(start.GetCol() != end.GetCol()){
      inBetween.push_back(start);
      start.SetCol(start.GetCol() + 1);
    }
  
  if(start.GetCol() == end.GetCol())
    while(start.GetRow() != end.GetRow()){
      inBetween.push_back(start);
      start.SetRow(start.GetRow() + 1);
    }
  
  if(inBetween.size() == 0)
    throw std::invalid_argument("Cannot generate in between coordinate if end and start are not on the same row/col");
  
  inBetween.push_back(end);
  return inBetween;
  
}

std::string Coordinates::ToUserCoordinates() const{
  std::string user_coordinates = "";
  user_coordinates += GetLetterFromNumber(GetRow());

  int col = GetCol() + 1;
  user_coordinates += std::to_string(col); 

  return user_coordinates;
};

std::set<Coordinates> Coordinates::GetAdjacentStarCoordinates(Coordinates current){
    std::set<Coordinates> adjacent;
    // top coord
    adjacent.insert(Coordinates(current.GetRow() - 1, current.GetCol()));
    // left
    adjacent.insert(Coordinates(current.GetRow(), current.GetCol() - 1));
    // right
    adjacent.insert(Coordinates(current.GetRow(), current.GetCol() + 1));
    // bottom
    adjacent.insert(Coordinates(current.GetRow() + 1, current.GetCol()));

    return adjacent;

}

void Coordinates::SetRow(int row){
  if(!IsValid(row, row_col_.second))
    throw std::invalid_argument("Invalid coordinates");
  
  row_col_.first = row;
}

void Coordinates::SetCol(int col){
  if(!IsValid(row_col_.first, col))
    throw std::invalid_argument("Invalid coordinates");
  
  row_col_.second = col;
}

Coordinates Coordinates::ParseCoordinates(std::string &coordinates) {
  int row = GetNumberFromLetter(coordinates[0]);
  int col = 0;

  if (coordinates.size() == 3)
    col = 10 + (coordinates[2] - '0');
  else
    col = coordinates[1] - '0';

  // col - 1 because the string range is 1 - 12, but we use 0 - 11
  return Coordinates(row, col - 1);
}








// operatrs
bool operator==(const Coordinates &a,const Coordinates &b){
  return (a.GetRow() == b.GetRow()) && (a.GetCol() == b.GetCol());
}

bool operator!=(const Coordinates &a,const Coordinates &b){
  return !(a == b);
}

bool operator>(const Coordinates &a, const Coordinates &b){
  return (a.GetRow() > b.GetRow() || (a.GetRow() == b.GetRow() && a.GetCol() > b.GetCol()));
}

bool operator<(const Coordinates &a, const Coordinates &b){
  return (a.GetRow() < b.GetRow() || (a.GetRow() == b.GetRow() && a.GetCol() < b.GetCol()));
}

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates){
  return os << "(" << coordinates.GetRow() << "," << coordinates.GetCol() << ")";
}
