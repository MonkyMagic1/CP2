#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Location.h"
#include "Potion.h"
#include "Chest.h"
#include <vector>

class Game {
public:
    void run();

private:
    Player player;
    std::vector<Location> locations;
    std::vector<Potion> potions;
    std::vector<Chest> chests;

    void showMainMenu() const;
    void startNewGame();
    void createLocations();
    void showCurrentLocation() const;
};

#endif
