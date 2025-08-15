/*20240923
练习目的：熟练掌握策略模式
练习题目：设计一个系统，用于计算不同类型商品的折扣。系统包含三种折扣策略：无折扣（NoDiscount）、固定金额折扣（FixedDiscount）和百分比折扣（PercentageDiscount）。每种商品根据其促销策略计算最终价格。
题目要求
定义一个DiscountStrategy接口，包含applyDiscount方法，该方法接收原价并返回折扣后的价格。
实现上述三种折扣策略类。无折扣策略（NoDiscount）；固定金额折扣策略（FixedDiscount）；百分比折扣策略（PercentageDiscount）
定义一个Product类，包含价格和一个DiscountStrategy指针，用于存储商品的折扣策略。
编写一个主函数，演示如何使用不同策略来计算商品的价格。*/
#ifndef DISCOUTSTRATEGY_H
#define DISCOUTSTRATEGY_H

class DiscountStrategy
{
public:
    virtual ~DiscountStrategy() = default;
    virtual void applyDiscount() = 0;
};

class NoDiscount : public DiscountStrategy
{
public:
    void applyDiscount() override;
};

class FixedDiscount : public DiscountStrategy
{
public:
    void applyDiscount() override;
};

#endif//DISCOUTSTRATEGY_H