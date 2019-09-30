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
// TODO: Collision detection - prevent shapes from overlapping
