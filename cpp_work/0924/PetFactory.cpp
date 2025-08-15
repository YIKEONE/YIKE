#include "PetFactory.h"
#include "Pet.h"
#include <memory>

std::unique_ptr<Pet> CatFactory::createPet()
{
    return std::make_unique<Cat>();
}

std::unique_ptr<Pet> DogFactory::createPet()
{
    return std::make_unique<Dog>();
}

std::unique_ptr<Pet> BirdFactory::createPet()
{
    return std::make_unique<Bird>();
}