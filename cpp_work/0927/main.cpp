#include "Logger_hungry.h"
#include "Logger_lazy.h"

int main()
{
    Logger_hungry::getInstance()->log("hungry guy");
    Logger_hungry::getInstance()->log("hungry guy~");
    Logger_lazy::getInstance()->log("lazy guy");
    Logger_lazy::getInstance()->log("lazy guy~");
}