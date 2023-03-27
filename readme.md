# Battleship

## Game rules

Each player has two game grids consisting of 12x12 squares. One grid is for defense, used to position their naval units,
and the other is for attack, used to track hits (X) or misses (O) against the opponent's units. Additionally, each
player has 8 units of three different types: Battleship (B), Support Ship (S), and Submarine (E).
Example:

```
  1  2  3  4  5  6  7  8  9  10 11 12	  1  2  3  4  5  6  7  8  9  10 11 12
A ~  ~  ~  C  C  C  C  C  C  ~  ~  ~  A	A ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  A
B ~  ~  ~  ~  ~  ~  ~  ~  C  ~  ~  ~  B	B ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  B
C ~  ~  ~  ~  ~  ~  ~  ~  C  ~  ~  ~  C	C ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  C
D ~  S  S  S  ~  ~  ~  ~  C  E  ~  ~  D	D ~  ~  ~  ~  ~  ~  ~  X  ~  ~  ~  ~  D
E ~  ~  ~  ~  ~  ~  ~  ~  C  ~  ~  ~  E	E ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  E
F S  S  S  ~  ~  ~  S  S  S  ~  ~  ~  F	F ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  F
G ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  G	G ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  G
H ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  H	H ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  H
I ~  E  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  I	I ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  I
L ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  L	L ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  L
M C  C  C  C  C  ~  ~  ~  ~  ~  ~  ~  M	M ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  M
N ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  N	N ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  N
  1  2  3  4  5  6  7  8  9  10 11 12	  1  2  3  4  5  6  7  8  9  10 11 12
```

## Naval Units

All naval units can perform an action, which differs depending on the type of unit. In addition, each unit has a
specific size that is also equivalent to its initial armor. When all the squares occupied by a unit are hit, the unit is
considered sunk. Armor and size are initially equivalent. As the unit is hit, the armor decreases while the size remains
the same. Below are the characteristics of each naval unit:

| Naval unit             | Quantity | Size | Armor | Action          |
|------------------------|----------|------|-------|-----------------|
| Battleship             | 3        | 5    | 5     | Fire            |
| Support Ship           | 3        | 3    | 3     | Move and repair |
| Exploration  Submarine | 2        | 1    | 1     | Move and search |

The actions that the different naval units can perform are listed below:

- **Fire**: the battleship fires at specific coordinates. The shot hits if the targeted square is occupied by an enemy
  unit.
  If the target unit's armor reaches 0 (all squares where the unit is present have been hit), the target unit is sunk.
- **Move and repair**: the support ship moves to the received coordinates. The square must not already be occupied. Once
  it
  has moved, it supports all player units within a 3x3 area, considering the support ship as the center. The units in
  this area will be completely repaired (i.e., their armor returns to the initial value). Just one square inside the
  area is sufficient for the entire unit to receive support. The supporting ship cannot benefit from its own repairs (
  i.e., it needs the help of another support ship to be repaired).
- **Move and search**: the exploration submarine moves to the received coordinates. The square must not already be
  occupied.
  Once it has moved, it launches a sonar pulse that reveals if there are enemy units within a 5x5 area, considering the
  submarine as the center. Squares where there are enemy units (or parts of enemy units) are marked on the attack grid
  with the character Y.

### Note on movement

The movement is relative to the central square of the unit. Each movement must be valid, that is, the unit after the
movement must be entirely within the grid and cannot overlap with other units of the player. There is no rotation, the
units translate rigidly on the grid.

## Players and turns

There are always and only two players. One of the two players can be human. At the beginning of the game, all players
place their units on their own defense grid. The program randomly decides which player starts the game. In their turn,
the player must perform an action with only one of their units. Once the action is performed, the turn passes to the
other player.

### Game commands

Each player performs an action on one of their units, using a command with the following syntax:

`XYOrigin XYTarget`

`XYOrigin` corresponds to the coordinates of the unit that must perform the action (the coordinates that identify a unit
are those of the central square). `XYTarget` corresponds to the coordinates that are the target of the unit's action. In
the case of a battleship, they correspond to the target square for fire; in the case of support ships and exploration
submarines, they correspond to the destination square of the move.

With a special command (AA AA), it is possible to clear sonar sightings (character Y) on the attack grid (as units have
moved, sightings may not be up to date). This command does not use the turn's move.

### Ships placement

The initial placement of naval units is done at the beginning of the game. In this phase of the game, the program asks
the player to provide the coordinates of the bow and stern of each of their units. The units can only be arranged
horizontally or vertically and cannot overlap (not even in the case of submarines, for simplicity).

### Visualization

In the case of a game with one player, it is possible to request the program to display the defense and attack grids
using a special command:

