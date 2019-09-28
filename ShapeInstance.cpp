//
// Created by ruben on 25/09/2019.
//

#include <random>
#include <vector>
#include <list>
#include "mathfu/glsl_mappings.h"
#include "mathfu/vector.h"
#include "ShapeInstance.h"
#include <ncurses.h>

ShapeInstance::ShapeInstance(const std::list<mathfu::vec2i> &shape, const mathfu::vec2i &origin) : shape(shape),
                                                                                                   origin(origin) {}

void ShapeInstance::draw() const {
    for (const mathfu::vec2i &point : shape) {
        mvaddch(origin.y + point.y, origin.x + point.x, 'x');
    }
}

bool ShapeInstance::isShapeWithinScreenBounds(const mathfu::vec2i &translation) {
    ShapeInstance shape_instance_temp(*this);
    shape_instance_temp.origin += translation;
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