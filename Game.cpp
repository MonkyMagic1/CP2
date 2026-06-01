#include "Game.h"

#include <iostream>

void Game::run()
{
    std::cout << "Quest Game" << std::endl;
    showMainMenu();
    startNewGame();
}

void Game::startNewGame()
{
    createLocations();
    showCurrentLocation();
}

void Game::createLocations()
{
    Potion smallPotion(1, "Small healing potion", 20);
    Potion largePotion(2, "Large healing potion", 40);

    potions.push_back(smallPotion);
    potions.push_back(largePotion);

    Chest entranceChest(1, false);
    entranceChest.addPotionId(1);

    chests.push_back(entranceChest);

    Location entrance(1, "Entrance", "Entrance of an underground maze.", true);

    entrance.addArtLine("###########");
    entrance.addArtLine("#    @ C  #");
    entrance.addArtLine("#    >    #");
    entrance.addArtLine("###########");

    entrance.addChestId(1);

    locations.push_back(entrance);
}

void Game::showCurrentLocation() const
{
    int currentLocationId = player.getCurrentLocationId();

    for (const Location& location : locations) {
        if (location.getId() == currentLocationId) {
            std::cout << std::endl;
            std::cout << "Health: " << player.getHealth() << std::endl;
            std::cout << "Location: " << location.getName() << std::endl;
            std::cout << location.getDescription() << std::endl;

            for (const std::string& line : location.getArt()) {
                std::cout << line << std::endl;
            }

        std::cout << std::endl;
        std::cout << "Legend: @ - player, C - chest, > - exit" << std::endl;

        if (!location.getChestIds().empty()) {
            std::cout << "Chests here: ";

            for (int chestId : location.getChestIds()) {
                std::cout << chestId << " ";
            }

            std::cout << std::endl;
        }

            return;
        }
    }

    std::cout << "Current location was not found." << std::endl;
}

void Game::showMainMenu() const
{
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "0. Exit" << std::endl;
}
