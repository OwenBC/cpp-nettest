#pragma once
#include <string>
#include "server.hpp"
#include "client.hpp"

class Game {
private:
    bool m_host;
    short m_port;
    Server *s;
    Client *c;
public:
    Game(bool host, short port);
    ~Game();
    
    void createGame();
    void joinGame();
};
