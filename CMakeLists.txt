cmake_minimum_required(VERSION 3.10)
project(battaglia_navale)

set(CMAKE_CXX_STANDARD 11)

include_directories("include/battleship")
include_directories("src")

file(GLOB SOURCES "src/*.cpp" "src/*.hpp" "include/battleship/*.h")

add_executable("${PROJECT_NAME}" ${SOURCES} src/UserCommand.cpp)
