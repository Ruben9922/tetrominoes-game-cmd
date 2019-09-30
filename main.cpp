#include <ncurses.h>
#include "Game.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(500);
    curs_set(0);

    Game game;
    game.play();

    endwin();
    return 0;
}

// TODO: Consider switching to C++ version of Curses library (e.g. AnsiGL)
// TODO: Sort out accessibility in Game class
// TODO: Use C++ library for "timer"
// TODO: Consider creating GameObject class (for features like drawing and collision detection) and have ShapeInstance inherit from it
// TODO: Add scoring
// TODO: Add menu and "game over" screens
// TODO: Allow rotating moving shape instance
// TODO: Properly implement being able to quickly move the shape downwards (in the 2 different ways)
// TODO: Make size of playable area fixed and mark the "un-playable" area
// TODO: Make completely filled horizontal line disappear and incorporate into scoring
