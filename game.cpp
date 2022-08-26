#include "game.hpp"
#include "server.hpp"
#include "client.hpp"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/socket.h>

#include <errno.h>

void *host(void *params) {
    hthread_args_t *args = (hthread_args_t *)params;
    printf("server routine: sem: %p; fd: %p %d\n", args->sem, args->fd, *(args->fd));

    std::cout << "Host thread " << args->id << " started\n";
    char *buffer[100];
    int error=0;
    printf("Sent %d bytes\n", error=send(*(args->fd), &args->id, sizeof(args->id), 0));
    if (error==-1)
        perror("Error: ");
    printf("Recieved %d bytes\n", error=read(*(args->fd), &buffer, sizeof(buffer)));
    if (error==-1)
        perror("Error: ");
    std::cout << "Thread " << args->id << " " << buffer << std::endl;
    return NULL;
}

void *client(void *params) {
    cthread_args_t *args = (cthread_args_t *)params;
    //printf("client routine: sem: %p; fd: %p %d\n", args->sem, args->fd, *(args->fd));

    printf("Starting Client\n");
    sleep(1);
    int id, error=0;
    printf("Recieved %d bytes\n", error=read(*(args->fd), &id, sizeof(id)));
    if (error==-1)
        perror("Error: ");
    std::cout << "Client thread " << id << " started\n";
    char msg[100] = "Client response\n";
    printf("Sent %d bytes\n", error=send(*(args->fd), &msg, sizeof(msg), 0));
    if (error==-1)
        perror("Error: ");
    return NULL;
}

//Game::Game() = delete;

Game::Game(bool host, short port) {
    m_host = host;
    m_port = port;
    if(host) Game::createGame();
    else Game::joinGame();
}

Game::~Game() {
    if (s) delete s;
    if (c) delete c;
}

void Game::createGame() {
    std::cout << "creating a game\n";
    s = new Server(m_port, host, 2);
    c = NULL;
}

void Game::joinGame() {
    std::cout << "joining a game\n";
    s = NULL;
    c = new Client("localhost", m_port, client);
}
