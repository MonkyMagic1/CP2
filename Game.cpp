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
    gameWon = false;
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

    Chest alchemyChest(2, false);
    alchemyChest.addPotionId(2);
    chests.push_back(alchemyChest);

    Location entrance(1, "Entrance", "Entrance of an underground maze.", true);
    entrance.addArtLine("#################");
    entrance.addArtLine("#               #");
    entrance.addArtLine("#      @   C    #");
    entrance.addArtLine("#               #");
    entrance.addArtLine("#           >   #");
    entrance.addArtLine("#################");
    entrance.addChestId(1);
    entrance.addConnection(2);
    locations.push_back(entrance);

    Location stoneHall(2, "Stone Hall", "A cold hall with old stone walls.", false);
    stoneHall.addArtLine("#################");
    stoneHall.addArtLine("#               #");
    stoneHall.addArtLine("#      @        #");
    stoneHall.addArtLine("#    #####      #");
    stoneHall.addArtLine("#       >       #");
    stoneHall.addArtLine("#################");
    stoneHall.addConnection(1);
    stoneHall.addConnection(3);
    locations.push_back(stoneHall);
    

    Location alchemyRoom(3, "Alchemy Room", "A quiet room with an old chest near the wall.", false);
    alchemyRoom.addArtLine("#################");
    alchemyRoom.addArtLine("#               #");
    alchemyRoom.addArtLine("#       @   C   #");
    alchemyRoom.addArtLine("#               #");
    alchemyRoom.addArtLine("#       >       #");
    alchemyRoom.addArtLine("#################");
    alchemyRoom.addChestId(2);
    alchemyRoom.addConnection(2);
    alchemyRoom.addConnection(4);
    locations.push_back(alchemyRoom);

    Location exitGate(4, "Exit Gate", "A massive gate blocks the way out of the maze.", false);
    exitGate.addArtLine("#################");
    exitGate.addArtLine("#               #");
    exitGate.addArtLine("#       @       #");
    exitGate.addArtLine("#      GATE     #");
    exitGate.addArtLine("#           >   #");
    exitGate.addArtLine("#################");
    exitGate.addConnection(3);
    locations.push_back(exitGate);
}

void Game::printSeparator() const
{
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void Game::printBigSeparator() const
{
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
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

            showConnections(location);

            return;
        }
    }

    std::cout << "Current location was not found." << std::endl;
}

void Game::showConnections(const Location& location) const
{
    if (location.getConnections().empty()) {
        std::cout << "No exits from this location." << std::endl;
        return;
    }

    std::cout << "Available exits: ";

    for (int locationId : location.getConnections()) {
        std::cout << locationId << " ";
    }

    std::cout << std::endl;
}

Location* Game::findLocationById(int locationId)
{
    for (Location& location : locations) {
        if (location.getId() == locationId) {
            return &location;
        }
    }

    return nullptr;
}

bool Game::solveLocationPuzzle(int locationId)
{
    std::string answer;

    if (locationId == 2) {
        std::cout << "Puzzle: What is 2 + 2? ";
        std::cin >> answer;

        return answer == "4";
    }

    if (locationId == 3) {
        std::cout << "Puzzle: Type the word 'potion': ";
        std::cin >> answer;

        return answer == "potion";
    }

    if (locationId == 4) {
        std::cout << "Puzzle: Enter the escape code 123: ";
        std::cin >> answer;

        return answer == "123";
    }

    return true;
}

void Game::moveToLocation()
{
    int currentLocationId = player.getCurrentLocationId();
    int targetLocationId;

    std::cout << "Enter location ID: ";
    std::cin >> targetLocationId;

    for (const Location& location : locations) {
        if (location.getId() == currentLocationId) {
            for (int connectedLocationId : location.getConnections()) {
                if (connectedLocationId == targetLocationId) {
                    Location* targetLocation = findLocationById(targetLocationId);

                    if (targetLocation == nullptr) {
                        std::cout << "Target location was not found." << std::endl;
                        return;
                    }

                    if (!targetLocation->isOpen()) {
                        std::cout << "This location is locked. Solve the puzzle to open it." << std::endl;

                        if (solveLocationPuzzle(targetLocationId)) {
                            targetLocation->openLocation();
                            std::cout << "Puzzle solved. Location opened." << std::endl;
                        } else {
                            player.takeDamage(20);
                            std::cout << "Wrong answer. You took 20 damage." << std::endl;
                            return;
                        }
                    }

                    player.setCurrentLocationId(targetLocationId);
                    std::cout << "You moved to location " << targetLocationId << "." << std::endl;
                    if (targetLocationId == 4) {
                        std::cout << "You escaped the maze. Victory!" << std::endl;
                        gameWon = true;
                    }
                    return;
                }
            }

            std::cout << "You cannot move there from here." << std::endl;
            return;
        }
    }

    std::cout << "Current location was not found." << std::endl;
}

void Game::gameLoop()
{
    int command = -1;

    while (command != 0 && player.isAlive() && !gameWon) {
        printBigSeparator();
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
    std::cout << "3. Move" << std::endl;
    std::cout << "4. Drink potion" << std::endl;
    std::cout << "0. Quit" << std::endl;
}

void Game::handleCommand(int command)
{
    if (command == 1) {
        openChest();
    } else if (command == 2) {
        showInventory();
    } else if (command == 3) {
        moveToLocation();
    } else if (command == 4) {
        drinkPotion();
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
        std::cout << "- ID " << potionId << ": " << getPotionInfoById(potionId) << std::endl;
    }
}

void Game::drinkPotion()
{

    if (player.getPotionIds().empty()) {
        std::cout << "You have no potions." << std::endl;
        return;
    }

    showInventory();

    int potionId;
    std::cout << "Enter potion ID to drink: ";
    std::cin >> potionId;

    for (const Potion& potion : potions) {
        if (potion.getId() == potionId) {
            if (player.removePotionId(potionId)) {
                player.heal(potion.getHealAmount());
                std::cout << "You drank " << potion.getName() << "." << std::endl;
                std::cout << "Health is now " << player.getHealth() << "." << std::endl;
            } else {
                std::cout << "You do not have this potion." << std::endl;
            }

            return;
        }
    }

    std::cout << "Potion was not found." << std::endl;
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