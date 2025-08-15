#include "0911_complex.h"
#include <iostream>

int main() {
    complex::Complex c1(1, 2);
    complex::Complex c2(3, 4);
    auto c3 = c1 + c2;
    std::cout << "c3: " << c3 << std::endl;
}