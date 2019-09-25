#include <ncurses.h>
#include "mathfu/vector.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    endwin();
    return 0;
}