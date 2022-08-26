#include "server.hpp"
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sys/socket.h>

Server::Server(short port, void *(*start_routine)(void *), int no_of_clients) {
    // Init member variables
    m_no_of_clients = no_of_clients;

    // Init semaphores
    for (int i=0; i<no_of_clients; i++) {
        sem_init(&client_sem[i], 0, 0);
    }

    // Start server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    bzero((char *) &serverAddr, sizeof(serverAddr));
    // Automatically be filled with host's IP addr
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // Byte order
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // Bind the socket to the address and port number
    if (bind(server_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) 
            != 0) {
        std::cout << "Failed to bind socket.\n";
        exit(EXIT_FAILURE);
    }

    Server::Open(start_routine);
}

Server::~Server() {
    for (int i=0; i<m_no_of_clients; i++) {
        pthread_cancel(client_threads[i]);
        sem_close(&client_sem[i]);
        close(client_fd[i]);
    }
    close(server_fd);
}

void Server::Open(void *(*start_routine)(void *)) {
    // Listen for connections
    if (listen(server_fd, m_no_of_clients) != 0) {
        std::cout << "Failed to set socket to listen.\n";
        exit(1);
    }

    // Create client threads
    struct sockaddr_in clientAddr;
    socklen_t addr_size = sizeof(clientAddr);
    int i = 0;
    while (i < m_no_of_clients) {

        // Extract a connection from the queue
        client_fd[i] = accept(server_fd, (struct sockaddr*)&clientAddr, 
                &addr_size);
        printf("server: got connection from %s port %d\n", 
                inet_ntoa(clientAddr.sin_addr), 
                ntohs(clientAddr.sin_port));

        hthread_args_t args = {i, &client_sem[i], &client_fd[i]};

        
        /*printf("server init: sem: %p; fd: %p %d\n", &client_sem[i], &client_fd[i], client_fd[i]); 
        send(client_fd[i], "test message\n", 13, 0);
        char buffer[256];
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);*/

        // Create player thread
        if (pthread_create(&client_threads[i++], NULL, start_routine, &args) 
                != 0)
            std::cout << "Failed to create player thread." << --i << "\n";
    }
}
