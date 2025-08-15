#include <iostream>
#include <memory>
#include <vector>

class MyClass
{
private:
    int num_;
public:
    explicit MyClass(int num) : num_(num) {}
    void print() const {
        std::cout << num_ << std::endl;
    }
};

int main() {
    std::vector<std::unique_ptr<MyClass>> myClassVec;
    for (size_t i = 0; i <= 100; i += 10) {
        myClassVec.emplace_back(std::make_unique<MyClass>(i)); 
    }
    for (const auto& ptr : myClassVec) {
        ptr->print();
    }
    return 0;
}