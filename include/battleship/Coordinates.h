#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

#include <stdio.h>
#include <string>
#include "Orientation.h"

class Coordinates {
public:
    Coordinates(int row, int col) : row_{row}, col_{col} {};

    int GetRow() { return row_; }

    int GetCol() { return col_; }

    void SetRow(int row) { row_ = row; }

    void SetCol(int col) { col_ = col; }

    bool IsInBound(int min, int max);

    bool GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count);


private:
    int row_;
    int col_;

};

static Coordinates ParseCoordinates(std::string &coordinates);


#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_



