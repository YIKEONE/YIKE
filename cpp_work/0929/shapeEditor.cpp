#include "shapeEditor.h"
#include <iostream>

void ShapeEditor::copy(const Shape *shape)
{
    if (shape)
    {
        this->copyBak = shape->clone();
    }
    
}

void ShapeEditor::past()
{
    if (!this->copyBak)
    {
        std::cout << "copyBak is empty";
        return;
    }
    this->copyBak->draw();
}