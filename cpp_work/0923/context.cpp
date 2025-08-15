#include "context.h"
#include <memory>
#include <utility>
#include <vector>

Product::Product(std::unique_ptr<DiscountStrategy> strategy) : strategy_(std::move(strategy)) {}

void Product::execute()
{
    strategy_->applyDiscount();
}