#ifndef SHAPEEDITOR_H
#define SHAPEEDITOR_H

#include "shape.h"
#include <memory>

class ShapeEditor
{
private:
    std::unique_ptr<Shape> copyBak;
public:
    void copy(const Shape *shape);

    void past();
};

#endif //SHAPEEDITOR_H