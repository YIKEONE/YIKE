#include "Pet.h"
#include <iostream>

void Cat::makeSound() const
{
    std::cout << "cat miao~" << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "dog wong~" << std::endl;
}

void Bird::makeSound() const
{
    std::cout << "bird zha~" << std::endl;
}