#include "shape.h"
#include "shapeEditor.h"
#include <memory>
#include <utility>

int main()
{
    auto circle = std::make_unique<Circle>(6);
    auto rec = std::make_unique<Rectangle>(1, 2);

    ShapeEditor se;
    se.copy(circle.get());
    se.past();

    se.copy(rec.get());
    se.past();

    se.copy(circle.get());
    se.past();
}