#include "Chest.h"

Chest::Chest()
{
    id = 0;
    opened = false;
}

Chest::Chest(int id, bool opened)
{
    this->id = id;
    this->opened = opened;
}

int Chest::getId() const
{
    return id;
}

bool Chest::isOpened() const
{
    return opened;
}

void Chest::openChest()
{
    opened = true;
}

void Chest::addPotionId(int potionId)
{
    potionIds.push_back(potionId);
}

std::vector<int> Chest::getPotionIds() const
{
    return potionIds;
}