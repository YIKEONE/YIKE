#include "DiscountStrategy.h"
#include <iostream>

void NoDiscount::applyDiscount()
{
    std::cout << "NoDiscount" << std::endl;
}

void FixedDiscount::applyDiscount()
{
    std::cout << "FixedDiscount" << std::endl;
}