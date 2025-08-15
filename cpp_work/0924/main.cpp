#include "Pet.h"
#include "PetFactory.h"
#include <iostream>
#include <memory>

int main()
{
    auto catFactory = std::make_unique<CatFactory>();
    catFactory->createPet()->makeSound();

    auto dogFactory = std::make_unique<DogFactory>();
    dogFactory->createPet()->makeSound();

    auto birdFactory = std::make_unique<BirdFactory>();
    birdFactory->createPet()->makeSound();
}