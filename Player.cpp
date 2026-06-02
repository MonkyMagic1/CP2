#include "Player.h"

Player::Player()
{
    health = 100;
    currentLocationId = 1;
}

int Player::getHealth() const
{
    return health;
}

void Player::setHealth(int health)
{
    this->health = health;

    if (this->health < 0) {
        this->health = 0;
    }

    if (this->health > 100) {
        this->health = 100;
    }
}

int Player::getCurrentLocationId() const
{
    return currentLocationId;
}

void Player::setCurrentLocationId(int locationId)
{
    currentLocationId = locationId;
}

void Player::takeDamage(int damage)
{
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void Player::heal(int amount)
{
    health += amount;
    if (health > 100) {
        health = 100;
    }
}

bool Player::isAlive() const
{
    return health > 0;
}

void Player::addPotionId(int potionId)
{
    potionIds.push_back(potionId);
}

bool Player::removePotionId(int potionId)
{
    for (std::vector<int>::iterator it = potionIds.begin(); it != potionIds.end(); ++it) {
        if (*it == potionId) {
            potionIds.erase(it);
            return true;
        }
    }

    return false;
}

void Player::clearPotions()
{
    potionIds.clear();
}

std::vector<int> Player::getPotionIds() const
{
    return potionIds;
}