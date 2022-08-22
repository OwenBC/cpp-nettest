#include "game.h"
#include <iostream>

Game::Game(bool host) {
    m_host = host;
    if(host) Game::createGame();
    else Game::joinGame();
}

void Game::createGame() {
    std::cout << "creating a game\n";
}

void Game::joinGame() {
    std::cout << "joining a game\n";
}
