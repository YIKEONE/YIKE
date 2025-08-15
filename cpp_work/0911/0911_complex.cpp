#include "0911_complex.h"
#include <ostream>

namespace complex
{
    Complex::Complex(double r, double i) : real(r), imag(i) {}
    Complex::Complex(const Complex& other) : real(other.real), imag(other.imag) {}
    Complex::~Complex() {}
    Complex Complex::operator+(const Complex& other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }
    std::ostream& operator<<(std::ostream& os, const Complex& other)
    {
        os << other.real << (other.imag >= 0 ? "+" : "") << other.imag << "i";
        return os;
    }

} // namespace complex
