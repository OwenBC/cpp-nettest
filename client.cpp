#include "client.hpp"
#include <iostream>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sys/socket.h>

Client::Client(char *hostname, short port, void *(*start_routine)(void *)) {
    sem_init(&lock, 0, 0);

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct hostent *server;
    if ((server = gethostbyname(hostname)) == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *)&address, sizeof(address));
    address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&address.sin_addr.s_addr,
         server->h_length);
    address.sin_port = htons(port);

    if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "Failed to connect.\n";
        exit(EXIT_FAILURE);
    }

    cthread_args_t args = {&lock, &socket_fd};

    //printf("client init: sem: %p; fd: %p %d\n", &lock, &socket_fd, socket_fd);

    if (pthread_create(&cthread, NULL, start_routine, &args) != 0) {
        std::cout << "Failed to create thread.\n";
        exit(EXIT_FAILURE);
    }
}

Client::~Client(){
    pthread_cancel(cthread);
    sem_close(&lock);
    close(socket_fd);
}
