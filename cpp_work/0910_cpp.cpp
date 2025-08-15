#include <algorithm>
#include <iostream>
#include <memory>
namespace cpp_0910
{
    class Shape
    {
    public:
        virtual void draw() = 0;
        virtual ~Shape() {}
    };

    class Rectangle : public Shape
    {
    private:
        int width_, height_;
    public:
        Rectangle(int w, int h) : width_(w), height_(h) {}
        ~Rectangle() {}
        void draw() override
        {
            std::cout << "Rectangle draw" << std::endl;
        }
    };

    class Circle : Shape
    {
    private:
        int radius_;
    public:
        Circle(int r) : radius_(r) {}
        ~Circle() {}
        void draw() override
        {
            std::cout << "Circle draw" << std::endl;
        }
    };

} // namespace cpp_0910

int main()
{
    std::unique_ptr<cpp_0910::Shape> rec(new cpp_0910::Rectangle(5, 6));
    std::unique_ptr<cpp_0910::Circle> cir(new cpp_0910::Circle(5));
    rec->draw();
    cir->draw();
}


class Solution {
public:
    int RomanToInt(std::string s) {
        
    }
    private:
    std::unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

};