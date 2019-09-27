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

bool isShapeWithinScreenBounds(ShapeInstance shape_instance, const mathfu::vec2i &translation);

void draw(const std::list<ShapeInstance> &shape_instances, const ShapeInstance &shape_instance);

ShapeInstance generate_shape_instance(const std::vector<std::list<mathfu::vec2i>> &shapes);

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(500);

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

    draw(shape_instances, moving_shape_instance);
    getch();

    bool prevent_update = false;
    do {
        if (!prevent_update) {
            update(shape_instances, moving_shape_instance, shapes);
        }
        prevent_update = false;
        draw(shape_instances, moving_shape_instance);

        int key = getch();
        if (key != ERR) {
            prevent_update = true;
        }
        switch (key) {
            case KEY_LEFT: {
                const mathfu::vec2i left = {-1, 0};
                if (isShapeWithinScreenBounds(moving_shape_instance, left)) {
                    moving_shape_instance.origin += left;
                }
                break;
            }
            case KEY_RIGHT: {
                const mathfu::vec2i right = {1, 0};
                if (isShapeWithinScreenBounds(moving_shape_instance, right)) {
                    moving_shape_instance.origin += right;
                }
                break;
            }
            default:
                break;
        }
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
    const mathfu::vec2i down = {0, 1};
    if (isShapeWithinScreenBounds(shape_instance, down)) {
        shape_instance.origin += down;
    } else {
        shape_instances.push_back(shape_instance);
        shape_instance = generate_shape_instance(shapes);
    }
}

bool isShapeWithinScreenBounds(ShapeInstance shape_instance, const mathfu::vec2i &translation) {
    shape_instance.origin += translation;
    for (const mathfu::vec2i &local_point : shape_instance.shape) {
        mathfu::vec2i world_point = shape_instance.origin + local_point;

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
