#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_

class Coordinates {
public:
    Coordinates(int row, int col) : row_{row}, col_{col} {};

    int GetRow() { return row_; }

    int GetCol() { return col_; }

    void SetRow(int row) { row_ = row; }

    void SetCol(int col) { col_ = col; }

private:
    int row_;
    int col_;

};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_COORDINATES_H_


/*
class Coordinates {
 - int row_
- int col_
+ Coordinates(int row, int column)
+ int GetRow()
+ int GetCol()
+ void SetRow(int row);
+ void SetCol(int col);
+ bool IsInBounds(int min, int max);
+ bool GetAdjacentCoordinates(Coordinates starting, Orientation orientation, int count);
+ static Coordinates(std::string &coordinates);
}
*/
