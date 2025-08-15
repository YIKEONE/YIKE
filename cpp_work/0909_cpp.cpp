/*
20240909
练习目的：熟练使用模板类和vector
练习题目：编写一个C++程序，实现一个简单的栈（Stack）类，包括基本操作：push（压栈）、pop（出栈）、peek（查看栈顶元素但不移除）
和isEmpty（检查栈是否为空）。使用模板类，使其能够存储任意类型的数据。*/
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T>
class Stack
{
private:
    std::vector<T> stack;
public:
    bool isEmpty() const
    {
        return stack.empty();
    }
    void push(const T &element)
    {
        stack.emplace_back(element);
    }
    T pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("pop form empty stack");
        }
        T topElement = stack.back();
        stack.pop_back();
        return topElement;
    }
    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("peek form empty stack");
        }
        return stack.back();
    }
    size_t size() const
    {
        return stack.size();
    }
};
int main()
{
    Stack<int> intStack;
    for (size_t i = 0; i < 5; ++i)
    {
        intStack.push(i);
    }

    while (!intStack.isEmpty())
    {
        int peekNum = intStack.peek();
        std::cout << "peekNum: " << peekNum << std::endl;
        int popNum = intStack.pop();
        std::cout << "popNum: " << popNum << std::endl;
    }
}