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
    void draw() const;
    bool is_shape_within_screen_bounds(const mathfu::vec2i &translation);
    bool check_for_collision(const mathfu::vec2i &translation, const std::list<ShapeInstance> &shape_instances);
    void rotate();
};


#endif //TETROMINOES_GAME_CMD_SHAPEINSTANCE_H
