#include "Potion.h"

Potion::Potion()
{
    id = 0;
    name = "";
    healAmount = 0;
}

Potion::Potion(int id, const std::string& name, int healAmount)
{
    this->id = id;
    this->name = name;
    this->healAmount = healAmount;
}

int Potion::getId() const
{
    return id;
}

std::string Potion::getName() const
{
    return name;
}

int Potion::getHealAmount() const
{
    return healAmount;
}
