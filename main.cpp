#include <ncurses.h>
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"
#include "ShapeInstance.h"
#include <list>
#include <vector>
#include <random>

int random_int(int max);

void update(std::list<ShapeInstance> &shape_instances, ShapeInstance &shape_instance,
            const std::vector<std::list<mathfu::vec2i>> &shapes);

bool isShapeWithinScreenBounds(const ShapeInstance &shape_instance);

void draw(const std::list<ShapeInstance> &shape_instances, const ShapeInstance &shape_instance);

ShapeInstance generate_shape_instance(const std::vector<std::list<mathfu::vec2i>> &shapes);

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
    ShapeInstance moving_shape_instance = generate_shape_instance(shapes);

    do {
        timeout(500);
        update(shape_instances, moving_shape_instance, shapes);
        draw(shape_instances, moving_shape_instance);
        getch();
    } while (true);

    endwin();
    return 0;
}

ShapeInstance generate_shape_instance(const std::vector<std::list<mathfu::vec2i>> &shapes) {
    int shape_index = random_int(shapes.size());
    std::list<mathfu::vec2i> shape = shapes[shape_index];
    return {shape, mathfu::vec2i(0, 0)};
}

int random_int(int max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, max);

    int random_number = distr(eng);
    return random_number;
}

void update(std::list<ShapeInstance> &shape_instances, ShapeInstance &shape_instance,
            const std::vector<std::list<mathfu::vec2i>> &shapes) {
    if (isShapeWithinScreenBounds(shape_instance)) {
        shape_instance.origin += {0, 1};
    } else {
        shape_instances.push_back(shape_instance);
        shape_instance = generate_shape_instance(shapes);
    }
}

bool isShapeWithinScreenBounds(const ShapeInstance &shape_instance) {
    ShapeInstance shape_instance_temp(shape_instance);
    shape_instance_temp.origin += {0, 1};
    for (const mathfu::vec2i &local_point : shape_instance_temp.shape) {
        mathfu::vec2i world_point = shape_instance_temp.origin + local_point;

        // Check computed WC point is actually within the screen bounds
        bool withinBounds = world_point.x >= 0 && world_point.x < COLS && world_point.y >= 0 && world_point.y < LINES;
        if (!withinBounds) {
            return false;
        }
    }
    return true;
}

void draw(const std::list<ShapeInstance> &shape_instances, const ShapeInstance &shape_instance) {
    clear();

    for (const ShapeInstance &shape_instance_1 : shape_instances) {
        shape_instance_1.draw();
    }

    shape_instance.draw();
}

// TODO: Consider switching to C++ version of Curses library (e.g. AnsiGL)
