#include <memory>
#include <utility>

void func(std::unique_ptr<int> ptr)
{

}

int main()
{
    auto ptr = std::make_unique<int>();
    func(std::move(ptr));
}