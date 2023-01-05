#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include "Orientation.h"
#include <vector>
#include <iostream>
// #include <algorithm>
// #include <map>


class Coordinates {
public:
    Coordinates(): row_{0}, col_{0} {};
    
    bool IsValidCoord(int value) const;

    Coordinates(int row, int col);

    int GetRow() const { return row_; }

    int GetCol() const { return col_; }

    void SetRow(int row) { row_ = row; }

    void SetCol(int col) { col_ = col; }

    bool IsInBound(int min, int max) const;

    static std::vector<Coordinates> GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count);

    static std::vector<Coordinates> GetAdjacentStarCoordinates(Coordinates starting);

    // from A8 to (1,8)
    static Coordinates ParseCoordinates(std::string &coordinates);

    Coordinates& operator=(Coordinates coords);


private:
    int row_;
    int col_;

    int const MIN_COORD = 0;\
    int const MAX_COORD = 11;

};

bool operator==(Coordinates c1, Coordinates c2);

bool operator!=(Coordinates c1, Coordinates c2);

std::ostream& operator<<(std::ostream& os, Coordinates coord);


#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_



