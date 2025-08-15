#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : Shape
{
private:
    int radius;
public:
    Circle(int r);
    
    void saveState() override;
    void draw() override;
    void undo() override;
};

#endif