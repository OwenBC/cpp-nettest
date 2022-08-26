#pragma once
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int id;
    sem_t *sem;
    int *fd;
} hthread_args_t;

class Server {
private:
    int m_no_of_clients;
    sem_t client_sem[10];
    pthread_t client_threads[10];
    int server_fd, client_fd[10];
public:
    Server(short port, void *(*start_routine)(void *), int no_of_clients);
    ~Server();
private:
    void Open(void *(*start_routine)(void *));
};
