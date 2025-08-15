#include "circle.h"
#include <iostream>

Circle::Circle(int r) : radius(r) {}

void Circle::saveState()
{
    std::cout << "save Circle" << std::endl;
}

void Circle::draw() 
{
    std::cout << "draw Circle" << std::endl;
}

void Circle::undo()
{
    std::cout << "undo Circle" << std::endl;
}

