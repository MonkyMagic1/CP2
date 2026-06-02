#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Location.h"
#include "Potion.h"
#include "Chest.h"
#include <vector>
#include <string>

class Game {
public:
    void run();

private:
    Player player;
    std::vector<Location> locations;
    std::vector<Potion> potions;
    std::vector<Chest> chests;
    std::string getPotionInfoById(int potionId) const;
    bool gameWon;

    void showMainMenu() const;
    void handleMainMenu();
    void startNewGame();
    void createLocations();
    void showCurrentLocation() const;
    void gameLoop();
    void showActions() const;
    void handleCommand(int command);
    void openChest();
    void showInventory() const;
    void drinkPotion();
    void saveGame() const;
    void loadGame();
    void moveToLocation();
    Location* findLocationById(int locationId);
    bool solveLocationPuzzle(int locationId);
    void showConnections(const Location& location) const;
    void printSeparator() const;
    void printBigSeparator() const;
    
};

#endif
