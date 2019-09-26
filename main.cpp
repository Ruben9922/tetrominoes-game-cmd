#include <ncurses.h>
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "ShapeInstance.h"
#include <list>
#include <vector>
#include <random>

int random_int(int max);

void update(std::list<ShapeInstance> &shape_instances);

void draw(const std::list<ShapeInstance> &shape_instances);

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    std::vector<std::list<mathfu::vec2i>> shapes = {
            {
                    {0, 0},
                    {0, 1},
                    {0, 2},
                    {0, 3},
            },
            {
                    {1, 0},
                    {0, 0},
                    {0, 1},
                    {0, 2},
            },
            {
                    {0, 0},
                    {0, 1},
                    {0, 2},
                    {1, 2},
            },
            {
                    {0, 0},
                    {0, 1},
                    {1, 0},
                    {1, 1},
            },
            {
                    {0, 0},
                    {0, 1},
                    {1, 1},
                    {1, 2},
            },
            {
                    {0, 0},
                    {0, 1},
                    {0, 2},
                    {1, 1},
            },
            {
                    {0, 1},
                    {0, 2},
                    {1, 0},
                    {1, 1},
            },
    };

    std::list<ShapeInstance> shape_instances;
    int shape_index = random_int(shapes.size());
    std::list<mathfu::vec2i> shape = shapes[shape_index];
    shape_instances.emplace_back(shape, mathfu::vec2i(0, 0));

    do {
        timeout(500);
        update(shape_instances);
        draw(shape_instances);
        getch();
    } while (true);

    endwin();
    return 0;
}

int random_int(int max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, max);

    int random_number = distr(eng);
    return random_number;
}

void update(std::list<ShapeInstance> &shape_instances) {
    for (ShapeInstance &shape_instance : shape_instances) {
        shape_instance.origin += {0, 1};
    }
}

void draw(const std::list<ShapeInstance> &shape_instances) {
    clear();

    for (const ShapeInstance &shape_instance : shape_instances) {
        for (const mathfu::vec2i &point : shape_instance.shape) {
            mvaddch(shape_instance.origin.y + point.y, shape_instance.origin.x + point.x, 'x');
        }
    }
}

// TODO: Consider switching to C++ version of Curses library (e.g. AnsiGL)
