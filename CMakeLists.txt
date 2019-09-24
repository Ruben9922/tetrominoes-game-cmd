cmake_minimum_required(VERSION 3.14)
project(tetrominoes_game_cmd)

set(CMAKE_CXX_STANDARD 14)

add_executable(tetrominoes_game_cmd main.cpp)
target_link_libraries(${PROJECT_NAME} ncurses)
