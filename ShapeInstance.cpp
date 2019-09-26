//
// Created by ruben on 25/09/2019.
//

#include "ShapeInstance.h"
#include <ncurses.h>

ShapeInstance::ShapeInstance(const std::list<mathfu::vec2i> &shape, const mathfu::vec2i &origin) : shape(shape),
                                                                                                   origin(origin) {}

void ShapeInstance::draw() const {
    for (const mathfu::vec2i &point : shape) {
        mvaddch(origin.y + point.y, origin.x + point.x, 'x');
    }
}
