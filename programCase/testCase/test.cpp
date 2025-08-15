#include <iostream>

class Widget
{
private:
    /* data */
    enum { ASPECT_RATIO = 5, ASPECT_RADIO = 6 };
    int arr[ASPECT_RATIO];
public:
    Widget(); // default constructor ctor
    Widget(const Widget& widget); // copy constructor
    Widget& operator=(const Widget& widget); // assignment operator constructor

    ~Widget() {} //destructor dtor
};

int main()
{
    Widget w1; // default constructor
    Widget w2(w1); // copy constructor
    // 区分拷贝构造和拷贝赋值
    // 当有新对象创建的时候, 肯定会有构造
    // 因为 explicit禁止了隐式调用拷贝构造函数。
    Widget widget = w1; // copy constructor
    // 反之, 当没有的时候, 则就是赋值
    w1 = w2; // assignment operator
}

class Base
{
private:
    /* data */
    void init()
    {
        initMethod();
    }
public:
    Base() { init(); }
    ~Base() {}

    void initMethod() {}
};

class Derived : public Base
{
private:
public:
    Derived() : Base() {}
    ~Derived() {}
};