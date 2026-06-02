#ifndef PLAYER_H
#define PLAYER_H

#include<vector>

class Player {
public:
    Player();

    int getHealth() const;
    int getCurrentLocationId() const;

    void setCurrentLocationId(int locationId);
    void takeDamage(int damage);
    void heal(int amount);

    void addPotionId(int potionId);
    bool removePotionId(int potionId);
    std::vector<int> getPotionIds() const;

    bool isAlive() const;

private:
    int health;
    int currentLocationId;
    std::vector<int> potionIds;
};

#endif
