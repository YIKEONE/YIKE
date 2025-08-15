#include "shape.h"
#include <memory>
#include <iostream>

Circle::Circle(double radius) : radius_(radius) {}

Circle::Circle(const Circle &circle) : radius_(circle.radius_) {}

std::unique_ptr<Shape> Circle::clone() const
{
    return std::make_unique<Circle>(*this);
}

void Circle::draw() const
{
    std::cout << "circle drawing\n";
}

Rectangle::Rectangle(double weight, double height) : weight_(weight), height_(height) {} 

Rectangle::Rectangle(const Rectangle &rectangle) : weight_(rectangle.weight_), height_(rectangle.height_) {}

std::unique_ptr<Shape> Rectangle::clone() const
{
    return std::make_unique<Rectangle>(*this);
}

void Rectangle::draw() const
{
    std::cout << "rectangle drawing\n";
}