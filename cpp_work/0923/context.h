#ifndef CONTEXT_H
#define CONTEXT_H

#include "DiscountStrategy.h"
#include <memory>

class Product
{
private:
    std::unique_ptr<DiscountStrategy> strategy_;
public:
    Product(std::unique_ptr<DiscountStrategy> strategy);
    ~Product() {}

    void execute();
};

#endif