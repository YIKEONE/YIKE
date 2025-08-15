#include "context.h"
#include "DiscountStrategy.h"
#include <memory>
#include <utility>

int main()
{
    auto noDisStrategy = std::make_unique<NoDiscount>();
    auto fixedDisStrategy = std::make_unique<FixedDiscount>();
    Product noDis(std::move(noDisStrategy));
    noDis.execute();
    Product fixDis(std::move(fixedDisStrategy));
    fixDis.execute();
}
