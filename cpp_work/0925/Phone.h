#ifndef PHONE_H
#define PHONE_H

class Phone
{
private:
public:
    virtual ~Phone() = default;
};

class IPhone : public Phone
{
private:
public:
    IPhone(/* args */) {}
    ~IPhone() {}
};

#endif