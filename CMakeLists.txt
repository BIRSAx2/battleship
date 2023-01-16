cmake_minimum_required(VERSION 3.10)
project(Battleship LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")

include_directories(src include/battleship)

file(GLOB BATTLESHIP_SOURCES "src/*.cpp")
file(GLOB BATTLESHIP_HEADERS "include/battleship/*.h")

LIST(REMOVE_ITEM BATTLESHIP_SOURCES src/battaglia_navale.cpp src/replay.cpp)

# Creates a library
add_library(battleship_game STATIC ${BATTLESHIP_SOURCES})
target_include_directories(battleship_game PUBLIC ${BATTLESHIPS_HEADERS})


# Creates battaglia_navale executable
add_executable(battaglia_navale src/battaglia_navale.cpp)
target_link_libraries(battaglia_navale PRIVATE battleship_game)


# Creates replay executable
add_executable(replay src/replay.cpp)
target_link_libraries(replay PRIVATE battleship_game)