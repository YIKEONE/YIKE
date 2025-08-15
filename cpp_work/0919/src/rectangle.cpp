#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(int x, int y) : x(x), y(y) {}

void Rectangle::saveState()
{
    std::cout << "save Rectangle" << std::endl;
}

void Rectangle::draw() 
{
    std::cout << "draw Rectangle" << std::endl;
}

void Rectangle::undo()
{
    std::cout << "undo Rectangle" << std::endl;
}

