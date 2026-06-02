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
    gameLoop();
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

void Game::printSeparator() const
{
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void Game::showCurrentLocation() const
{
    int currentLocationId = player.getCurrentLocationId();

    for (const Location& location : locations) {
        if (location.getId() == currentLocationId) {
            printSeparator();

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

void Game::gameLoop()
{
    int command = -1;

    while (command != 0 && player.isAlive()) {
        showCurrentLocation();
        showActions();

        std::cout << "Choose action: ";
        std::cin >> command;

        handleCommand(command);
    }

    std::cout << "Game ended." << std::endl;
}

void Game::showActions() const
{
    printSeparator();
    std::cout << "Actions:" << std::endl;
    std::cout << "1. Open chest" << std::endl;
    std::cout << "2. Show inventory" << std::endl;
    std::cout << "0. Quit" << std::endl;
}

void Game::handleCommand(int command)
{
    if (command == 1) {
        openChest();
    } else if (command == 2) {
        showInventory();
    } else if (command == 0) {
        std::cout << "You leave the maze." << std::endl;
    } else {
        std::cout << "Unknown command." << std::endl;
    }
}

void Game::openChest()
{
    printSeparator();
    int currentLocationId = player.getCurrentLocationId();

    for (const Location& location : locations) {
        if (location.getId() == currentLocationId) {
            if (location.getChestIds().empty()) {
                std::cout << "There are no chests here." << std::endl;
                return;
            }

            int chestId = location.getChestIds()[0];

            for (Chest& chest : chests) {
                if (chest.getId() == chestId) {
                    if (chest.isOpened()) {
                        std::cout << "Chest " << chestId << " is already opened." << std::endl;
                    } else {
                        chest.openChest();
                        std::cout << "You opened chest " << chestId << "." << std::endl;
                        
                        for (int potionId : chest.getPotionIds()) {
                            player.addPotionId(potionId);
                            std::cout << "You received potion " << potionId << "." << std::endl;
                        }
                    }

                    return;
                }
            }

            std::cout << "Chest was not found." << std::endl;
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

void Game::showInventory() const
{
    printSeparator();
    std::cout << "Inventory:" << std::endl;

    if (player.getPotionIds().empty()) {
        std::cout << "No potions." << std::endl;
        return;
    }

    std::cout << "Potions:" << std::endl;

    for (int potionId : player.getPotionIds()) {
        std::cout << "- " << getPotionInfoById(potionId) << std::endl;
    }
}

std::string Game::getPotionInfoById(int potionId) const
{
    for (const Potion& potion : potions) {
        if (potion.getId() == potionId) {
            return potion.getName() + " (+" + std::to_string(potion.getHealAmount()) + " HP)";
        }
    }

    return "Unknown potion";
}