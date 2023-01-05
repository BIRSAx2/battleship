#include "../include/battleship/Coordinates.h"

bool Coordinates::IsValidCoord(int value) const{
    return (value >= MIN_COORD) && (value <= MAX_COORD);
}

Coordinates::Coordinates(int row, int col){
    if(!IsValidCoord(row) || !IsValidCoord(col))
        throw std::invalid_argument("Coordinates value out of range have been given.");
    row_ = row;
    col_ = col;
}


bool Coordinates::IsInBound(int min, int max) const {
    return ((row_ >= min) && (row_ < max)) && ((col_ >= min) && (col_ < max));
}

std::vector<Coordinates> Coordinates::GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count){
    std::vector<Coordinates> adjacent;
    for(int i = 1; i <= count; i++){
        Coordinates adjCoord = Coordinates();
        if(orientation == VERTICAL)
            adjCoord = Coordinates(starting.GetRow() + i, starting.GetCol());

        if(orientation == HORIZONTAL)
            adjCoord = Coordinates(starting.GetRow(), starting.GetCol() + i);
        
        adjacent.push_back(adjCoord);
    }

    return adjacent;
}

std::vector<Coordinates> Coordinates::GetAdjacentStarCoordinates(Coordinates starting){
    std::vector<Coordinates> adjacent;
    // top coord
    adjacent.push_back(Coordinates(starting.GetRow() - 1, starting.GetCol()));
    // bottom
    adjacent.push_back(Coordinates(starting.GetRow() + 1, starting.GetCol()));
    // left
    adjacent.push_back(Coordinates(starting.GetRow(), starting.GetCol() - 1));
    // right
    adjacent.push_back(Coordinates(starting.GetRow(), starting.GetCol() + 1));

    return adjacent;

}

int GetNumberFromLetter(char &c){
    char letters[] = "ABCDEFGHILMN";
    for(int i = 0; i < 12; i++)
        if(letters[i] == c)
            return i;
    return -1;
}

Coordinates Coordinates::ParseCoordinates(std::string &coordinates){
    int row = GetNumberFromLetter(coordinates[0]);
    int col = 0;

    if(coordinates.size() == 3)
        col = 10 + (coordinates[2] - '0');
    else
        col = coordinates[1] - '0';
    
    // col - 1 because the string range is 1 - 12, but we use 0 - 11
    return Coordinates(row, col - 1);
}



Coordinates& Coordinates::operator=(Coordinates coords){
    row_ = coords.GetRow();
    col_ = coords.GetCol();
    
    return *this;
}

bool operator==(Coordinates c1, Coordinates c2){
    return (c1.GetRow() == c2.GetRow()) && (c1.GetCol() == c2.GetCol());
}

bool operator!=(Coordinates c1, Coordinates c2){
    return !(c1 == c2);
}

std::ostream& operator<<(std::ostream& os, Coordinates coords){
    return os << "(" << coords.GetRow() << "," << coords.GetCol() << ")" ;
}