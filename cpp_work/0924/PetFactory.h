/*练习目的：熟练掌握工厂方法模式
练习题目：我们需要使用工厂方法模式来创建不同类型的宠物（如狗、猫、鸟等）。每种宠物都有自己独特的行为（如狗会叫，猫会喵喵叫，鸟会唱歌）。用户可以根据输入的类型来选择并获取相应的宠物对象。
题目要求
定义一个Pet接口，包含makeSound方法。
完成三种宠物的实现类。狗（Dog）；猫（Cat）；鸟（Bird）
定义一个PetFactory接口，createPet方法。
完成三种宠物的工厂的实现类。DogFactory、CatFactory、BirdFactory
编写一个主函数，演示如何使用不同工厂。
内存管理方面，要使用智能指针。*/

#ifndef PETFACTORY_H
#define PETFACTORY_H

#include "Pet.h"
#include <memory>

class PetFactory
{
public:
    virtual ~PetFactory() = default;
    virtual std::unique_ptr<Pet> createPet() = 0;
};

class CatFactory : PetFactory
{
public:
    CatFactory() {}
    ~CatFactory() {}
    std::unique_ptr<Pet> createPet() override;
};

class DogFactory : PetFactory
{
public:
    DogFactory() {}
    ~DogFactory() {}
    std::unique_ptr<Pet> createPet() override;
};

class BirdFactory : PetFactory
{
public:
    BirdFactory() {}
    ~BirdFactory() {}
    std::unique_ptr<Pet> createPet() override;
};

#endif