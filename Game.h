//
// Created by ruben on 30/09/2019.
//

#ifndef TETROMINOES_GAME_CMD_GAME_H
#define TETROMINOES_GAME_CMD_GAME_H


#include <mathfu/glsl_mappings.h>
#include <vector>
#include "ShapeInstance.h"

class Game {
public:
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

    ShapeInstance generate_shape_instance(const std::vector<std::list<mathfu::vec2i>> &shapes);
    void play();
    void update();
    void draw();
    static int random_int(int max);
};


#endif //TETROMINOES_GAME_CMD_GAME_H