`XX XX`

The display is carried out by printing a character for each naval unit in the defense grid and for each shot fired and
sonar detection in the attack grid. Each grid must have the coordinates as shown in Figure 1. The
characters on the grids have the following code:

| Attack grid           |     | Defence grid    |     |
|-----------------------|-----|-----------------|-----|
| Battleship            | C   | Hit unit        | X   |
| Support ship          | S   | Water           | O   |
| Exploration submarine | E   | Sonar detection | Y   |

If there is no unit, shot or sonar detection present, a tilde `~` is printed. The squares corresponding to hit parts
of a unit are marked with a lowercase letter.

### Game replay

The project is accompanied by a module (consisting of a separate executable, see next point) for replaying the
game, done by reading the corresponding log. The replay is made by printing the two game grids for each turn. Printing
is done on screen, with a suitable pause (e.g. 1 second) between one turn and the next, or on file - in this case
writing takes place without pauses.

### Executables

The project generates two executables:
- The game executable, called "battleship", which must manage command line arguments according to the following scheme:
  - pc argument: player vs. computer game (p stands for player, c for computer)
  - cc argument: computer vs. computer game
- The replay executable, called "replay", which accepts command line arguments according to the following scheme:
  - `v [log_file_name]`: prints the replay of the indicated log file to the screen
  - `f [log_file_name] [replay_output_file_name]`: writes the replay of the indicated log file to a file.
## Compilation and execution

### Note before execution:

The log files are located in the game_logs folder
Files starting with cc are for computer vs computer matches, while files starting with pc are for player vsGame rules
Each player has two game grids consisting of 12x12 squares. One grid is for defense, used to position their naval units,
and the other is for attack, used to track hits (X) or misses (O) against the opponent's units. Additionally, each
player has 8 units of three different types: Battleship (B), Support Ship (S), and Submarine (E).
computer matches.
As requested by the project, we generated two log files for the two different types of matches, respectively:
`cc_game_20230116194828.txt` and `pc_game_20230116195426.txt`

### Compile & Execute

Naval Units
All naval units can perform an action, which differs depending on the type of unit. In addition, each unit has a
specific size that is also equivalent to its initial armor. When all the squares occupied by a unit are hit, the unit is
considered sunk. Armor and size are initially equivalent. As the unit is hit, the armor decreases while the size remains
the same. Below are the characteristics of each naval unit:
To compile the project, run the following commands:

```bash
# Create the build directory if it does not exist
mkdir -p build

# Move to the build directory
cd build

# Compile the project with cmake
cmake ../

cmake --build .

# To run the battleship executable, run
./battleship pc


# To replay a log file with screen visualization, run:

./replay v ../game_logs/cc_game_20230116194828.txt

# To replay a log file with output printed to a file, use:

./replay f ../game_logs/cc_game_20230116194828.txt output.txt
```

## Documentation

In addition to the documentation within the project code, we have generated a PDF with documentation for the main
classes of the project and diagrams of the interactions between the various classes. The file is located in
docs/docs.pdf. Additionally, a UML class diagram is available and can be found in docs/uml.svg.

## Notes on design

The project is structured into several classes, which can be grouped as follows:

- Ship management: Ship, Battleship, Submarine, and SupportShip classes
- Ship position and movement management: Board, FiringBoard, GameBoard, and Coordinates classes
- Gameplay management: Player, Game classes
- Replay functionality management: GameRecorder class
- User command management: UserCommand and Game classes

Due to the way we designed the program, it would not have made much sense to make the Ship class a pure virtual class
and derive other types of ships from it, mainly because ships have no knowledge of their context. Actions such as
MoveShip could not be implemented inside a derived class of Ship because the class itself has no knowledge of which
other ships are positioned on the GameBoard, nor does it have access to the GameBoard. The problem could be circumvented
by passing a reference to GameBoard as a parameter, but doing so would not really leverage the polymorphism received by
being an abstract class. This, among other reasons, led us to use the Ship derivatives simply as a tool to differentiate
the various types of ships and make their existence more explicit. When it made sense, we included static methods inside
the derivatives to perform actions strictly related to the ship type (e.g., SupportShip and Submarine).

Instead, the main functionalities, such as the management of received shots, were implemented directly in the Ship
class.

As can be seen from the code, we tried as much as possible to not expose either the FireBoard or GameBoard to the user
of the Player class, which led to the creation of various helper methods in the Player class with the same names as the
associated methods present in GameBoard/FireBoard. In our opinion, this is a good compromise to ensure a certain level
of information hiding.

If there are general utility functions used in multiple contexts but not strictly related to any class, we placed them
in Utility.h.