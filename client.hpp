#pragma once
#include <pthread.h>
#include <semaphore.h>
#include <netdb.h>
#include <sys/socket.h>

typedef struct {
    sem_t *sem;
    int *fd;
} cthread_args_t;

class Client {
private:
    sem_t lock;
    pthread_t cthread;
    int socket_fd;
    struct sockaddr_in address;
public:
    Client(char *hostname, short port, void *(*start_routine)(void *));
    ~Client();
};
