#ifndef BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_
#define BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_

class GameBoard {
};

#endif//BATTLESHIP_INCLUDE_BATTLESHIP_GAMEBOARD_H_

/*
class GameBoard{
    - vector<Tile> tiles_
    + static const int DEFAULT_BOARD_SIZE = 12;
    + GameBoard();
    + GameBoard(int size);
    + vector<Tile> GetTiles()
    + void SetTiles(vector<Tile> tiles)
    + int GetSize();
    + void SetSize();
    + static bool IsInsideBoard(int ship_width, Orientation orientation, Coordinates starting_position);
    + bool OverlapsShip(int ship_width, Orientation orientation, Coordinates &startingPositions);
    + bool ReceiveAttack(Coordinates target)
    + vector<Tile> ScanSurrounding(Coordinates starting_position, int range = 1);
    + bool ReceiveAttack(Coordinates target);
    + void ChangeTileType(Coordinates target, OccupationType type);
    + bool MoveShip(Coordinate origin, Coordinates target, int width, Orientation orientation);
}
*/