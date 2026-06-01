#include "Game.h"

#include <iostream>

void Game::run()
{
    std::cout << "Quest Game" << std::endl;
    showMainMenu();
}

void Game::showMainMenu() const
{
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "0. Exit" << std::endl;
}
