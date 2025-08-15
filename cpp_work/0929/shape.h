/*练习目的：练习原型模式
练习题目：设计一个图形编辑器，其中包含多种形状（如圆形、矩形、三角形）。编辑器需要支持复制任意形状并粘贴到画布上的功能。为了实现这一功能，我们将使用原型模式（Prototype Pattern），允许我们创建一个对象的副本，同时无需知道对象的类。
要求：
1. 定义一个形状基类Shape，包含纯虚函数 clone() 用于创建对象的副本。纯虚函数draw()用于描画图形。
2. 派生 Circle、Rectangle 和 Triangle 类，并实现 clone() 和draw()方法。
3. 创建一个 ShapeEditor 类，包含复制copy(Shape) 和粘贴形状paste() 的方法。*/

#ifndef SHAPE_H
#define SHAPE_H

#include <memory>

class Shape
{
public:
    virtual ~Shape() = default;

    virtual std::unique_ptr<Shape> clone() const = 0;

    virtual void draw() const = 0;
};

class Circle : public Shape
{
private:
    double radius_;
public:
    Circle(double radius);

    Circle(const Circle &circle);

    std::unique_ptr<Shape> clone() const override;

    void draw() const override;
};

class Rectangle : public Shape
{
private:
    double weight_;

    double height_;
public:
    Rectangle(double weight, double height);

    Rectangle(const Rectangle &rectanlg);

    std::unique_ptr<Shape> clone() const override;

    void draw() const override;
};

#endif