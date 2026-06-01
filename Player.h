#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();

    int getHealth() const;
    int getCurrentLocationId() const;

    void setCurrentLocationId(int locationId);
    void takeDamage(int damage);
    void heal(int amount);

    bool isAlive() const;

private:
    int health;
    int currentLocationId;
};

#endif
