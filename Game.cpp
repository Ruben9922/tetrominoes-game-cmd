//
// Created by ruben on 30/09/2019.
//

#include <random>
#include "Game.h"
#include <ncurses.h>
#include <vector>
#include <list>
#include "mathfu/vector.h"
#include "mathfu/glsl_mappings.h"

ShapeInstance Game::generate_shape_instance() {
    int shape_index = random_int(shapes.size() - 1);
    std::list<mathfu::vec2i> shape = shapes[shape_index];

    mathfu::vec2i origin((COLS - shape_width(shape)) / 2, 0);

    return {shape, origin};
}

void Game::play() {
    draw();
    getch();

    bool prevent_update = false;
    do {
        if (!prevent_update) {
            update();
        }
        draw();

        int key = getch();
        switch (key) {
            case KEY_LEFT: {
                const mathfu::vec2i left = {-1, 0};
                if (moving_shape_instance.isShapeWithinScreenBounds(left) &&
                    !moving_shape_instance.checkForCollision(left, shape_instances)) {
                    moving_shape_instance.origin += left;
                }
                prevent_update = true;
                break;
            }
            case KEY_RIGHT: {
                const mathfu::vec2i right = {1, 0};
                if (moving_shape_instance.isShapeWithinScreenBounds(right) &&
                    !moving_shape_instance.checkForCollision(right, shape_instances)) {
                    moving_shape_instance.origin += right;
                }
                prevent_update = true;
                break;
            }
            default:
                prevent_update = false;
                break;
        }
    } while (true);
}

void Game::update() {
    const mathfu::vec2i down = {0, 1};
    if (moving_shape_instance.isShapeWithinScreenBounds(down) && !moving_shape_instance.checkForCollision(down, shape_instances)) {
        moving_shape_instance.origin += down;
    } else {
        shape_instances.push_back(moving_shape_instance);
        moving_shape_instance = generate_shape_instance();
    }
}

void Game::draw() {
    clear();

    for (const ShapeInstance &shape_instance_1 : shape_instances) {
        shape_instance_1.draw();
    }

    moving_shape_instance.draw();
}

int Game::random_int(int max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, max);

    int random_number = distr(eng);
    return random_number;
}

int Game::shape_width(const std::list<mathfu::vec2i> &shape) {
    auto[min, max] = std::minmax_element(shape.begin(), shape.end(),
                                         [](const mathfu::vec2i &v1, const mathfu::vec2i &v2) { return v1.x < v2.x; });
    return max->x - min->x + 1;
}
