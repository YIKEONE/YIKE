#ifndef COMPLEX_H
#define COMPLEX_H

#include <ostream>
namespace complex
{
    class Complex
    {
    private:
        double real;
        double imag;
    public:
        Complex(double r = 0.0, double i = 0.0);

        Complex(const Complex &other);

        ~Complex();

        Complex operator+(const Complex &other) const;

        friend std::ostream& operator<<(std::ostream& os, const Complex& other);
    };
} // namespace complex
#endif