#pragma once
#include <string>

class Game {
private:
    bool m_host;
public:
    std::string port;

    Game(bool host);
    
    void createGame();
    void joinGame();
};
