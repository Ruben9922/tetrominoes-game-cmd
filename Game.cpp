//
// Created by ruben on 30/09/2019.
//

#include <random>
#include "Game.h"
#include <ncurses.h>

ShapeInstance Game::generate_shape_instance(const std::vector<std::list<mathfu::vec2i>> &shapes) {
    int shape_index = random_int(shapes.size() - 1);
    std::list<mathfu::vec2i> shape = shapes[shape_index];
    return {shape, mathfu::vec2i(0, 0)};
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
        moving_shape_instance = generate_shape_instance(shapes);
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
