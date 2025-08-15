#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : Shape
{
private:
    int x;
    int y;
public:
    Rectangle(int x, int y);
    
    void saveState() override;
    void draw() override;
    void undo() override;
};

#endif