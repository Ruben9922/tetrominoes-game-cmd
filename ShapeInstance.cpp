//
// Created by ruben on 25/09/2019.
//

#include <list>
#include "mathfu/glsl_mappings.h"
#include "mathfu/vector.h"
#include "ShapeInstance.h"
#include <ncurses.h>
#include <algorithm>

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

bool ShapeInstance::checkForCollision(const mathfu::vec2i &translation,
                                      const std::list<ShapeInstance> &shape_instances) {
    ShapeInstance shape_instance_temp(*this);
    shape_instance_temp.origin += translation;

    for (const ShapeInstance &shape_instance : shape_instances) {
        std::list<mathfu::vec2i> shape_instance_temp_world;
        std::list<mathfu::vec2i> shape_instance_world;

        std::transform(shape_instance_temp.shape.begin(), shape_instance_temp.shape.end(),
                       std::back_inserter(shape_instance_temp_world),
                       [shape_instance_temp](const mathfu::vec2i &p) -> mathfu::vec2i {
                           return shape_instance_temp.origin + p;
                       });
        std::transform(shape_instance.shape.begin(), shape_instance.shape.end(),
                       std::back_inserter(shape_instance_world),
                       [shape_instance](const mathfu::vec2i &p) -> mathfu::vec2i {
                           return shape_instance.origin + p;
                       });

        bool collision = std::find_first_of(shape_instance_temp_world.begin(), shape_instance_temp_world.end(),
                                            shape_instance_world.begin(), shape_instance_world.end()) !=
                         shape_instance_temp_world.end();
        if (collision) {
            return true;
        }
    }
    return false;
}
