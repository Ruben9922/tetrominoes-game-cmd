//
// Created by ruben on 25/09/2019.
//

#ifndef TETROMINOES_GAME_CMD_SHAPEINSTANCE_H
#define TETROMINOES_GAME_CMD_SHAPEINSTANCE_H


#include <list>
#include <mathfu/glsl_mappings.h>

class ShapeInstance {
public:
    std::list<mathfu::vec2i> shape;
    mathfu::vec2i origin{0, 0};

    ShapeInstance(const std::list<mathfu::vec2i> &shape, const mathfu::vec2i &origin);
};


#endif //TETROMINOES_GAME_CMD_SHAPEINSTANCE_H