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

