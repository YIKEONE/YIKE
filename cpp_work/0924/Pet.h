#ifndef PET_H
#define PET_H

class Pet
{
public:
    virtual ~Pet() = default;
    virtual void makeSound() const = 0;
};

class Dog : public Pet
{
public:
    Dog() {}
    ~Dog() {}

    void makeSound() const override;
};

class Cat : public Pet
{
public:
    Cat() {}
    ~Cat() {}

    void makeSound() const override;
};

class Bird : public Pet
{
public:
    Bird() {}
    ~Bird() {}

    void makeSound() const override;
};

#endif