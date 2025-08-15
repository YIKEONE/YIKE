/*练习目的：由于工厂模式很常用，大家必须掌握，所以，今天还是练习工厂方法模式
练习题目：假设我们有个工厂要生产手机，手机的类型有苹果手机，小米手机，我们要按照工厂模式，设计这个需求。具体要求如下：
题目要求
首先我们应该定义一个抽象产品类PhoneInterface。
然后根据抽象产品类来实现具体的产品类，假设我们有苹果手机和小米手机。
定义一个抽象的工厂类，来定义具体工厂的统一接口
然后定义一个苹果手机工厂，用于生产苹果手机，再定义一个小米手机工厂，用于生产苹果手机，那么这两个工厂就是具体工厂角色
内存管理方面，要使用智能指针。
编写一个主函数，演示如何使用不同工厂。*/
#ifndef PHONEINTERFACE_H
#define PHONEINTERFACE_H

#include "Phone.h"
#include <memory>

class PhoneInterface
{
public:
    std::unique_ptr<Phone> phone;
    virtual ~PhoneInterface() = default;
    virtual std::unique_ptr<Phone> productPhone() =0;
};

class IPhoneFactory : public PhoneInterface
{
public:
    IPhoneFactory(/* args */) {}
    ~IPhoneFactory() {}
    std::unique_ptr<Phone> productPhone() override;
};

#endif