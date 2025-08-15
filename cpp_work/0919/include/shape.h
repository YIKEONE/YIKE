#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:
    virtual ~Shape() = default;

    void execute();

    virtual void undo() = 0;
    virtual void saveState() = 0;
    virtual void draw() = 0;
};

#endif